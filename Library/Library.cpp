// Library.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Library.h"
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>
#include <locale>
#include <string>

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

LIBRARY_API std::string shift(std::istream& vstup, char ch)
{
	std::string s = "";
	char q = '.';
	std::locale loc;
	if (ch == 'l')
	{
		while (!vstup.eof())
		{
			q = tolower(vstup.get(), loc);
			s += q;
		}
	}
	if (ch == 'u')
	{
		while (!vstup.eof())
		{
			q = toupper(vstup.get(), loc);
			s += q;
		}
	}
	s.pop_back();
	return s;
}
