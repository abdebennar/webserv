#pragma once

#include <string>
#include <limits>
#include <stdint.h>
#include <map>
#include <iostream>

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
	private:
		int	num_server;

	public :
		static std::map<string, string>			defaults;
		static std::map<string, loc_details>	location;
	
	
};