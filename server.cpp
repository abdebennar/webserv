



#include "server.hpp"
#include "config.hpp"

void	Server::setup()
{
	uint16_t 		port;
	in_addr_t	host;
	

	port = Config::get_port();
	host = Config::get_host(); // TODO 
	

}