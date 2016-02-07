#include "obj_loader.h"

namespace sparky {
	fileLoader::fileLoader(std::string filename)
	{
		std::ifstream readfile;
		readfile.open(filename);
		std::string line;
		std::string arr[4];
		
		while (std::getline(readfile, line)) {
			if (line.at(0) == 'v' && line.at(1) == ' '){
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				verts.push_back(maths::vec4(stof(arr[1]), stof(arr[2]), stof(arr[3]), 1));
			}
			else if (line.at(0) == 'f') {
				std::stringstream ssin(line);
				
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				for (int i = 1; i < 4; i++) {
					int a = arr[i].find('/');
					arr[i] = arr[i].substr(0, a);
				}
				indices.push_back(stof(arr[1]));
				indices.push_back(stof(arr[2]));
				indices.push_back(stof(arr[3]));

			}
		}
	}
}