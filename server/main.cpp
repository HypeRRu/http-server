#include <iostream>
#include <signal.h>
#include <getopt.h>
#include <unistd.h>
#include "core/server.h"

int main(int argc, char *argv[])
{	
	signal(SIGHUP, SIG_IGN);

	char* ip = nullptr;
	short int port = 0;
	char* work_dir = nullptr;

	int opt;
	/* parse arguments */
	while ((opt = getopt(argc, argv, "h:p:d:")) != -1)
	{
		switch (opt)
		{
			case 'h':
				/* IP address */
				ip = optarg;
				break;
			case 'p':
				/* Port */
				port = atoi(optarg);
				break;
			case 'd':
				/* Working directory */
				work_dir = optarg;
				break;
			default:
				std::cerr << "Usage: " << argv[0] << " [-h ip] [-p port] [-d directory]" << std::endl;
				return 1;
		}
	}
	/* daemonize server */
	daemon(1, 0);
	/* setup server */
	core::Server server(ip, port);
	/* change working and root directory (root permissions required) */
	if (work_dir)
	{
		if (chroot(work_dir) == -1)
		{
			/* if no permissions, change just working directory */
			chdir(work_dir);
		} else
		{
			/* root directory changed, set working directory */
			chdir("/");
		}
	}
	/* start accepting connections */
	server.accept_connections();
	return 0;
}
