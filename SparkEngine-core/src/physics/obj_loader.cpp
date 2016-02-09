#include "obj_loader.h"

namespace sparky {
	fileLoader::fileLoader(std::string filename)
	{
		std::ifstream readfile;
		readfile.open(filename);
		std::string line;
		std::string arr[4];
		std::string arr1[3];
		std::string arr2[3];

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
			else if (line.at(0) == 'v' && line.at(1) == 'n') {
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				norms.push_back(maths::vec4(stof(arr[1]), stof(arr[2]), stof(arr[3]), 1));
			}
			else if (line.at(0) == 'f' && line.at(1) == ' '){
				std::stringstream ssin(line);
				
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				for (int i = 1; i < 4; i++) {
					int a = arr[i].find('/');
					arr1[i-1] = arr[i].substr(0, a);
					int b = arr[i].find_last_of('/');
					arr2[i-1] = arr[i].substr(b+1);
				}
				indices.push_back((int) stof(arr1[0]));
				indices.push_back((int) stof(arr1[1]));
				indices.push_back((int) stof(arr1[2]));

				nindices.push_back((int) stof(arr2[0]));
				nindices.push_back((int) stof(arr2[1]));
				nindices.push_back((int) stof(arr2[2]));
			}
		}
	}
}