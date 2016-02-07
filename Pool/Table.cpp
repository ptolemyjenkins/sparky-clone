#include "Table.h"
Table::Table() {
	tableColour = vec4(62 / 255.0, 180 / 255.0, 10 / 255.0, 1);
	cushionColour = vec4(0.15, 0.6, 0.001, 1);
	potColour = vec4(0, 0, 0, 1);
	markColour = vec4(0, 0, 0, 1);

	halfMarkWidth = 1.275;

	middlePocketRadius = 76;
	middlePocketIndent = 6;
	cornerPocketRadius = 89;
	cornerPocketIndent = 40;

	this->paddingWidth = paddingWidth;
	width = WIDTH - 2 * paddingWidth;
	height = HEIGHT - 2 * paddingWidth;
}

Table::~Table() {
	
}

object Table::circle(vec2 pos, double r, vec4 colour, int verts) {
	double t = (2 * 3.14159265359) / verts;
	vec2* points = new vec2[verts];
	for (int i = 0; i < verts; i++)
	{
		points[i] = vec2(pos.x + (float)r * sin(t*i), pos.y + (float)r * cos(t*i));
	}
	object circ(points, colour, verts);
	delete points;
	return circ;
	
}

void Table::initialise(int width_, int height_, double paddingWidth) {
	WIDTH = width_;
	HEIGHT = height_;

	this->paddingWidth = paddingWidth;
	width = WIDTH - 2 * paddingWidth;
	height = HEIGHT - 2 * paddingWidth;

	vec2* points = new vec2[4];
	points[0] = vec2(0, 0);
	points[1] = vec2(WIDTH, 0);
	points[2] = vec2(WIDTH, HEIGHT);
	points[3] = vec2(0, HEIGHT);
	objects.push_back(object(points, tableColour, 4));

	points[0] = vec2(paddingWidth + (3 * width / 4.0) - halfMarkWidth, paddingWidth);
	points[1] = vec2(paddingWidth + (3 * width / 4.0) + halfMarkWidth, paddingWidth);
	points[2] = vec2(paddingWidth + (3 * width / 4.0) + halfMarkWidth, height + paddingWidth);
	points[3] = vec2(paddingWidth + (3 * width / 4.0) - halfMarkWidth, height + paddingWidth);
	objects.push_back(object(points, markColour, 4));

	float cIndent = cornerPocketIndent + sqrt(pow(cornerPocketRadius, 2) - pow(cornerPocketIndent, 2));
	float mIndent = sqrt(pow(middlePocketRadius, 2) - pow(middlePocketIndent, 2));
	float altMIndent = mIndent + (middlePocketIndent*paddingWidth / sqrt(pow(middlePocketRadius, 2) - pow(middlePocketIndent, 2)));
	cushion(vec2(cIndent, HEIGHT), vec2((WIDTH / 2.0) - mIndent, HEIGHT), vec2(cIndent + paddingWidth, HEIGHT - paddingWidth), vec2((WIDTH / 2.0) - altMIndent, HEIGHT - paddingWidth));
	cushion(vec2((WIDTH / 2.0) + mIndent, HEIGHT), vec2(WIDTH - cIndent, HEIGHT), vec2((WIDTH / 2.0) + altMIndent, HEIGHT - paddingWidth), vec2(WIDTH - cIndent - paddingWidth, HEIGHT - paddingWidth));
	cushion(vec2(cIndent, 0), vec2((WIDTH / 2.0) - mIndent, 0), vec2(cIndent + paddingWidth, paddingWidth), vec2((WIDTH / 2.0) - altMIndent, paddingWidth));
	cushion(vec2((WIDTH / 2.0) + mIndent, 0), vec2(WIDTH - cIndent, 0), vec2((WIDTH / 2.0) + altMIndent, paddingWidth), vec2(WIDTH - cIndent - paddingWidth, paddingWidth));
	cushion(vec2(0, cIndent), vec2(0, HEIGHT - cIndent), vec2(paddingWidth, cIndent + paddingWidth), vec2(paddingWidth, HEIGHT - cIndent - paddingWidth));
	cushion(vec2(WIDTH, cIndent), vec2(WIDTH, HEIGHT - cIndent), vec2(WIDTH - paddingWidth, cIndent + paddingWidth), vec2(WIDTH - paddingWidth, HEIGHT - cIndent - paddingWidth));
	//cushion(vec2(1200, 400), vec2(1400, 400), vec2(1400, 800), vec2(1200, 800));
	circle(vec2(paddingWidth + (width / 4.0), HEIGHT / 2.0), 2 * halfMarkWidth, markColour, 6);

	objects.push_back(circle(vec2(cornerPocketIndent, cornerPocketIndent), cornerPocketRadius, potColour, 50));
	holes.push_back(vec4(cornerPocketIndent, cornerPocketIndent, 0, cornerPocketRadius));
	objects.push_back(circle(vec2(WIDTH - cornerPocketIndent, cornerPocketIndent), cornerPocketRadius, potColour, 50));
	holes.push_back(vec4(WIDTH - cornerPocketIndent, cornerPocketIndent, 0, cornerPocketRadius));
	objects.push_back(circle(vec2(WIDTH - cornerPocketIndent, HEIGHT - cornerPocketIndent), cornerPocketRadius, potColour, 50));
	holes.push_back(vec4(WIDTH - cornerPocketIndent, HEIGHT - cornerPocketIndent, 0, cornerPocketRadius));
	objects.push_back(circle(vec2(cornerPocketIndent, HEIGHT - cornerPocketIndent), cornerPocketRadius, potColour, 50));
	holes.push_back(vec4(cornerPocketIndent, HEIGHT - cornerPocketIndent, 0, cornerPocketRadius));

	objects.push_back(circle(vec2(WIDTH / 2.0, middlePocketIndent), middlePocketRadius, potColour, 50));
	holes.push_back(vec4(WIDTH / 2.0, middlePocketIndent, 0, middlePocketRadius));
	objects.push_back(circle(vec2(WIDTH / 2.0, HEIGHT - middlePocketIndent), middlePocketRadius, potColour, 50));
	holes.push_back(vec4(WIDTH / 2.0, HEIGHT - middlePocketIndent, 0, middlePocketRadius));

}

void Table::cushion(vec2 back1, vec2 back2, vec2 corner1, vec2 corner2) {
	vec2* points = new vec2[4];
	points[0] = back1;
	points[1] = corner1;
	points[2] = corner2;
	points[3] = back2;
	objects.push_back(object(points, cushionColour, 4));
	cushions.push_back(objects.back());
}