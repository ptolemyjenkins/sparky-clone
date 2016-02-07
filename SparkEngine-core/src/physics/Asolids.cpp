#include "Asolids.h"

namespace sparky {namespace physics {
	A_solid::A_solid(maths::vec4 vertices[], int vertsize, int indices[], int intsize)
	{
		this->verts = vertices;
		this->vertsize = vertsize;
		this->indices = indices;
		this->intsize = intsize;
		maths::vec4 result;
		for (int i = 0; i < vertsize; i++) {
			result += vertices[i];
		}
		result /= vertsize;
		this->centroid = result;
		this->jigsaw = new Tetra[intsize / 3];
		for (int i = 0; i < intsize; i+=3)
		{
			maths::vec4 vert1 = vertices[indices[i]];
			maths::vec4 vert2 = vertices[indices[i+1]];
			maths::vec4 vert3 = vertices[indices[i+2]];
			Tetra res = Tetra(vert1, vert2, vert3, centroid);
			jigsaw[i / 3] = res;
		}
		float totalVolume = 0;
		for (int i = 0; i < intsize/3; i++)
		{ 
			totalVolume += jigsaw[i].volume();
			com +=  jigsaw[i].COM() * jigsaw[i].volume();
		}
		com /= totalVolume;
		this->Volume = totalVolume;
	}
}}