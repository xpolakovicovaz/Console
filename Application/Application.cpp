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
	std::cout << "\t-h - help: celociselna kalkulacka pre priklady zaddane v tvare: 6 / 2 - ( 3 - 9 ) * 8" << std::endl << " - f \"cesta\" vrati vysledok prikladu zo suboru" << std::endl << "v pripade neuspe3nej operacie vrati INT_MIN" << std::endl;;

}

int main(int argc, char **argv)
{
	std::stringstream ss;
	std::fstream subor;
	int c;
	int suma;

	if (argc == 1)
	{
		c = calc(std::cin);
	}
	else
	{
		while ((c = getopt(argc, argv, "hf:")) != EOF)
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
				c = calc(subor);
				break;
			default:
				std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
				DisplayUsage(argv[0]);
			}
		}
		if (argc > 1 && argv[1][0] != 'f')
		{
			for (int i = 1; i < argc; i++) 
			{
				ss << argv[i] << " ";
			}
		}
	}
		std::cout << c << std::endl;
	
	return 0;
}

