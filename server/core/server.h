#ifndef CORE_SERVER_H
#define CORE_SERVER_H

#include <string>
#include "threads/pool.hpp"

namespace core
{
	class Server
	{
	public:
		Server(
			const std::string& ip_addr,
			short int port,
			int max_events = 128
		);
		~Server();

		void accept_connections();
		void shutdown();
		bool is_valid() const;
	protected:
		bool handle_connection(int slave_socket);
		bool setup_master_socket(
			const std::string& ip_addr,
			short int port
		);

		threads::Pool pool_;
		int master_socket_;
		int max_events_;
		bool valid_;
	};
};

#endif
