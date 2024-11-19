
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include "server.hpp"
#include "config.hpp"


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


int	main(/*int argc, char **argv*/)
{
	Server::defaults.insert(std::make_pair<string, string>("listen", "undefined"));
	std::string		filename("./test.conf");
	// Config::init(filename);
	Config::get_servers(filename);


}