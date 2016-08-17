#include "mesh.h"
namespace sparky { namespace graphics {
	std::unordered_map<std::string, resource::MeshResource> Mesh::loadedModels;

	Mesh::Mesh()
	{
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

	void Mesh::initModel(util::IndexedModel* model){
		this->fileName = "";
		uploadModel(model);
	}

	void Mesh::loadMesh(std::string filename)
	{
		util::ObjModel obj = util::ObjModel(filename);
		util::IndexedModel model;
		obj.toIndexedModel(&model);
		uploadModel(&model);
	}

	void Mesh::initSpriteSheet() {
		this->fileName = "";
		spriteResource = new resource::SpriteResource();
		glBindVertexArray(spriteResource->getVao());
		std::vector<int> intBuffer;
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			intBuffer.push_back(offset + 0);
			intBuffer.push_back(offset + 1);
			intBuffer.push_back(offset + 2);

			intBuffer.push_back(offset + 2);
			intBuffer.push_back(offset + 1);
			intBuffer.push_back(offset + 3);

			offset += 4;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteResource->getIbo());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, intBuffer.size() * sizeof(int), &intBuffer[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::uploadModel(util::IndexedModel* model)
	{
		resource = new resource::MeshResource(model->indices.size());
		glBindVertexArray(resource->getVao());

		glBindBuffer(GL_ARRAY_BUFFER, resource->getPosVbo());
		std::vector<float> floatBuffer;
		for (unsigned int i = 0; i < model->positions.size(); i++) { 
			floatBuffer.push_back(model->positions[i].x);
			floatBuffer.push_back(model->positions[i].y);
			floatBuffer.push_back(model->positions[i].z);
		}	
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, resource->getTexVbo());
		floatBuffer.clear();
		for (unsigned int i = 0; i < model->texCoords.size(); i++) {
			floatBuffer.push_back(model->texCoords[i].x);
			floatBuffer.push_back(model->texCoords[i].y);
		}
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, resource->getNorVbo());
		floatBuffer.clear();
		for (unsigned int i = 0; i < model->normals.size(); i++) {
			floatBuffer.push_back(model->normals[i].x);
			floatBuffer.push_back(model->normals[i].y);
			floatBuffer.push_back(model->normals[i].z);
		}
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, resource->getTanVbo());
		floatBuffer.clear();
		for (unsigned int i = 0; i < model->tangents.size(); i++) {
			floatBuffer.push_back(model->tangents[i].x);
			floatBuffer.push_back(model->tangents[i].y);
			floatBuffer.push_back(model->tangents[i].z);

		}
		glBufferData(GL_ARRAY_BUFFER, floatBuffer.size() * sizeof(float), &floatBuffer[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		std::vector<int> intBuffer;
		for (unsigned int i = 0; i < model->indices.size(); i++)
		{
			intBuffer.push_back(model->indices[i]);
		}
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, intBuffer.size() * sizeof(int), &intBuffer[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void Mesh::beginSprite()
	{
		glBindBuffer(GL_ARRAY_BUFFER, spriteResource->getVbo());
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		m_Buffer = (SpriteVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Mesh::submitSprite(Transform* transform, maths::vec4& colour, maths::vec2& bleft, maths::vec2& tright)
	{
		maths::mat4 trans = transform->getTransformation();
		m_Buffer->vertex = trans.transform(maths::vec4(-1, -1, 0, 1));
		m_Buffer->color = colour;
		m_Buffer->tex = bleft;
		m_Buffer++;

		m_Buffer->vertex = trans.transform(maths::vec4(-1, 1, 0, 1));
		m_Buffer->color = colour;
		m_Buffer->tex = maths::vec2(bleft.x, tright.y);
		m_Buffer++;

		m_Buffer->vertex = trans.transform(maths::vec4(1, -1, 0, 1));
		m_Buffer->color = colour;
		m_Buffer->tex = maths::vec2(tright.x, bleft.y);
		m_Buffer++;

		m_Buffer->vertex = trans.transform(maths::vec4(1, 1, 0, 1));
		m_Buffer->color = colour;
		m_Buffer->tex = tright;
		m_Buffer++;

		spriteResource->size += 6;
	}

	void Mesh::endSprite() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh::drawSprites()
	{
		glBindVertexArray(spriteResource->getVao());

		glEnableVertexAttribArray(SHADER_POSITION_INDEX);//position
		glEnableVertexAttribArray(SHADER_COLOUR_INDEX);//colour
		glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);//Tex-coord

		glBindBuffer(GL_ARRAY_BUFFER, spriteResource->getVbo());
		glVertexAttribPointer(SHADER_POSITION_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(4 * sizeof(GLfloat)));
		glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(8 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteResource->getIbo());
		glDrawElements(GL_TRIANGLES, spriteResource->getSize(), GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(SHADER_POSITION_INDEX);
		glDisableVertexAttribArray(SHADER_COLOUR_INDEX);
		glDisableVertexAttribArray(SHADER_TEXCOORD_INDEX);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::draw()
	{
		glBindVertexArray(resource->getVao());
		glEnableVertexAttribArray(0);//position
		glEnableVertexAttribArray(1);//Tex-coord
		glEnableVertexAttribArray(2);//normal
		glEnableVertexAttribArray(3);//tangent

		glBindBuffer(GL_ARRAY_BUFFER, resource->getPosVbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, resource->getTexVbo());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, resource->getNorVbo());
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, resource->getTanVbo());
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getIbo());
		glDrawElements(GL_TRIANGLES, resource->getSize(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

} }
