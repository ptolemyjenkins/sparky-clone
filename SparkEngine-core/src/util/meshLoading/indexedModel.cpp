#include "indexedModel.h"

namespace sparky { namespace util {
	IndexedModel::IndexedModel()
	{

	}
	void IndexedModel::calcNormals()
	{
		normals.clear();
		for (int i = 0; i < indices.size(); i += 3) {
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];

			maths::vec3 v1 = positions[i1] - positions[i0];
			maths::vec3 v2 = positions[i2] - positions[i0];

			maths::vec3 normal = v1.cross(v2).normalised();

			normals[i0] += normal;
			normals[i1] += normal;
			normals[i2] += normal;
		}
		for (int i = 0; i < normals.size(); i++) {
			normals[i].normalised();
		}
	}

	void IndexedModel::calcTangents()
	{
		tangents.clear();
		for (int i = 0; i < positions.size(); i++)
		{
			tangents.push_back(maths::vec3(0, 0, 0));
		}
		for (int i = 0; i < indices.size(); i += 3) {
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];

			maths::vec3 edge1 = positions[i1] - positions[i0];
			maths::vec3 edge2 = positions[i2] - positions[i0];

			float deltaU1 = texCoords[i1].x - texCoords[i0].x;
			float deltaV1 = texCoords[i1].y - texCoords[i0].y;
			float deltaU2 = texCoords[i2].x - texCoords[i0].x;
			float deltaV2 = texCoords[i2].y - texCoords[i0].y;

			float det = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

			maths::vec3 tangent;
			tangent.x = (det * (edge1.x * deltaV2 - deltaV1 *  edge2.x));
			tangent.y = (det * (edge1.y * deltaV2 - deltaV1 *  edge2.y));
			tangent.z = (det * (edge1.z * deltaV2 - deltaV1 *  edge2.z));

			tangents[i0] += tangent;
			tangents[i1] += tangent;
			tangents[i2] += tangent;
		}
		for (int i = 0; i < tangents.size(); i++) {
			tangents[i].normalised();
		}
	}

} }