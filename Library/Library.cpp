// Library.cpp : Defines the exported functions for the DLL application.
//
#include <iostream>
#include "stdafx.h"
#include "Library.h"
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>


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

LIBRARY_API std::string menvelkost(std::istream &stream)
{

		std::string line, output;
		/*while (std::getline(stream, line))
		{
		for ()
		}*/
		return "TESTOVACI STRING";


}