#include "Asolids.h"

namespace sparky {namespace physics {
	A_solid::A_solid(maths::vec4 vertices[], int vertsize, int indices[],
		int intsize, maths::vec4 norms[], int normsize, int nindices[], int nindsize)
	{
		this->verts = vertices;
		this->vertsize = vertsize;
		this->indices = indices;
		this->intsize = intsize;
		this->norms = norms;
		this->normsize = normsize;
		this->nindices = nindices;
		this->nindsize = nindsize;

		maths::vec4 result;
		for (int i = 0; i < vertsize; i++) {
			result += vertices[i];
		}
		result /= vertsize;
		this->centroid = result;
		this->jigsaw = new Piece[intsize / 3];
		for (int i = 0; i < intsize; i+=3)
		{
			maths::vec4 vert1 = vertices[indices[i] - 1];
			maths::vec4 vert2 = vertices[indices[i + 1] - 1];
			maths::vec4 vert3 = vertices[indices[i + 2] - 1];
			maths::vec4 norm1 = norms[nindices[i] - 1];
			maths::vec4 norm2 = norms[nindices[i + 1] - 1];
			maths::vec4 norm3 = norms[nindices[i + 2] - 1];

			Piece res = Piece(vert1, vert2, vert3, centroid, (norm1 + norm2 + norm3).normalised());
			jigsaw[i / 3] = res;
		}
		float totalVolume = 0;


		for (int i = 0; i < intsize/3; i++)
		{ 
			float a = (jigsaw[i].position).dot(jigsaw[i].normal);
			totalVolume += jigsaw[i].volume()* (a / abs(a));
			com +=  jigsaw[i].COM() * jigsaw[i].volume()* (a / abs(a)); // Copywrite of Ben Kitchen-Mordoor
		}
		com /= totalVolume;
		this->Volume = totalVolume;
	}
}}