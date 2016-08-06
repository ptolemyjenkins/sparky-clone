#include "objModel.h"
namespace sparky { namespace util {

	ObjModel::ObjModel(std::string filename)
	{
		std::string pre = "./res/models/";
		std::ifstream readfile;
		readfile.open(pre + filename);

		std::string line;
		std::string arr[4];
		std::string arr1[3];
		std::string arr2[3];
		std::string arr3[3];
		texCoordsB = true;

		while (std::getline(readfile, line)) {
			if (line.at(0) != 'v' && line.at(0) != 'f')
				continue;
			if (line.at(0) == 'v' && line.at(1) == ' ') {
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				positions.push_back(maths::vec3(stof(arr[1]), stof(arr[2]), stof(arr[3])));
			}
			else if (line.at(0) == 'v' && line.at(1) == 'n') {
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				normals.push_back(maths::vec3(stof(arr[1]), stof(arr[2]), stof(arr[3])));
			}
			else if (line.at(0) == 'v' && line.at(1) == 't') {
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 3) {
					ssin >> arr[i];
					++i;
				}
				texCoords.push_back(maths::vec2(stof(arr[1]), stof(arr[2])));
			}
			else if (line.at(0) == 'f' && line.at(1) == ' ') {
				std::stringstream ssin(line);

				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				for (int i = 1; i < 4; i++) {
					int a = arr[i].find('/');
					arr1[i - 1] = arr[i].substr(0, a);
					int b = arr[i].find_last_of('/');
					if (a + 1 != b) {
						arr2[i - 1] = arr[i].substr(a + 1, b);
					}
					else {
						texCoordsB = false;
					}
					arr3[i - 1] = arr[i].substr(b + 1);
				}

				pIndices.push_back((int)stof(arr1[0])-1);
				pIndices.push_back((int)stof(arr1[1])-1);
				pIndices.push_back((int)stof(arr1[2])-1);

				if (texCoordsB) {
					tIndices.push_back((int)stof(arr2[0]) - 1);
					tIndices.push_back((int)stof(arr2[1]) - 1);
					tIndices.push_back((int)stof(arr2[2]) - 1);
				}
				else {
					tIndices.push_back(0);
					tIndices.push_back(0);
					tIndices.push_back(0);
				}

				nIndices.push_back((int)stof(arr3[0])-1);
				nIndices.push_back((int)stof(arr3[1])-1);
				nIndices.push_back((int)stof(arr3[2])-1);
			}
		}
		if (nIndices.size() == pIndices.size()) {
			normalsB = true;
		}
	}

	void ObjModel::toIndexedModel(IndexedModel* result)
	{
		IndexedModel normalModel = IndexedModel();
		std::unordered_map<OBJIndex, int> resultIndexMap;
		std::unordered_map<int, int> normalIndexMap;
		std::unordered_map<int, int> indexMap;

		for (unsigned int i = 0; i < pIndices.size(); i++)
		{
			OBJIndex currentIndex = OBJIndex(pIndices[i], tIndices[i], nIndices[i]);

			maths::vec3 currentPosition = positions[currentIndex.vertexIndex];
			maths::vec2 currentTexCoord;
			maths::vec3 currentNormal;

			if (texCoordsB)
				currentTexCoord = texCoords[currentIndex.texCoordIndex];
			else
				currentTexCoord = maths::vec2(0,0);

			if (normalsB)
				currentNormal = normals[currentIndex.normalIndex];
			else
				currentNormal = maths::vec3(0, 0, 0);

			int modelVertexIndex;
			std::unordered_map<OBJIndex, int>::const_iterator temp = resultIndexMap.find(currentIndex);
			if (temp != resultIndexMap.end()){
				modelVertexIndex = resultIndexMap[currentIndex];
			}
			else {
				modelVertexIndex = result->positions.size();
				resultIndexMap[currentIndex] = modelVertexIndex;

				result->positions.push_back(currentPosition);
				result->texCoords.push_back(currentTexCoord);
				if (normalsB)
					result->normals.push_back(currentNormal);
			}

			int normalModelIndex;
			std::unordered_map<int, int>::const_iterator temp2 = normalIndexMap.find(currentIndex.vertexIndex);
			if (temp2 != normalIndexMap.end()) {
				normalModelIndex = normalIndexMap[currentIndex.vertexIndex];
			}
			else{
				normalModelIndex = normalModel.positions.size();
				normalIndexMap[currentIndex.vertexIndex] = normalModelIndex;

				normalModel.positions.push_back(currentPosition);
				normalModel.texCoords.push_back(currentTexCoord);
				normalModel.normals.push_back(currentNormal);
				normalModel.tangents.push_back(maths::vec3(0, 0, 0));
			}

			result->indices.push_back(modelVertexIndex);
			normalModel.indices.push_back(normalModelIndex);
			indexMap[modelVertexIndex] = normalModelIndex;
		}

		if (!normalsB)
		{
			normalModel.calcNormals();

			for (unsigned int i = 0; i < result->positions.size(); i++)
				result->normals.push_back(normalModel.normals[indexMap[i]]);
		}

		normalModel.calcTangents();

		for (unsigned int i = 0; i < result->positions.size(); i++)
			result->tangents.push_back(normalModel.tangents[indexMap[i]]);

		//		for(int i = 0; i < result.GetTexCoords().size(); i++)
		//			result.GetTexCoords().Get(i).SetY(1.0f - result.GetTexCoords().Get(i).GetY());
	}

} }