#include "config.hpp"
#include <sstream>
#include <map>

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// void	Config::init(std::string conff)
// {
// 	file_name = conff;
// }


bool	to_line_exp(string& line)
{
	// line.erase(0, line.find_first_not_of(" \t\n\r"));
    line.erase(line.find_last_not_of(" \t\r") + 1);

	if (line.find_last_of("#") != string::npos)
   		line.erase(line.find_last_of("#"));
	return (true);
}

TYPES	get_type(std::istringstream& str, bool &end)
{
	std::string pattern;
	std::map<std::string, TYPES> key_words;

	end = false;
	key_words.insert(std::make_pair<std::string, TYPES>("server", SERVER));
	key_words.insert(std::make_pair<std::string, TYPES>("{", OPEN_BLOCK));
	key_words.insert(std::make_pair<std::string, TYPES>("}", CLOSE_BLOCK));
	key_words.insert(std::make_pair<std::string, TYPES>("location", CLOSE_BLOCK));

	str >> pattern;
	if (str.eof())	end = true;
	return (key_words[pattern]);
}

// std::istringstream &get_one_block(std::ifstream &file)
// {
// 	string line;
// 	for ( ;; )
// 	{
// 		assert(!"");
// 		std::getline( file, line );
// 		std::istringstream sline(line);

// 		to_line_exp(line);

// 		cout << line << endl;


// 	}
// }

std::vector<Server> Config::get_servers(std::string file_name)
{
	std::ifstream	conff(file_name);
	std::string		line;
	std::string		expression;
	std::string		tocken;
	TYPES 			type;
	int 			blok = 0;
	// int				


	for ( ;; )
	{
		if (!std::getline( conff, line ))	break;

		to_line_exp( line );
		if (!line.empty())
			expression += line;
		// cout << line << endl;
	}

	std::stringstream sexp(expression);

	sexp >> line;
	// cout << sexp << endl;line
	if (line == "server")
	{
		sexp >> line;
		if (line == "{") blok++;
		else goto fail;

		// get_deafults();// getting the global defaults in a server
		// while loop and getting the locations 
		
	}
	exit(0);
	// cout << expression << endl;
	fail:
		std::cerr << "Error : invalid config file" << std::endl;
		std::exit(1);
}