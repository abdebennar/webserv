#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <fstream>


const char http_response[] =
    "HTTP/1.1 200 OK\n"
    "Accept-Ranges: bytes\r\n"
    "Age: 294510\r\n"
    "Cache-Control: max-age=604800\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Date: Fri, 21 Jun 2024 14:18:33 GMT\r\n"
    "Etag: \"3147526947\"\r\n"
    "Expires: Fri, 28 Jun 2024 14:18:33 GMT\r\n"
    "Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT\r\n"
    "Server: ECAcc (nyd/D10E)\r\n"
    "X-Cache: HIT\r\n"
    "Content-Length: [body-lenght] \r\n"
    "\r\n"
    "<!doctype html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
    "    <meta charset=\"UTF-8\">\n"
    "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
    "    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n"
    "    <title>Server Test - It's Working</title>\n"
    "    <style>\n"
    "        body {\n"
    "            font-family: Arial, sans-serif;\n"
    "            text-align: center;\n"
    "            margin-top: 50px;\n"
    "        }\n"
    "        .message {\n"
    "            font-size: 2em;\n"
    "            color: #4CAF50;\n"
    "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <div class=\"message\">It's Working!</div>\n"
    "    <p>Congratulations, your server is up and running.</p>\n"
    "</body>\n"
    "</html>";

// const char *response_404 = "HTTP/1.1 404 Not Found\r\n"
// "Content-Type: text/html; charset=UTF-8\r\n"
// "Cache-Control: no-cache, no-store, must-revalidate\r\n"
// "Date: Fri, 21 Nov 2024 14:18:33 GMT\r\n"
// "Expires: 0\r\n"
// "Server: CustomServer/1.0\r\n"
// "Content-Length: [body length]\r\n";


int main2()
{
	int fd = open("response.txt", O_RDWR);

	write (fd, http_response, strlen(http_response));
	exit(0);

}

// Function to set up a client socket and connect to the server
int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	assert(fd >= 0 && " ERROR: can't open a socket\n");

	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	struct sockaddr_in socketaddr;

	bzero(&socketaddr, sizeof(sockaddr_in));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_port = htons(80);

	int ret = bind(fd, (const struct sockaddr *)&socketaddr, sizeof(socketaddr));
	if (ret < 0)
		perror(""), errno = 0;


	ret = listen(fd, 8);
	assert(ret >= 0 && " ERROR: can't listen \n");

	struct sockaddr client_data = {0};
	socklen_t client_d_len = 0;


	std::string line;
	char in[1024];

	// flags = fcntl(cfd, F_GETFL, 0);
	// fcntl(cfd, F_SETFL, flags | O_NONBLOCK);

	

	

	while (true)
	{
		struct pollfd pfd = {0};
		int cfd = accept(fd, &client_data, &client_d_len);
		if (cfd > 0)
			std::cout << "new connection" << std::endl;
		pfd.events =  POLLIN;
		pfd.fd = cfd;
		if (poll(&pfd, 1, 1000) == 1)
		{
			if (pfd.revents & POLLIN)
			{
				while (true)
				{
					int rr = read(cfd, &in, 1024);
					if (rr > 0)
					{
						in[rr] = 0;
						std::cout << in;
					}
					else
						break;
				}
				int w = write(cfd, http_response, 950);
				std::cout << http_response << std::endl;
				std::cout << w << " of bytes writed in socket fd" << std::endl;

				std::cout << " Done writing !! " << std::endl;
				close(cfd);
				}
		}
		else
			std::cout << "timeout " << std::endl;
	}
	}



