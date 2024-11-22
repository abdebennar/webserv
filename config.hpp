
#pragma once

/**

Global Parameters
client_max_body_size

Purpose: Limits the size of the request body (e.g., for file uploads).
Default: None (unlimited).
error_page

Purpose: Path to custom error pages for HTTP errors like 404 or 500.
Default: None (use generic HTTP responses).
worker_connections (Implied by non-blocking requirements)

Purpose: Sets the maximum number of simultaneous connections the server can handle.
Default: System-defined or no limit.
keepalive_timeout (Optional for HTTP 1.1)

Purpose: Sets the duration for keeping idle connections alive.
Default: None (close connections after each request).
server_tokens (Optional)

Purpose: Whether to display server information in responses (for security).
Default: On (displays version info).

http {
    listen 8080;                  # Default port to listen on
    server_name localhost;        # Server's hostname
    root ./;                      # Root directory for serving files
    index index.html;             # Default file for directory requests
    error_page 404 /error_pages/404.html; # Default error page
    client_max_body_size 1m;      # Maximum client body size (default example)

    server {
        location / {
            allow_methods GET;          # Allowed methods for root
            autoindex off;              # Directory listing disabled
        }

        location /tours {
            allow_methods GET POST PUT HEAD;   # Allowed methods
            autoindex on;                      # Directory listing enabled
            index tours1.html;                 # Specific index file
        }

        location /red {
            return 301 /tours;         # Redirect to /tours
        }

        location /cgi-bin {
            root ./;                          # Root directory for CGI
            allow_methods GET POST DELETE;   # Methods allowed for CGI
            index time.py;                   # Default CGI script
            cgi_path /usr/bin/python3 /bin/bash;  # Paths to interpreters
            cgi_extensions .py .sh;          # Extensions for CGI
        }
    }
}


*/

#pragma once


#include "server.hpp"
#include <vector>
#include <fstream>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cerr;

enum GlobalDir
{
	MAX_BODY = 1,	// client_max_body_size
	ERR_PAGE,		// error_page
	WORK_CONN,		// worker_connections
	KEEP_ALV,		// keepalive_timeout
	// SRV_TOKN		// server_tokens (optional )
};


typedef enum
{
	SERVER = 1,
	OPEN_BLOCK,
	CLOSE_BLOCK,
	LOCATION
}	TYPES;

struct	loc_details;


class	Config
{
    
	public :
        std::map<string, string>		defaults;
		std::map<string, loc_details>	location;
        int                             socket_fd;
		struct sockaddr_in 				address;
		socklen_t						socket_len;

    public :
		Config() { address = {0}; socket_len = sizeof(address); };
        int get_port() {
                return atoi(this->defaults["listen"].c_str()); };
        int get_host() {
                return inet_addr(this->defaults["host"].c_str());
        }

        void set_socket(int fd) {
            this->socket_fd = fd ;
        }
        int get_socket() {
            // TODO add protections of invalid fd;
            return (this->socket_fd);
        }

		socklen_t get_socklen() { 
			return (this->socket_len);
		}

		socklen_t *get_socklenp() { 
			return (&socket_len);
		}

		const struct sockaddr* get_address()
		{
			return ((const struct sockaddr *)&this->address);
		}
		struct sockaddr* get_address(int)
		{
			return ((struct sockaddr *)&this->address);
		}

        void	accept_connections(std::vector<struct pollfd> fds);
		void	send_response(int index);
};