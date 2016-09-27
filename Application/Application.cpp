// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "..\Library\Library.h"
#include <iostream>

void DisplayUsage(char * appPath)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(appPath, drive, dir, fname, ext);
	std::cout << fname << std::endl;
	std::cout << "\t-h - help: celociselna kalkulacka pre priklady zadane v tvare: ( 8 - 2 ) / 3 + 7" << std::endl;

}

bool kontrola(int argc, char **argv)
{
	char *qwe = new char[argc];
	qwe[0] = '0';
	for (int i = 1; i < argc; i++)
	{
		qwe[i] = 'x';
		if (strlen(argv[i]) > 1)
			for (int j = 0; j < strlen(argv[i]); j++)
			{
				if (j == 0 && argv[i][0] == '-')j = 1;
				if (isdigit(argv[i][j]) == 0) { delete qwe; return false; }
				qwe[i] = 'c';
			}
		else
		{
			if (argv[i][0] == '(' || argv[i][0] == ')') qwe[i] = 'z';
			if (isdigit(argv[i][0]) != 0) qwe[i] = 'c';
			if (argv[i][0] == '+' || argv[i][0] == '-' || argv[i][0] == '*' || argv[i][0] == '/')qwe[i] = 'o';
		}
		if (qwe[i] == 'x') { delete qwe; return false; }
		if (qwe[i] == qwe[i - 1] && qwe[i] != 'z') { delete qwe; return false; }
	}
	return true;
}

int nasob(int argc, char **argv, int oz, int zz)
{
	for (int i = oz; i < zz; i++)
	{
		if (strcmp(argv[i], "/") == 0)
		{
			if (atoi(argv[i + 1]) == 0)return -1;
			argv[i - 1] = itoa(atoi(argv[i - 1]) / atoi(argv[i + 1]), argv[i - 1], 10);
			argv[i] = "+";
			argv[i + 1] = "0";
		}
		if (strcmp(argv[i], "*") == 0)
		{
			argv[i - 1] = itoa(atoi(argv[i - 1]) * atoi(argv[i + 1]), argv[i - 1], 10);
			argv[i] = "+";
			argv[i + 1] = "0";
		}
	}
	return 0;
}

int scitaj(int argc, char **argv, int oz, int zz)
{
	int suma = atoi(argv[oz + 1]);
	for (int i = oz + 1; i < zz; i++)
	{
		if (strcmp(argv[i], "+") == 0)
			suma += atoi(argv[i + 1]);
		if (strcmp(argv[i], "-") == 0)
			suma -= atoi(argv[i + 1]);
	}
	return suma;
}

int pocitaj(int *suma, int argc, char **argv)
{
	int *priklad = new int[argc];
	bool cibz;
	int oz;
	int zz;
	do {
		cibz = false;
		oz = 0;
		zz = argc;
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '(')
				oz = i;
			if (argv[i][0] == ')')
			{
				zz = i; cibz = true; break;
			}
		}
		if ((oz == 0 && zz != argc) || (oz != 0 && zz == argc)) return -1;
		if (nasob(argc, argv, oz, zz) == -1)return -1;
		*suma = scitaj(argc, argv, oz, zz);
		if (cibz) {
			argv[oz] = itoa(*suma, argv[oz], 10);
			for (int i = oz + 1; i < zz; i++)
				argv[i] = argv[i + (zz - oz)];
			for (int i = zz - 1; i < argc - (zz - oz); i++)
				argv[i] = argv[i + (zz - oz)];
			argc -= (zz - oz);
		}
	} while (cibz);
	return 0;
}

int kalkulacka(int argc, char **argv)
{
	int c; int suma;
	if (kontrola(argc, argv)) {
		c = pocitaj(&suma, argc, argv);
		if (c == 0)
		{
			std::wcout << suma << std::endl; return 0;
		}
		else
			std::wcout << "chyba" << std::endl;
	}
	else std::wcout << "chyba" << std::endl;
	return -1;
}
std::string menvelkost(std::istream &stream) 
{
	std::string line, output;
	/*while (std::getline(stream, line)) 
	{
		for ()
	}*/
	return "TESTOVACI STRING";

}

int main(int argc, char **argv)
{
	int c;
	int suma;
	std::istream *stream;
	if (argc == 1)
	{
		return 0;
	}
	else
	{
		while ((c = getopt(argc, argv, "h")) != EOF)
		{
			switch (c)
			{
			case 'h':
				DisplayUsage(argv[0]);
				break;
			case 'f':
				
				break;
			default:
				std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
				DisplayUsage(argv[0]);
			}
		}
		menvelkost(*stream);
		kalkulacka(argc, argv);

	}
	return 0;
}

