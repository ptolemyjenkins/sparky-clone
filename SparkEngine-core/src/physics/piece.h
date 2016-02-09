#pragma once
#include "tetra.h"

namespace sparky {
	namespace physics {
		class Piece : public Tetra {
		private:
		public:
			maths::vec4 normal;
			maths::vec4 position;
			Piece();
			Piece(maths::vec4 t1, maths::vec4 t2, maths::vec4 t3, maths::vec4 t4, maths::vec4 normal);


		};
	}
}