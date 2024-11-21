
#pragma once

#include <vector>
#include "server.hpp"
#include "server.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::cerr;


// typedef enum
// {
// 	SERVER = 1,
// 	OPEN_BLOCK,
// 	CLOSE_BLOCK,
// 	LOCATION
// }	TYPES;



class Parse
{
    public :
		static std::vector<Config>	get_servers(std::string filename);
};
