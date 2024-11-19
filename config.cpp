#include "config.hpp"
#include <sstream>
#include <map>

// void	Config::init(std::string conff)
// {
// 	file_name = conff;
// }

void to_line_exp(string &line)
{
	line.erase(0, line.find_first_not_of(" \t\r"));
	line.erase(line.find_last_not_of(" \t\r") + 1);

	if (string::npos && line.find(';') != line.find_last_of(';'))
		line.insert(line.find(';') + 1, "\n");
	if (line.find_last_of("#") != string::npos)
		line.erase(line.find_last_of("#"));
}

// TYPES get_type(std::istringstream &str, bool &end)
// {
// 	std::string pattern;
// 	std::map<std::string, TYPES> key_words;

// 	end = false;
// 	key_words.insert(std::make_pair<std::string, TYPES>("server", SERVER));
// 	key_words.insert(std::make_pair<std::string, TYPES>("{", OPEN_BLOCK));
// 	key_words.insert(std::make_pair<std::string, TYPES>("}", CLOSE_BLOCK));
// 	key_words.insert(std::make_pair<std::string, TYPES>("location", CLOSE_BLOCK));

// 	str >> pattern;
// 	if (str.eof())
// 		end = true;
// 	return (key_words[pattern]);
// }

std::vector<string> split_paths(string &line)
{
	std::istringstream sline(line);
	std::vector<string> paths;
	string path;

	while (sline >> path)
		paths.push_back(path);

	return paths;
}

void get_defaults(std::istringstream &exp)
{
	std::string line;
	std::string value;
	std::string key;
	string path;

	while (exp >> line)
	{
		if (line == "listen" || line == "server_name" || line == "host" ||
			line == "root" || line == "client_max_body_size" || line == "index" || line == "error_page")
		{
			key = line;
			value.clear();
			while (exp >> line)
			{
				value += line + " ";
				if (line.back() == ';')
				{
					value.pop_back();
					break;
				}
			}

			if (value.empty() || value.back() != ';')
				throw std::runtime_error("Invalid format: missing semicolon at the end.");

			if (value.back() == ';')
				value.pop_back();
			Server::defaults[key] = value;
		}
		else if (line == "location")
		{
			exp >> std::ws;
			while (exp >> line)
			{
				if (line == "{")
					break;

				path += line;
				split_paths(line);
			}
			if (line != "{")
				throw std::runtime_error("Invalid format: expacted `{' after location defenetion");
			line.clear();

			exp >> std::ws;
			exp >> line;
			while  (line == "allow_methods" || line == "index" || line == "autoindex" || line == "root" || line == "return")
			{
				// assert(!"inside location");
				key = line;
				value.clear();
				while (exp >> line)
				{
					value += line + " ";
					if (line.back() == ';')
					{
						value.pop_back();
						break;
					}
				}

				if (value.empty() || value.back() != ';')
					throw std::runtime_error("Invalid format: missing semicolon at the end.");

				if (value.back() == ';')
					value.pop_back();
				// Server::defaults[key] = value;

				cout << "key : " << key << " => " << value << endl;
				exp >> std::ws;
				exp >> line;
			}
		}
		else // one server is done
			exit (1); // FIXME
	}
}

std::vector<Server> Config::get_servers(std::string file_name)
{
	std::ifstream conff(file_name);
	std::string line;
	std::string expression;
	std::string tocken;
	TYPES type;
	int blok = 0;

	for (;;)
	{

		if (!std::getline(conff, line))
			break;
		line.push_back('\n');
		to_line_exp(line);
		if (std::istringstream(line) >> std::ws && !std::istringstream(line).eof())
			expression += line;
	}

	std::istringstream sexp(expression);

	sexp >> line;
	if (line == "server")
	{
		sexp >> line;
		if (line == "{")
			blok++;
		else
			goto fail;
		sexp >> std::ws;
		get_defaults(sexp);
	}

	cout << Server::defaults["listen"] << endl;
	cout << Server::defaults["server_name"] << endl;
	cout << Server::defaults["host"] << endl;
	cout << Server::defaults["root"] << endl;
	cout << Server::defaults["index"] << endl;
	cout << Server::defaults["error_page"] << endl;
	exit(0);

fail:
	std::cerr << "Error : invalid config file" << std::endl;
	std::exit(1);
}