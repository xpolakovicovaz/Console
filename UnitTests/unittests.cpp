#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Library/Library.h"

#include <vector>
#include <fstream>
#include <string>

namespace UnitTests
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Test_XGetOpt_fail)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv = { "appName", "-db", "param B", "-a", "-c", "-e", "param E", "--fail" };
			char * opts = "ab:cde:";

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'd', L"option -d");
			Assert::IsTrue(optarg == nullptr, L"option param -d");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'b', L"option -b");
			Assert::AreEqual(argv[2], optarg, L"option param -b");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'a', L"option -a");
			Assert::IsTrue(optarg == nullptr, L"option param -a");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'c', L"option -c");
			Assert::IsTrue(optarg == nullptr, L"option param -c");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'e', L"option -e");
			Assert::AreEqual(argv[6], optarg, L"option param -e");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == '?', L"option --fail");
			Assert::IsTrue(optind == 8, L"--fail index");
		}

		TEST_METHOD(Test_XGetOpt_param)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv = { "appName", "-db", "param B", "-e", "param E", "param 1", "param 2" };
			char * opts = "ab:cde:";

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'd', L"option -d");
			Assert::IsTrue(optarg == nullptr, L"option param -d");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'b', L"option -b");
			Assert::AreEqual(argv[2], optarg, L"option param -b");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'e', L"option -e");
			Assert::AreEqual(argv[4], optarg, L"option param -e");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == EOF, L"last option");
			Assert::IsTrue(optind == 5, L"first param index");
		}

		TEST_METHOD(Test_Xsubor)
		{
			optarg = "C:\\Users\\Zdenka\\Desktop\\test.txt";
			std::fstream subor;
			subor.open(optarg, std::fstream::in);

			Assert::AreEqual(calc(subor), 32, L"subor");
		}

		TEST_METHOD(Test_Xvstup)
		{
			std::stringstream ss;
			ss << "4 * 8 /10";
			Assert::AreEqual(calc(ss), INT_MIN, L"bez_medzery");
			ss.clear();
			ss << "4 * a - 10";
			Assert::AreEqual(calc(ss), INT_MIN, L"pismeno");
			ss.clear();
			ss << "4 * ( 8 / 10";
			Assert::AreEqual(calc(ss), INT_MIN, L"bez_zatvorky_zatvaracej");
			ss.clear();
			ss << "4 * 8 ) / 10";
			Assert::AreEqual(calc(ss), INT_MIN, L"bez_zatvorky_otvaracej");
			ss.clear();
			ss << "4 * 8 10";
			Assert::AreEqual(calc(ss), INT_MIN, L"2krat_cislo");
			ss.clear();
			ss << "4 * 8 + + 10";
			Assert::AreEqual(calc(ss), INT_MIN, L"2krat_znamienko");
		}

		TEST_METHOD(Test_Xoperacie)
		{
			std::stringstream ss;
			ss << "-8 + 10";
			Assert::AreEqual(calc(ss), 2, L"+");
			ss.clear();
			ss << "8.2 * 10 ";
			Assert::AreEqual(calc(ss), 80, L"*");
			ss.clear();
			ss << "-6 - -4";
			Assert::AreEqual(calc(ss), -2, L"--");
			ss.clear();
			ss << "4 / 0";
			Assert::AreEqual(calc(ss), INT_MIN, L"/0");
			ss.clear();
			ss << "4 / 10";
			Assert::AreEqual(calc(ss), 0, L"0.4");
			ss.clear();
			ss << "2 * 3 * ( -4 ) * 5";
			Assert::AreEqual(calc(ss), -120, L"**");
			ss.clear();
			ss << "2 * 3 + 4 * 5";
			Assert::AreEqual(calc(ss), 26, L"*+*");
			ss.clear();
			ss << "2 - 3 + 4 * 5 / 6";
			Assert::AreEqual(calc(ss), 2, L"-+*/");
			ss.clear();
			ss << "( 1 + 2 ) * 4";
			Assert::AreEqual(calc(ss), 12, L"(+)*");
			ss.clear();
			ss << "( ( 1 + 2 ) * 3 + 4 ) * 5";
			Assert::AreEqual(calc(ss), 65, L"(())");
			ss.clear();
			ss << "5 * ( 2 + 4 )";
			Assert::AreEqual(calc(ss), 30, L"*(+)");
			ss.clear();
			ss << "( ( ( 1 + 2 ) * ( 3 + 4 ) - 10 ) * 4 - 1 ) * 5";
			Assert::AreEqual(calc(ss), 215, L"((()()))");

		}
	};
}