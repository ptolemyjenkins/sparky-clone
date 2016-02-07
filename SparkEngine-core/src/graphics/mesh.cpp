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
		if (calcNormal) calcNormals(vertices, vertSize, indices, intSize);
		calcTangents(vertices, vertSize, indices, intSize);
		resource = &resource::MeshResource(intSize);
		glBindVertexArray(resource->getVao());
		glBindBuffer(GL_ARRAY_BUFFER, resource->getVbo());
		float *verts = toBuffer(vertices, vertSize);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertSize, verts, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * intSize, indices, GL_STATIC_DRAW);
		delete [] verts;
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
	}

	void Mesh::draw()
	{
		glEnableVertexAttribArray(0);//position
		glEnableVertexAttribArray(1);//Tex-coord
		glEnableVertexAttribArray(2);//normal
		glEnableVertexAttribArray(3);//tangent

		glBindBuffer(GL_ARRAY_BUFFER, resource->getVbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)20);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)32);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		glDrawElements(GL_TRIANGLES, resource->getSize(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
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
