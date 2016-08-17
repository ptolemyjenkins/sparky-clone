#pragma once
#include "../../component.h"
namespace sparky { namespace components{
	class Sprite : public architecture::Component
	{
	private:
		maths::vec4 m_Colour;
	public:
		Sprite(maths::vec4 colour)
			: m_Colour(colour)
		{	}

		~Sprite() {}

		inline maths::vec4 getColor() const { return m_Colour; }

	};
} }