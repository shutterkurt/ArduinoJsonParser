#include "CppUnitTest.h"
#include <string>
#include <fstream>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArduinoJsonParserTests
{
	TEST_CLASS(TestExampleCompilation)
	{
		class GccCommandLineBuilder
		{
		public:
			GccCommandLineBuilder(string gccPath)
			{
				buffer = "\"" + gccPath + "\"";
			}

			void addOption(string option)
			{
				bool containsSpace = option.find(' ') != string::npos;

				if (containsSpace)
				{
					buffer.append(" \"" + option + "\"");
				}
				else
				{
					buffer.append(" " + option);
				}
			}

			string commandLine()
			{
				return buffer;
			}

		private:

			string buffer;
		};


	public:
		
		TEST_METHOD(TestMethod1)
		{
			createCppFile();

			int gccReturnCode = callGcc();

			Assert::AreEqual(0, gccReturnCode);
		}

		void createCppFile()
		{
			ifstream  src("..\\..\\examples\\JsonParserExample\\JsonParserExample.ino", std::ios::binary);
			ofstream  dst("JsonParserExample.cpp", std::ios::binary);

			dst << "#include <Arduino.h>";
			dst << std::endl;
			dst << src.rdbuf();
			dst.flush();
		}

		int callGcc()
		{
			string arduinoDir = "C:\\Program Files (x86)\\Arduino\\";

			GccCommandLineBuilder cliBuilder(arduinoDir + "hardware\\tools\\avr\\bin\\avr-g++.exe");

			cliBuilder.addOption("-c");
			cliBuilder.addOption("-Wall");
			cliBuilder.addOption("-fno-exceptions");
			cliBuilder.addOption("-ffunction-sections");
			cliBuilder.addOption("-fdata-sections");
			cliBuilder.addOption("-mmcu=atmega2560");
			cliBuilder.addOption("-DF_CPU=16000000L");
			cliBuilder.addOption("-DUSB_VID=null");
			cliBuilder.addOption("-DUSB_PID=null");
			cliBuilder.addOption("-DARDUINO=105");
			cliBuilder.addOption("-I" + arduinoDir + "hardware\\arduino\\cores\\arduino");
			cliBuilder.addOption("-I" + arduinoDir + "hardware\\arduino\\variants\\mega");
			cliBuilder.addOption("-I..\\..");
			cliBuilder.addOption("JsonParserExample.cpp");
			cliBuilder.addOption("-oArduinoJsonParserExample.o");

			return system(cliBuilder.commandLine().c_str());
		}

	};
}