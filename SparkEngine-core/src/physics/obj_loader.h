#pragma once
#include "../maths/maths.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace sparky {
	class fileLoader {
	public:
		std::vector<maths::vec4> verts;
		std::vector<int> indices;
		std::vector<maths::vec4> norms;
		std::vector<int> nindices;
		fileLoader(std::string filename);


	};


}