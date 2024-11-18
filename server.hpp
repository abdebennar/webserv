#pragma once

#include <string>
#include <limits>
#include <stdint.h>


typedef struct perm
{
	std::string	path;
	bool		get;
	bool		post;
	bool		del;
} perm;



class	Server
{
	private:
		int	num_server;
		perm *locations;
	
	
};