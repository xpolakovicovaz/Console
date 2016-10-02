// Library.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Library.h"
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>
#include <locale>
#include <string>
#include <vector>
#include <iterator>

//// This is an example of an exported variable
//LIBRARY_API int nLibrary=0;
//
//// This is an example of an exported function.
//LIBRARY_API int fnLibrary(void)
//{
//    return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see Library.h for the class definition
//CLibrary::CLibrary()
//{
//    return;
//}

bool kontrola(std::vector<std::string>& koef)
{
	int kolko = koef.size();
	char *qwe = new char[kolko];
	qwe[0] = '0';
	for (int i = 1; i < kolko; i++)
	{
		qwe[i] = 'x';
		if (koef[i].size()> 1)
			for (int j = 0; j < koef[i].size(); j++)
			{
				if (j == 0 && koef[i].at(0) == '-')j = 1;
				if (isdigit(koef[i].at(j)) == 0) { delete qwe; return false; }
				qwe[i] = 'c';
			}
		else
		{
			if (koef[i].at(0) == '(' || koef[i].at(0) == ')') qwe[i] = 'z';
			if (isdigit(koef[i].at(0)) != 0) qwe[i] = 'c';
			if (koef[i].at(0) == '+' || koef[i].at(0) == '-' || koef[i].at(0) == '*' || koef[i].at(0) == '/')qwe[i] = 'o';
		}
		if (qwe[i] == 'x') { delete qwe; return false; }
		if (qwe[i] == qwe[i - 1] && qwe[i] != 'z') { delete qwe; return false; }
	}
	return true;
}

int nasob(std::vector<std::string>& koef, int kolko, int oz, int zz)
{
	for (int i = oz; i < zz; i++)
	{
		if (koef[i] == "/")
		{
			if (stoi(koef[i + 1]) == 0)return INT_MIN;
			koef[i - 1] = std::to_string(stoi(koef[i - 1]) / stoi(koef[i + 1]));
			koef.erase(koef.begin() + i);
			koef.erase(koef.begin() + i);
			zz += -2;
			i -= 1;
		}
		if (koef[i] == "*")
		{
			koef[i - 1] = std::to_string((int)stoi(koef[i - 1]) * (int)stoi(koef[i + 1]));
			koef.erase(koef.begin() + i);
			koef.erase(koef.begin() + i);
			zz += -2;
			i -= 1;
		}
	}
	return zz;
}

int scitaj(std::vector<std::string>& koef, int kolko, int oz, int zz)
{
	int suma = stoi(koef[oz]);
	for (int i = oz + 1; i < zz; i++)
	{
		if (koef[i] == "+")
			suma += stoi(koef[i + 1]);
		if (koef[i] == "-")
			suma -= stoi(koef[i + 1]);
	}
	return suma;
}

int pocitaj(std::vector<std::string>& koef)
{
	int c = 0;
	int cibz;
	int oz;
	int zz;
	do {
		cibz = 0;
		oz = 0;
		zz = koef.size();
		for (int i = 0; i <koef.size(); i++)
		{
			if (koef[i] == "(")
			{
				oz = i; cibz = 2;
			}
			if (koef[i] == ")")
			{
				zz = i; cibz -= 1; break;
			}
		}

		if (cibz != 1 && cibz != 0) return INT_MIN;
		zz = nasob(koef, koef.size(), oz, zz);
		if (zz == INT_MIN)return INT_MIN;
		if (koef.size() == 1) return stoi(koef[0]);
		if (cibz != 0)oz++;
		c = scitaj(koef, koef.size(), oz, zz);
		if (cibz != 0) {
			koef[oz - 1] = std::to_string(c);
			for (int i = oz; i <= zz; i++)
				koef.erase(koef.begin() + oz);

		}
	} while (cibz != 0);
	return c;
}

LIBRARY_API int calc(std::istream& stream)
{
	std::vector<std::string> koef((std::istream_iterator<std::string>(stream)), (std::istream_iterator<std::string>()));
	int c;
	if (kontrola(koef)) {
		c = pocitaj(koef);
	}
	else return INT_MIN;
	return c;
}