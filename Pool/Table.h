#pragma once
#include <vector>
#include "vec.h"
#include "util.h"

struct object {
	std::vector<vec2> vertices;
	vec4 colour;
	int numVerts;
	object(){
		this->numVerts = 0;
		this->colour = vec4(0,0,0,0);
	}
	object(vec2 verts[], vec4 colour, int numVerts) {
		this->numVerts = numVerts;
		this->colour = colour;
		for (int i = 0; i < numVerts; i++)
		{
			vertices.push_back(verts[i]);
		}
	}
};

class Table {
public:
	int WIDTH;
	int HEIGHT;
	std::vector<object> objects;
	std::vector<object> cushions;
	std::vector<vec4> holes;
	double paddingWidth;
private:
	vec4 tableColour;
	vec4 cushionColour;
	vec4 potColour;
	vec4 markColour;

	double halfMarkWidth;

	double middlePocketRadius;
	double middlePocketIndent;
	double cornerPocketRadius;
	double cornerPocketIndent;

	double width;
	double height;

public:
	Table();
	~Table();
	void initialise(int width_, int height_, double paddingWidth);
	void cushion(vec2 back1, vec2 back2, vec2 corner1, vec2 corner2);
	object circle(vec2 pos, double r, vec4 colour, int verts);
	};