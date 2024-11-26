/**
 * @file cgi.cpp
 * @brief 
 * @date 2024-11-26
 * 
 */

#include "cgi.hpp"
using	std::clog;
using	std::cerr;
using	std::cout;
using	std::endl;



Cgi::Cgi(string& script_path, string& request_body)
{
	this->_script_path = script_path;
	this->_request_body = request_body;


	executeCgi();
	// init_env();
}

string Cgi::get_response()
{
	return (this->response);
}

#define CGI_READ_BUFFS 1024

Cgi_type Cgi::get_cgi_type()
{
	string	script_extension;

	// get the script extention
	script_extension = _script_path.substr(_script_path.find_last_of('.'), _script_path.size());
	// cout << "script extentions : " <<   script_extension << endl;

	if (script_extension == ".py")
		return python;
	else if (script_extension == ".sh")
		return shell;
	else if (script_extension == ".ruby")
		return ruby;
	else if (script_extension == ".php")
		return php;
	else 
		return unknown;
}


void		Cgi::executeCgi()
{
	// creat copy of io fd's

	int fdin = dup(STDIN_FILENO); // TODO mybe add some protections
	int fdout = dup(STDOUT_FILENO);

	//  int fd = fileno(file.rdbuf()->fd());

	int	fileout = fileno(tmpfile());
	int	filein	= fileno(tmpfile());

	char *args[5];

	Cgi_type type = get_cgi_type();
	switch (type)
	{
		case shell:
		{
			args[0] = getenv("SHELL");
			args[1] = (char *) _script_path.c_str();
			args[2] = NULL;
		}
		break;
		case python :
		{
			args[0] = (char *) "/usr/bin/python3";
			args[1] = (char *) _script_path.c_str();
			args[2] = NULL;
		}
		break;
		case ruby:
		{
			args[0] = (char *) "/usr/bin/ruby";
			args[1] = (char *) _script_path.c_str();
			args[2] = NULL;
		} 
		break;
		case php:
		{
			args[0] = (char *) "/usr/bin/php";
			args[1] = (char *) _script_path.c_str();
			args[2] = NULL;
		}
		break;
		default: // TODO 
			_code = 501;
			std::clog << "unimplemented. cgi" << std::endl;
			break;
	}


	/*
	** 	write the request to a file so if cgi want to read so
	*/

	{
		int write_return = write(filein, this->_request_body.c_str(), this->_request_body.size());
		if (write_return == -1)
		{
			perror("CGI write() faild");
			_code = 500;
			return;
		}

		lseek(filein, 0, SEEK_SET); // TODO protect this
	}

	/*
	** 	child proccess to excute the cgi script
	*/

 	int fork_return = fork();
	if (fork_return == -1)
	{
		perror ("fork() faild");
		_code = 500;
		return ;
	}
	else if (fork_return == 0)
	{
		// TODO 2 > /dev/null
		// alarm (timeout);

		alarm(2);
		dup2(fileout, STDOUT_FILENO);
		dup2(filein, STDIN_FILENO);
		close(fdin);
        close(fdout);
		execve(args[0], args, NULL);
		perror ("execve() faild");
		exit(1);
	}

	int exit_code;
	waitpid(fork_return, &exit_code, 0); // TODO add protection

	if (WIFSIGNALED(exit_code))
	{
		if (WTERMSIG(exit_code) == SIGALRM)
		{
			clog << "CGI timeout" << endl;
			_code = 504;
		}
		else
		{
			clog << "CGI terminated by delevered signal [" << WTERMSIG(exit_code) << "]" << endl;
			_code = 500;
 		}
		return ;
	}
	else if (WTERMSIG(exit_code) && WEXITSTATUS(exit_code) != 0)
	{
		clog << "CGI excutable error" << endl;
		_code = 500;
		return;
	}
	else
	{
		char buffer[CGI_READ_BUFFS];
		int	offset;
		lseek(fdout, 0, SEEK_SET);
		while (offset == read(fdout, buffer, CGI_READ_BUFFS - 1))
		{
			if (!offset) break;
			else if (offset == -1)
			{
				perror ("read() faild");
				exit(0);
			}

			buffer[offset] = '\0';
			response += buffer;
		}
	}
}




int main()
{
    // Simulating a basic POST request
    string http_request = 
        "POST /submit HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 27\r\n"
        "\r\n"
        "name=John&age=30";

    // Set the path to the CGI script (simulating Python script)
    string script_path("cgi-bin/cgitest.sh");


        // Initialize the Cgi object with script path and HTTP request body
        Cgi cgi(script_path, http_request);

        // Here we can add more test logic, such as checking the response
        // For example, print the response body
        cout << "CGI Response: " << cgi.get_response() << endl;  // Assuming get_response() exists

    return 0;
}