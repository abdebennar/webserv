
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include "server.hpp"
#include "config.hpp"
#include "parse.hpp"
#include <deque>


using namespace std;

// int main()
// {
// 	int fd = socket(AF_INET, SOCK_STREAM, 0);
// 	assert(fd >= 0 && " ERROR: can't open a socket\n");

// 	struct sockaddr_in socketaddr;

// 	bzero(&socketaddr, sizeof(sockaddr_in));
// 	socketaddr.sin_family = AF_INET;
// 	socketaddr.sin_port = htons(8080);

// 	int ret = bind(fd , (const struct sockaddr *) &socketaddr, sizeof(socketaddr));
// 	if (ret < 0)	perror("");

// 	 ret = listen(fd, 0);
// 	assert(ret >= 0 && " ERROR: can't listen \n");

// 	struct sockaddr client_data = {0};
// 	socklen_t client_d_len = 0;

// 	listen:
// 		int cfd = accept(fd, &client_data, &client_d_len);
// 		char line[100];

// 		struct pollfd pfd;

// 		pfd.events = POLLIN;
// 		pfd.fd = cfd;


// 	while  (true)
// 	{
// 		if (poll(&pfd, 1, 1000) == 1)
// 		{
// 			if (pfd.revents & POLLIN)
// 			{
// 				read(cfd, line, 98);
// 				line[99] = 0;
// 				std::cout << line;
// 				bzero(line, 100);
// 			}
// 		}
// 		else
// 			goto listen;
// 	}


	

// 	close(cfd);
// 	close(fd);

// }

// std::string Config::file_name = "fefault";


// std::map<std::string, loc_details> Server::location;

std::deque<struct pollds>	fds;

void	init(std::vector<Config> servers)
{
	for (int i = 0; i < servers.size(); i++)
	{
		PORT	port = atoi(servers[i].defaults["listen"].c_str());
		// BUG  the address should be trimed from any space
		// cout <<  "host : \'" << servers[i].defaults["host"].c_str() << "'" << endl;
		ip_addr	ip	= inet_addr(servers[i].defaults["host"].c_str() + 1);
		if (ip == -1)
			perror ("83"), exit(errno);

		int sfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sfd < 0)
			perror ("87"), exit(errno);

		int flags = fcntl(sfd, F_GETFL, 0);
		fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
		
		struct sockaddr_in address = {0};

		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = ip;
		socklen_t	len = sizeof(address);

		int bret = bind(sfd, (const struct sockaddr *)&address, len );
		if (bret < 0)
			perror ("87"), exit(errno);

		int lsn = listen(sfd, 5);
		// if

		cout << setw(10) << "Server informations" << endl;
		cout << endl;
		cout << "Server name\t:" <<  servers[i].defaults["server_name"] << endl;
		cout << "Port\t\t: " << port	<< endl;
		cout << "Host\t\t: " << servers[i].defaults["host"] << endl;
		cout << endl;

		while (true)
		{
			// TODO accept all connection 

			// add the conections to the poll fds 
			// remove the closed connections from the poll fds 
		}

	}
	cout << "ALL servers created secsesfully" << endl;
}

// void	run(Server)
// {

// }


int	main(/*int argc, char **argv*/)
{
	// try 
	// {
		std::vector<Config>	servers;
		std::string		filename("./test.conf");
		servers = Parse::get_servers(filename);

		init(servers);
		run();

		// Server::init(); // check all the servers  are valid, check ip addresses
		// , ports , duplication , and creat sockets and bind them , open ports ...
		// Server::run(); // TODO run  the servers , start lestning
	// }


}