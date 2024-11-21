

#include "parse.hpp"

std::vector<string> split_paths(string &line)
{
	std::istringstream sline(line);
	std::vector<string> paths;
	string path;

	while (sline >> path)
		paths.push_back(path);

	return paths;
}

bool	is_defaults(std::string key)
{
	return (key == "listen" || key == "server_name" || key == "host" ||
			key == "root" || key == "client_max_body_size" || key == "index" || key == "error_page");
}

bool	is_location(std::string key)
{
	return (key == "allow_methods" || key == "index" 
	|| key == "autoindex" || key == "root" || key == "return");
}

void to_line_exp(string &line)
{
	line.erase(0, line.find_first_not_of(" \t\r"));
	line.erase(line.find_last_not_of(" \t\r") + 1);

	if (string::npos && line.find(';') != line.find_last_of(';'))
		line.insert(line.find(';') + 1, "\n");
	if (line.find_last_of("#") != string::npos)
		line.erase(line.find_last_of("#"));
}

void	location_params(loc_details &loc, string &key, string &value)
{
	if (key == "allow_methods")
	{
		 // TODO check methodes

		 loc.allow_methods = value;
	}
	else if (key == "autoindex")
	{
		if (value == "on")
			loc.auto_index = true;
		else if (value == "off")
			loc.auto_index = false;
		// FIXME
	}
	else if (key == "root")
	{
		loc.root = value;
		// else throw "Root is  invalid\n"; // FIXME
	}
	else if (key == "index")
	{
		loc.index_path = value;
		// FIXME 
	}
	else 
		assert(false && "unimplemented yet ");
}


void get_defaults(std::istringstream &exp, Config &conf)
{
	std::string line;
	// std::string value;
	std::string	key;
	string		path;
	loc_details	loc = {0};


	while (std::getline(exp, line , '\n'))
	{
		std::istringstream sline(line);

		sline >> key;
		if (is_defaults(key))
		{ 
			if (line.back() != ';')
				throw (std::runtime_error("Error: expected `;' end of expression"));

			std::getline( sline , line );
			line.erase(line.find_last_not_of(";") + 1);
			conf.defaults[key] = line;
			key.clear();
			// sline.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		else if (key == "location")
		{
			std::getline( sline , line );
			size_t pos = line.find_last_not_of(" \n\r\t") ;
			if (pos != string::npos)
			{
				if (line[pos] != '{')
					throw (std::runtime_error("Error: expected `{' after location path"));
				line.erase(line.find('{'));
			}
			std::vector<string> paths = split_paths( line );

			while   (true)
			{
				line.clear();
				// cout << "here" << endl;
 				std::getline( exp, line, '\n' );
				std::istringstream sline(line);

				sline >> key;
				if (is_location(key))
				{ 
					if (line.back() != ';')
					{
						throw (std::runtime_error("Error: expected `;' end of expression"));
					}

					std::getline( sline , line );
					line.erase(line.find_last_not_of(";") + 1);
					location_params( loc, key, line );
					key.clear();
				}
				else if (key == "}")
					break;
			}
			for (int i = 0; i < paths.size() ; i++)
			{
				conf.location[paths[i]] = loc;
			}
		}
		else
			continue;
			// FIXME unexpacted input
	}

}

std::vector<Config> Parse::get_servers(std::string file_name)
{
	std::ifstream conff(file_name);
	std::string line;
	std::string expression;
	std::string tocken;
    Config		servers_conf;
    std::vector<Config> servers; 

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
		// ADD protect errors
		sexp >> std::ws;
		get_defaults(sexp, servers_conf);
        servers.push_back(servers_conf);
	}

	// cout << servers_conf.defaults["listen"] << endl;
	// cout << servers_conf.defaults["server_name"] << endl;
	// cout << servers_conf.defaults["host"] << endl;
	// cout << servers_conf.defaults["root"] << endl;
	// cout << servers_conf.defaults["index"] << endl;
	// cout << servers_conf.defaults["error_page"] << endl;

	// cout << std::boolalpha << servers_conf.location["/"].root << endl;
	// cout << std::boolalpha << servers_conf.location["/user"].allow_methods << endl;
	// cout << std::boolalpha << servers_conf.location["/path1"].allow_methods << endl;

	return (servers);
}