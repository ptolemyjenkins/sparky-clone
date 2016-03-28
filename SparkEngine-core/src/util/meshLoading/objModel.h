#pragma once
#include <vector>
#include "../../maths/maths.h"
#include "indexedModel.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
namespace sparky {
	namespace util {
		class ObjModel {
		private:
			bool texCoordsB;
			bool normalsB;
		public:
			std::vector<maths::vec3> positions;
			std::vector<int> pIndices;
			std::vector<maths::vec2> texCoords;
			std::vector<int> tIndices;
			std::vector<maths::vec3> normals;
			std::vector<int> nIndices;

		public:
			ObjModel(std::string fileName);
			void toIndexedModel(IndexedModel* result);
		};

	struct OBJIndex {
		int vertexIndex;
		int texCoordIndex;
		int normalIndex;
		OBJIndex(int vert, int tex, int norm) :
			vertexIndex(vert), texCoordIndex(tex), normalIndex(norm) {};
		

		bool operator==(const OBJIndex &other) const
		{
			return (vertexIndex == other.vertexIndex
				&& texCoordIndex == other.texCoordIndex
				&& normalIndex == other.normalIndex);
		}

		std::size_t operator()() const{
			int BASE = 17;
			int MULTIPLIER = 31;

			int result = BASE;
			result += MULTIPLIER * result + vertexIndex;
			result += MULTIPLIER * result + texCoordIndex;
			result += MULTIPLIER * result + normalIndex;

			return result;
		}
	};

} }

namespace std {
	template <>
	struct hash<sparky::util::OBJIndex>
	{
		std::size_t operator()(const sparky::util::OBJIndex& k) const
		{
			int BASE = 17;
			int MULTIPLIER = 31;

			int result = BASE;
			result += MULTIPLIER * result + k.vertexIndex;
			result += MULTIPLIER * result + k.texCoordIndex;
			result += MULTIPLIER * result + k.normalIndex;

			return result;
		}
	};
}