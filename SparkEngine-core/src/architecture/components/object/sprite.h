#pragma once
#include "../../component.h"
namespace sparky { namespace components{
	class Sprite : public architecture::Component
	{
	private:
		maths::vec4 m_Colour;
		maths::vec4 m_TexCoords;
		int m_TexID;
	public:
		Sprite(maths::vec4 colour, maths::vec4 texCoords, int TexID)
			: m_Colour(colour), m_TexCoords(texCoords), m_TexID(TexID)
		{	}

		~Sprite() {}

		inline maths::vec4 getColor() const { return m_Colour; }
		inline maths::vec2 getBL() const { return maths::vec2(m_TexCoords.x, m_TexCoords.y); }
		inline maths::vec2 getTR() const { return maths::vec2(m_TexCoords.z, m_TexCoords.w); }
		inline int getTexID() const { return m_TexID; }



	};
} }