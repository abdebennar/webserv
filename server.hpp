#pragma once

#include <string>
#include <limits>
#include <stdint.h>
#include <map>
#include <iostream>
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
#include "config.hpp"


using std::string;
using std::cout;
using std::endl;
using std::cerr;


//		int status_code;
//     bool auto_index;
//     bool has_cgi;
//     std::string root;
//     std::vector<std::string> index_files;
//     std::vector<std::string> allowed_methods;

// 		uint16_t						_port;
// 		in_addr_t						_host;
// 		std::string						_server_name;
// 		std::string						_root;
// 		unsigned long					_client_max_body_size;
// 		std::string						_index;
// 		bool							_autoindex;
// 		std::map<short, std::string>	_error_pages;
// 		std::vector<Location> 			_locations;
//         struct sockaddr_in 				_server_address;
//         int     						_listen_fd;


typedef	uint16_t	PORT;
typedef	in_addr_t	ip_addr;



struct	loc_details
{
	// std::string	path;
	int 		status_code;
	string 		index_path;
	std::string	allow_methods;
	bool		auto_index;
	bool		has_cgi;
	string 		root;

};



class	Server
{
	PORT	port;
	ip_addr	ip;
	public :
		Server();
		void run();
		~Server();
};