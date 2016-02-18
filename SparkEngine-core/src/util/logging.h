#pragma once
#include <iostream>
namespace sparky { namespace util {
	class Logging {
	public:
		static void Log(std::string msg, int errorNum) {
			std::cout << msg.c_str() << std::endl;
			system("PAUSE");
			exit(errorNum);
		}
	};
} }