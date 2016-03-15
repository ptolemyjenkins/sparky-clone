#pragma once
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "logging.h"

namespace sparky { namespace util {
	class FileUtils {
	public:
		static std::string read_file(const char* filepath)
		{
			FILE* file = fopen(filepath, "rt");
			if (file == NULL) {
				std::string i = filepath;
				Logging::Log("File not found error: " + i,1);
			}
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}


		static bool startsWith(std::string string, std::string text) {
			std::string start = string.substr(0, text.size());
			return start == text;
		}

		static int find(std::string text, std::string phrase, int first) {
			text = text.substr(first);
			int i = text.find(phrase);
			if (i == -1) return i;
			return i + first;
		}

		static std::string ltrim(std::string s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
		}

		static std::string rtrim(std::string s) {
			s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
		}

		static std::string trim(std::string s) {
			return ltrim(rtrim(s));
		}
	};
} }