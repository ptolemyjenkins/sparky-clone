#pragma once
#include "../../maths/maths.h"

namespace sparky { namespace graphics {
	class Vertex {
	private:
		maths::vec3 pos;
		maths::vec2 texCoord;
		maths::vec3 normal;
		maths::vec3 tangent;
	public:
		static const int SIZE;
		Vertex();
		Vertex(maths::vec3 pos);
		Vertex(maths::vec3 pos, maths::vec2 texCoord);
		Vertex(maths::vec3 pos, maths::vec2 texCoord, maths::vec3 normal);
		Vertex(maths::vec3 pos, maths::vec2 texCoord, maths::vec3 normal, maths::vec3 tangent);

		void setPos(maths::vec3 pos);
		void setTexCoord(maths::vec2 texCoord);
		void setNormal(maths::vec3 normal);
		void setTangent(maths::vec3 tangent);
		
		maths::vec3 getPos();
		maths::vec2 getTexCoord();
		maths::vec3 getNormal();
		maths::vec3 getTangent();
	};
} }