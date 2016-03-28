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

	Mesh::~Mesh()
	{
		if (resource->removeReference() && !(fileName == "")) {
			if (loadedModels.find(fileName) != loadedModels.end()) {
				loadedModels.erase(fileName);
			}
		}
	}

	void Mesh::uploadModel(util::IndexedModel* model)
	{
		resource = new resource::MeshResource(model->indices.size());
		glBindVertexArray(resource->getVao());

		glBindBuffer(GL_ARRAY_BUFFER, resource->getPosVbo());
		std::vector<float> floatBuffer;
		for (int i = 0; i < model->positions.size(); i++) { 
			floatBuffer.push_back(model->positions[i].x);
			floatBuffer.push_back(model->positions[i].y);
			floatBuffer.push_back(model->positions[i].z);
		}	
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, resource->getTexVbo());
		floatBuffer.clear();
		for (int i = 0; i < model->texCoords.size(); i++) {
			floatBuffer.push_back(model->texCoords[i].x);
			floatBuffer.push_back(model->texCoords[i].y);
		}
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		std::vector<int> intBuffer;
		for (int i = 0; i < model->indices.size(); i++)
		{
			intBuffer.push_back(model->indices[i]);
		}
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, intBuffer.size() * sizeof(int), &intBuffer[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}


	void Mesh::loadMesh(std::string filename)
	{
		util::ObjModel obj = util::ObjModel(filename);
		util::IndexedModel model;
		obj.toIndexedModel(&model);
		uploadModel(&model);

	}

	void Mesh::draw()
	{
		glBindVertexArray(resource->getVao());
		glEnableVertexAttribArray(0);//position
		glEnableVertexAttribArray(1);//Tex-coord
		//glEnableVertexAttribArray(2);//normal
		//glEnableVertexAttribArray(3);//tangent

		glBindBuffer(GL_ARRAY_BUFFER, resource->getPosVbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, resource->getTexVbo());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)20);
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, (void*)32);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		glDrawElements(GL_TRIANGLES, resource->getSize(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		//glDisableVertexAttribArray(2);
		//glDisableVertexAttribArray(3);
		glBindVertexArray(0);

	}

} }
