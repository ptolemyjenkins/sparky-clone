#pragma once
#include "../maths/maths.h"
#include "tetra.h"
namespace sparky {namespace physics {
	class A_solid {
	public:
		maths::vec4* verts;
		int vertsize;
		int *indices;
		int intsize;
		float Volume;
		Tetra* jigsaw;
		maths::vec4 centroid;
		maths::vec4 com;
	public:
		A_solid(maths::vec4 vertices[], int vertsize, int indices[], int intsize);
	};
} }
