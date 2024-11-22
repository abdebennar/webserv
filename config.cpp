#include "config.hpp"
#include <sstream>
#include <map>

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

extern std::vector<struct pollfd> fds;

void	Config::accept_connections(std::vector<struct pollfd> fds)
{
	int cl = 0;
	struct pollfd tmp;
	for (;; )
	{
		int ret = accept(this->get_socket(), this->get_address(1), get_socklenp());
		if (ret < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
			// std::clog << "no more clients" << endl;
            break;
        } else {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
    }
		tmp.fd = ret;
		tmp.events = POLLIN;
		tmp.revents = 0; 
		fds.push_back(tmp);
		cout << "fd connection: "  << tmp.fd << endl;

		// char req[8192];
		// int r = read(ret, req, sizeof(req) - 1);
		// if (r > 0) 
		// 	req[r] = '\0';
		// cout << req << endl;
		
		cl++;
	}

	cout << "pollds size now are " << fds.size() << endl;
}


void	Config::send_response(int index)
{
	if (fds[index].events & POLLIN)
	{
		cout << "HERE" << endl; 
		write(fds[index].fd, http_response, strlen(http_response));
		close(fds[index].fd);
	}
}







