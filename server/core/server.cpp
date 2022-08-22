#include "server.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <functional>
#include <sstream>
#include <chrono>
#include "processor.h"

using namespace core;

Server::Server(
	const std::string& ip_addr,
	short int port,
	int max_events
):
	pool_{std::thread::hardware_concurrency()}, // initialize thread pool
	max_events_{max_events},
	valid_{true}
{
	/* set default ip and port if not set */
	std::string ip_ = ip_addr.size() ? ip_addr : "127.0.0.1";
	short int port_ = port ? port : 3000;

	valid_ = setup_master_socket(ip_, port_);
}

Server::~Server()
{
	if (valid_)
		shutdown();
}

bool Server::setup_master_socket(
	const std::string& ip_addr,
	short int port
)
{
	/* create socket */
	master_socket_ = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP
	);
	if (master_socket_ == -1)
		return false;
	/* set reuseaddr flag */
	int flag = 1;  
    if (setsockopt(master_socket_, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) 
	    return false;
	/* create sockaddr struct */
	struct sockaddr_in master_in;
	master_in.sin_family = AF_INET;
	master_in.sin_port = htons(port);
	inet_pton(
		AF_INET, 
		ip_addr.c_str(),
		&master_in.sin_addr.s_addr
	);
	/* bind master socket to given address */
	if (bind(master_socket_, (struct sockaddr*)&master_in, sizeof(master_in)) == -1)
	{
		::shutdown(master_socket_, SHUT_RDWR);
		close(master_socket_);
		return false;
	}
	/* set socket listen with max backlog */
	if (listen(master_socket_, SOMAXCONN) == -1)
	{
		::shutdown(master_socket_, SHUT_RDWR);
		close(master_socket_);
		return false;
	}
	return true;
}

void Server::shutdown()
{
	/* close master socket */
	::shutdown(master_socket_, SHUT_RDWR);
	close(master_socket_);
	valid_ = false;
}

void Server::accept_connections()
{
	/* create epoll descriptor */
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		shutdown();
		return;
	}
	/* epoll events */
	struct epoll_event ev, events[max_events_];
	/* setup events */
	ev.events = EPOLLIN;
	ev.data.fd = master_socket_;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, master_socket_, &ev) == -1)
	{
		shutdown();
		return;
	}
	/* accept new connections */
	while (valid_)
	{
		int nfds = epoll_wait(epoll_fd, events, max_events_, -1);
		if (nfds == -1)
		{
			shutdown();
			return;
		}
		for (long int n = 0; n < nfds; ++n)
		{
			if (events[n].data.fd == master_socket_)
			{
				/* accepting new connection */
				int slave_socket = accept4(
					master_socket_, 
					NULL, 
					NULL,
					SOCK_NONBLOCK
				);
				/* skip failed connections */
				if (slave_socket == -1)
					continue;
				/* add epoll event */
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = slave_socket;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, slave_socket, &ev) == -1)
				{
					/* skip */
					shutdown();
					::shutdown(slave_socket, SHUT_RDWR);
					close(slave_socket);
					continue;
				}
			} else 
			{
				epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
				/* call handler function */
				pool_.add_task(
					std::bind(
						&Server::handle_connection,
						this,
						std::cref(events[n].data.fd)
					)
				);
			}
		}
	}
}

bool Server::handle_connection(int slave_socket)
{
	size_t buffer_size = 256;
	std::stringstream request_stream;
	char buffer[buffer_size + 1];
	/* waiting for resource ready */
	while (recv(
			slave_socket,
			buffer,
			buffer_size,
			MSG_PEEK | MSG_NOSIGNAL
		) == -1)
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
	/* read all data from socket */
	while (true)
	{
		ssize_t received = recv(
			slave_socket, 
			buffer, 
			buffer_size, 
			MSG_NOSIGNAL
		);
		if (received > 0)
			buffer[received] = '\0';
		else
			break;
		/*else if (received == 0)
			break;
		else if (received == -1 && errno == EAGAIN)
			continue;*/
		request_stream << buffer;
	}
	/* Data as Request */
	char* request_raw = new char[request_stream.str().length() + 1];
	request_raw[request_stream.str().length()] = '\0';
	request_stream.read(request_raw, request_stream.str().length());
	http::Request request(request_raw);
	delete [] request_raw;
	/* Process request and get response */
	http::Response* response = core::Processor::process_request(request);
	send(
		slave_socket,
		response->get().str().c_str(),
		response->get().str().size(),
		MSG_NOSIGNAL
	);
	/* close connection */
	::shutdown(slave_socket, SHUT_RDWR);
	close(slave_socket);
	return true;
}

bool Server::is_valid() const
{
	return valid_;
}
