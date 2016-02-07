#pragma once
#include "../maths/maths.h"

namespace sparky { namespace physics{
	class Tetra {
	private:
		maths::vec4 t1, t2, t3, t4;
	public:
		Tetra();
		Tetra(maths::vec4 t1, maths::vec4 t2, maths::vec4 t3, maths::vec4 t4);

		float volume();
		maths::vec4 COM();
	};
} }