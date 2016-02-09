#include "piece.h"
namespace sparky{ namespace physics{
	Piece::Piece() : Tetra()
	{
		this->normal = maths::vec4(0, 0, 0, 1);
	}
	Piece::Piece(maths::vec4 t1, maths::vec4 t2, maths::vec4 t3, maths::vec4 t4, maths::vec4 normal) : Tetra(t1, t2, t3, t4)
	{
		this->position = t1 + t2 + t3 - maths::vec4(0,0,0,3);
		this->normal = normal;
	}
} }
