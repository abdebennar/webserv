
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




#define NO_EVENT 0


std::vector<struct pollfd> fds;


int is_server(vector<Config> servers, int index)
{
	for (int i = 0; i < servers.size(); i++)
	{
		if (fds[index].fd == servers[i].get_socket())
			return (i);
	}
	return 0;
}

void	init(std::vector<Config> servers)
{

	for (int i = 0; i < servers.size(); i++)
	{
		struct pollfd tmp = {0};
		// struct sockaddr_in address = {0};
		
		servers[i].set_socket(socket(AF_INET, SOCK_STREAM, 0));

		int flags = fcntl(servers[i].get_socket(), F_GETFL, 0);
		flags = fcntl(servers[i].get_socket(), F_SETFL, flags | O_NONBLOCK);
		
		if (flags == -1)
			perror ("faild to fcntl()");

		servers[i].address.sin_family = AF_INET;
		servers[i].address.sin_port = htons(servers[i].get_port());
		servers[i].address.sin_addr.s_addr = servers[i].get_host();

		int bret = bind(servers[i].get_socket(), servers[i].get_address(), servers[i].get_socklen());
		if (bret < 0)
			perror ("87"), exit(errno);

		int lsn = listen(servers[i].get_socket(), 5);
		if (lsn < 0)
			perror ("faild to listen()");

		tmp.fd = servers[i].get_socket();
		tmp.events = POLLIN;
		tmp.revents = 0;

		fds.push_back(tmp);

	}
	
		clog << "ALL servers created secsesfully" << endl;

		cout << "sizeof pollfd is : " << fds.size() << endl;

	while (true)
	{
		struct pollfd *tmp = fds.data();
		int p_ret = poll( tmp, fds.size(), 1000);
		if (p_ret == -1)
			perror ("faild to poll()");
		else if (p_ret == 0)
			continue;
		else
		{
			for (int i = 0 ;i < fds.size(); i++)
			{
				// check the fd if is server so POLLIN means new connection
				// else the client iswaiting for response 
				if (fds[i].revents == 0)
					continue;
				int srv = is_server(servers, i);
				if (srv)
				{
					if (fds[srv].revents & POLLIN)
						servers[srv].accept_connections(fds);
				}
				if (fds[i].revents & POLLIN)
				{
					// recv(fds[i].fd, req, 8192, 0);

					cout <<  "event frome: " << fds[i].fd << endl;

					char req[8192];
					int r = read(fds[i].fd, req, sizeof(req) - 1); // Limit to buffer size minus 1
					if (r > 0) {
						req[r] = '\0'; // Null-terminate the string
						cout << req << endl;
					} else if (r == 0) {
						// Handle EOF (peer closed the connection)
						cout << "Connection closed by peer." << endl;
					} else {
						// Handle error case
						perror("read failed");
}


				}
				// else if (fds[i].ev)
				// {
				// 	servers[i].send_response(i);
				// }


				// if (fds[i].fd == sfd) 
				// {
				// 	cout << "in socket accept" << endl;
				// 	// int newfd = accept(sfd, (struct sockaddr*)&address, &len);
				// 	if (newfd < 0)
				// 		perror ("faild to accept()");
				// 	// recv(newfd, (void*)http_response, strlen(http_response),0);
				// 	int flags = fcntl(newfd, F_GETFL, 0);
				// 	fcntl(newfd, F_SETFL, flags | O_NONBLOCK);
				// 	fds.push_back({newfd, POLLIN,0});
				// }
				// if (fds[i].revents == POLLIN)
				// {
				// 	cout << "writing data" << endl;
				// 	send(fds[fds.size() - 1 ].fd, (void*)http_response, strlen(http_response), 0);
				// 	cout << "done writing" << std::endl;
				// }					
			}
		}


	// // 		// add the conections to the poll fds 
	// // 		// remove the closed connections from the poll fds 
	}
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

		Config	server1;
		Config	server2;
		server1.defaults["listen"] = "9090";
		server2.defaults["listen"] = "9099";
		server1.defaults["host"] 	= "127.0.0.1";
		server2.defaults["host"] 	= "127.0.0.1";

		servers.push_back(server1);
		servers.push_back(server2);
 
		// servers = Parse::get_servers(filename);

		init(servers);
		// run();

		// Server::init(); // check all the servers  are valid, check ip addresses
		// , ports , duplication , and creat sockets and bind them , open ports ...
		// Server::run(); // TODO run  the servers , start lestning
	// }


}