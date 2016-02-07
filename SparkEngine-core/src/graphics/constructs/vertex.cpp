#include "vertex.h"
namespace sparky { namespace graphics {
	const int Vertex::SIZE = 11;

	Vertex::Vertex()
	{

	}
	Vertex::Vertex(maths::vec3 pos)
	{
		this->pos = pos;

	}
	Vertex::Vertex(maths::vec3 pos, maths::vec2 texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}
	Vertex::Vertex(maths::vec3 pos, maths::vec2 texCoord, maths::vec3 normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	Vertex::Vertex(maths::vec3 pos, maths::vec2 texCoord, maths::vec3 normal, maths::vec3 tangent)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		this->tangent = tangent;
	}

	void Vertex::setPos(maths::vec3 pos)
	{
		this->pos = pos;
	}

	void Vertex::setTexCoord(maths::vec2 texCoord)
	{
		this->texCoord = texCoord;
	}

	void Vertex::setNormal(maths::vec3 normal)
	{
		this->normal = normal;
	}

	void Vertex::setTangent(maths::vec3 tangent)
	{
		this->tangent = tangent;
	}

	maths::vec3 Vertex::getPos()
	{
		return pos;
	}

	maths::vec2 Vertex::getTexCoord()
	{
		return texCoord;
	}

	maths::vec3 Vertex::getNormal()
	{
		return normal;
	}

	maths::vec3 Vertex::getTangent()
	{
		return tangent;
	}
} }
