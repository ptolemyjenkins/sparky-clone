#include "mesh.h"
namespace sparky { namespace graphics {
	std::unordered_map<std::string, resource::MeshResource> Mesh::loadedModels;

	Mesh::Mesh(){
	}

	Mesh::Mesh(const std::string& fileName)
	{
		this->fileName = fileName;
		auto result = loadedModels.find(fileName);
		if (result != loadedModels.end()) {
			resource =  &result->second;
			resource->addReference();
		} else {
			loadMesh(fileName);
			loadedModels[fileName] = *resource;
		}
	}

	Mesh::Mesh(Vertex vertices[], int vertSize, int indices[], int intSize)
	{
		fileName = "";
		addVertices(vertices, vertSize, indices, intSize, false);
	}

	Mesh::Mesh(Vertex vertices[], int vertSize, int indices[], int intSize, bool calcNormal)
	{
		fileName = "";
		addVertices(vertices, vertSize, indices, intSize, calcNormal);
	}

	Mesh::~Mesh()
	{
		if (resource->removeReference() && !(fileName == "")) {
			if (loadedModels.find(fileName) != loadedModels.end()) {
				loadedModels.erase(fileName);
			}
		}
	}

	float * Mesh::toBuffer(Vertex vertices[], int vertSize)
	{
		float* verts = new float[vertSize * Vertex::SIZE];
		for (int i = 0; i < vertSize; i++)
		{
			verts[i * 11] = vertices[i].getPos().x;
			verts[i * 11 + 1] = vertices[i].getPos().y;
			verts[i * 11 + 2] = vertices[i].getPos().z;
			verts[i * 11 + 3] = vertices[i].getTexCoord().x;
			verts[i * 11 + 4] = vertices[i].getTexCoord().y;
			verts[i * 11 + 5] = vertices[i].getNormal().x;
			verts[i * 11 + 6] = vertices[i].getNormal().y;
			verts[i * 11 + 7] = vertices[i].getNormal().z;
			verts[i * 11 + 8] = vertices[i].getTangent().x;
			verts[i * 11 + 9] = vertices[i].getTangent().y;
			verts[i * 11 + 10] = vertices[i].getTangent().z;
		}
		return verts;
	}

	void Mesh::addVertices(Vertex vertices[], int vertSize, int indices[], int intSize, bool calcNormal)
	{
		//if (calcNormal) calcNormals(vertices, vertSize, indices, intSize);
		//calcTangents(vertices, vertSize, indices, intSize);
		resource = new resource::MeshResource(intSize);
		glBindVertexArray(resource->getVao());
		glBindBuffer(GL_ARRAY_BUFFER, resource->getPosVbo());
		std::vector<float> floatBuffer;
		for (int i = 0; i < vertSize; i++) { 
			floatBuffer.push_back(vertices[i].getPos().x);
			floatBuffer.push_back(vertices[i].getPos().y);
			floatBuffer.push_back(vertices[i].getPos().z);
		}	
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		std::vector<int> intBuffer;
		for (int i = 0; i < intSize; i++)
		{
			intBuffer.push_back(indices[i]-1);
		}
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, intBuffer.size() * sizeof(int), &intBuffer[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	void Mesh::calcNormals(Vertex vertices[], int vertSize, int indices[], int intSize)
	{
		for (int i = 0; i < intSize; i += 3) {
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];

			maths::vec3 v1 = vertices[i1].getPos() - vertices[i0].getPos();
			maths::vec3 v2 = vertices[i2].getPos() - vertices[i0].getPos();

			maths::vec3 normal = v1.cross(v2).normalised();

			vertices[i0].setNormal(vertices[i0].getNormal().add(normal));
			vertices[i1].setNormal(vertices[i1].getNormal().add(normal));
			vertices[i2].setNormal(vertices[i2].getNormal().add(normal));

		}
		for (int i = 0; i < vertSize; i++) {
			vertices[i].setNormal(vertices[i].getNormal().normalised());
		}
	}

	void Mesh::loadMesh(std::string filename)
	{
		std::vector<maths::vec3> verts;
//TODO- fix normals
		std::vector<int> indices;
		std::vector<maths::vec3> norms;
		std::vector<int> nindices;

		std::string pre = "./res/models/";
		std::ifstream readfile;
		readfile.open(pre + filename);
		std::string line;
		std::string arr[4];
		std::string arr1[3];
		std::string arr2[3];

		while (std::getline(readfile, line)) {
			if (line.at(0) == 'v' && line.at(1) == ' ') {
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				verts.push_back(maths::vec3(stof(arr[1]), stof(arr[2]), stof(arr[3])));
			}
			else if (line.at(0) == 'v' && line.at(1) == 'n') {
				std::stringstream ssin(line);
				int i = 0;
				while (ssin.good() && i < 4) {
					ssin >> arr[i];
					++i;
				}
				norms.push_back(maths::vec3(stof(arr[1]), stof(arr[2]), stof(arr[3])));
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
					arr2[i - 1] = arr[i].substr(b + 1);
				}
				indices.push_back((int)stof(arr1[0]));
				indices.push_back((int)stof(arr1[1]));
				indices.push_back((int)stof(arr1[2]));

				nindices.push_back((int)stof(arr2[0]));
				nindices.push_back((int)stof(arr2[1]));
				nindices.push_back((int)stof(arr2[2]));
			}
		}
		std::vector<Vertex> vertexs;
		for (int i = 0; i < verts.size(); i++)
		{
			vertexs.push_back(Vertex(verts[i]));
		}
		addVertices(&vertexs[0], verts.size(), &indices[0], indices.size(), true);

	}

	void Mesh::draw()
	{
		glBindVertexArray(resource->getVao());
		glEnableVertexAttribArray(0);//position
		//glEnableVertexAttribArray(1);//Tex-coord
		//glEnableVertexAttribArray(2);//normal
		//glEnableVertexAttribArray(3);//tangent

		glBindBuffer(GL_ARRAY_BUFFER, resource->getPosVbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)12);
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)20);
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)32);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		glDrawElements(GL_TRIANGLES, resource->getSize(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);
		//glDisableVertexAttribArray(2);
		//glDisableVertexAttribArray(3);
		glBindVertexArray(0);

	}

	void Mesh::calcTangents(Vertex vertices[], int vertSize, int indices[], int intSize)
	{
		for (int i = 0; i < intSize; i += 3) {
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];

			maths::vec3 edge1 = vertices[i1].getPos() - (vertices[i0].getPos());
			maths::vec3 edge2 = vertices[i2].getPos() - (vertices[i0].getPos());

			float deltaU1 = vertices[i1].getTexCoord().x - vertices[i0].getTexCoord().x;
			float deltaV1 = vertices[i1].getTexCoord().y - vertices[i0].getTexCoord().y;
			float deltaU2 = vertices[i2].getTexCoord().x - vertices[i0].getTexCoord().x;
			float deltaV2 = vertices[i2].getTexCoord().y - vertices[i0].getTexCoord().y;

			float det = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

			maths::vec3 tangent;
			tangent.x = (det * (edge1.x * deltaV2 - deltaV1 *  edge2.x));
			tangent.y = (det * (edge1.y * deltaV2 - deltaV1 *  edge2.y));
			tangent.z = (det * (edge1.z * deltaV2 - deltaV1 *  edge2.z));

			vertices[i0].setTangent(vertices[i0].getTangent().add(tangent));
			vertices[i1].setTangent(vertices[i1].getTangent().add(tangent));
			vertices[i2].setTangent(vertices[i2].getTangent().add(tangent));
		}
		for (int i = 0; i < vertSize; i++) {
			vertices[i].setTangent(vertices[i].getTangent().normalised());
		}

	}
} }
