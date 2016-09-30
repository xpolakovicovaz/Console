// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "..\Library\Library.h"
#include <iostream>
#include <string>
#include <locale>    
#include <fstream>
#include <sstream>

void DisplayUsage(char * appPath)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(appPath, drive, dir, fname, ext);
	std::cout << fname << std::endl;
	std::cout << "\t-h - help: zmena pismen v zadanom retazci/subore/na vstupe z konzoly na male/velke" << std::endl << "-l/-u [\"retazac\"]/[-f \"nazov_suboru\"]/[] " << std::endl;

}

int main(int argc, char **argv)
{
	std::stringstream ss;
	std::fstream subor;
	std::string s = "koala";
	int c;


	if (argc == 1)
	{
		return 0;
	}
	else
	{
		while ((c = getopt(argc, argv, "hluf:")) != EOF)
		{
			switch (c)
			{
			case 'h':
				DisplayUsage(argv[0]);
				break;
			case 'f':
				subor.open(optarg, std::fstream::in);
				if (!subor.is_open())
				{
					return -1;
				}
				if (argv[1][1] == 'l')
					s = shift(subor, 'l');
				if (argv[1][1] == 'u')
					s = shift(subor, 'u');
				break;
			case 'l':
				if (argc == 2)
					s = shift(std::cin, 'l');
				if (argc == 3)
				{
					ss << argv[2];
					s = shift(ss, 'l');
				}
				break;
			case 'u':
				if (argc == 2)
					s = shift(std::cin, 'u');
				if (argc == 3)
				{
					ss << argv[2];
					s = shift(ss, 'l');
				}
				break;
			default:
				std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
				DisplayUsage(argv[0]);
			}
		}

		std::cout << s << std::endl;
	}
	return 0;
}

