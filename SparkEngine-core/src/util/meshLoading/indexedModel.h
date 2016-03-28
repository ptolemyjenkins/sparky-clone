#pragma once
#include <vector>
#include "../../maths/maths.h"
namespace sparky { namespace util{
	class IndexedModel {
	public:
		std::vector<maths::vec3> positions;
		std::vector<maths::vec2> texCoords;
		std::vector<maths::vec3> normals;
		std::vector<maths::vec3> tangents;
		std::vector<int> indices;
	public:
		IndexedModel();
		void calcNormals();
		void calcTangents();

	};
} }