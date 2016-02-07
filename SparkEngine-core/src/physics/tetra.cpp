#include "tetra.h"
namespace sparky { namespace physics {
	Tetra::Tetra()
	{
		t1 = maths::vec4(0, 0, 0, 1);
		t2 = maths::vec4(0, 0, 0, 1);
		t3 = maths::vec4(0, 0, 0, 1);
		t4 = maths::vec4(0, 0, 0, 1);
	}

	Tetra::Tetra(maths::vec4 t1, maths::vec4 t2, maths::vec4 t3, maths::vec4 t4)
	{
		this->t1 = t1;
		this->t2 = t2;
		this->t3 = t3;
		this->t4 = t4;
	}
	float Tetra::volume()
	{
		return abs((t1 - t4).dot((t2 - t4).cross(t3 - t4)))/6.0;
	}

	maths::vec4 Tetra::COM()
	{
		return (t1 + t2 + t3 + t4) / 4.0;
	}

} }