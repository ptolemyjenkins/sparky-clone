#pragma once
#include "table.h"

struct ball {
	float mass;
	float drag;
	double radius;
	vec2 impulse;
	vec2 position;
	vec2 prevPosition;
	vec2 velocity;
	vec2 spin;
	vec4 colour;
	bool inUse = false;
	object cushions[6];
	vec4 holes[6];
	int width;
	int height;
	float paddingWidth;
	
	ball() {
		this->mass = 1.0;
		this->drag = 0.5f;
		this->radius = 0.005;
		this->colour = vec4(1, 1, 1, 1);
		this->position = vec2(0, 0);
		this->prevPosition = vec2(0, 0);
		this->spin = vec2(0, 0);
		this->velocity = vec2(0, 0);
	}

	ball(double radius, vec4 colour, vec2 position, float mass , Table table) : ball() {
		this->radius = radius;
		this->colour = colour;
		this->position = position;
		this->mass = mass;
		for (int i = 0; i < 6; i++)
		{
			cushions[i] = table.cushions[i];
			holes[i] = table.holes[i];
		}
		width = table.WIDTH;
		height = table.HEIGHT;
		paddingWidth = table.paddingWidth;
		inUse = true;

	}

	vec2 constDrag = vec2(0, 0);
	void update(double time) {
		velocity += impulse;
		prevPosition = position;
		position += (velocity * time);

		if (velocity.x != 0 || velocity.y != 0) {
			constDrag = velocity * (100 / velocity.length()) * time;
		}

		velocity -= (constDrag);
		velocity -= (velocity * drag * time);
		constDrag.set(0, 0);
	}

	object render(int verts) {
		double t = (2 * 3.14159265359) / verts;
		vec2* points = new vec2[verts];
		for (int i = 0; i < verts; i++)
		{

			points[i] = vec2(position.x + (float) radius * sin(t*i), position.y + (float) radius * cos(t*i));
		}
		
		object object1(points, colour, verts);
		delete [] points;
		return object1;
	}

	vec2 ballCollide(ball other) {
		vec2 line = this->position - other.position;
		vec2 line2 = this->prevPosition - other.prevPosition;
		if (line.length() < this->radius + other.radius && line2.length() > this->radius + other.radius) {
			return   (line * ((velocity - other.velocity).dot(line) / (line.length()* line.length())))* ((-2.0 * other.mass) / (mass + other.mass));

		}
		return vec2(0, 0);
	}

	vec2 wallCollide() {
		//if (this->position.x > this->radius + paddingWidth && this->position.x < width - paddingWidth - this->radius && this->position.y > paddingWidth + this->radius && this->position.y < height - this->radius - paddingWidth) {
		//	return vec2(0, 0);
		//}
		potted();
		vec2 impulse = cushionCollide();
		if (impulse.length() != 0) {
			return impulse;
		}
		if (this->position.x < this->radius && this->prevPosition.x > this->radius) {
			return vec2(-2 * velocity.x, 0);
		}
		if (this->position.x > width - this->radius && this->prevPosition.x < width - this->radius) {
			return vec2(-2 * velocity.x, 0);
		}
		if (this->position.y < this->radius && this->prevPosition.y > this->radius) {
			return vec2(0, -2 * velocity.y);
		}
		if (this->position.y > height - this->radius && this->prevPosition.y < height - this->radius) {
			return vec2(0, -2 * velocity.y);
		}
		return vec2(0, 0);
	}


	vec2 getImpulse(vec2 line, vec2 circleRef) {
		float a;
		float b;
		float c;
		float delta;
		float u;
		a = pow(line.length(), 2);
		b = 2 * circleRef.dot(line);
		c = pow(circleRef.length(), 2) - pow(radius, 2);
		delta = (pow(b, 2) - 4 * a * c)/ (4*pow(a,2));
		u = -b / (2 * a);
		return vec2(u, delta);
	}

	vec2 cushionCollide() {
		vec2 line;
		vec2 circleRef;
		vec2 prevCircleRef;
		vec2 prevUDelta;
		vec2 uDelta;
		vec2 impulse = vec2(0,0);
		for (int i = 0; i < sizeof(cushions)/sizeof(object); i++){
			object  cushion = cushions[i];
			for (int j = 0; j < cushion.numVerts; j++){
				if (j == cushion.numVerts - 1) {
					line = cushion.vertices[0] - cushion.vertices[j];
				} else {
					line = cushion.vertices[j + 1] - cushion.vertices[j];
				}
				circleRef = cushion.vertices[j] - this->position;
				prevCircleRef = cushion.vertices[j] - this->prevPosition;
				uDelta = getImpulse(line, circleRef);
				prevUDelta = getImpulse(line, prevCircleRef);

				if (uDelta.y < 0) {
					continue;
				}
				uDelta.y = sqrt(uDelta.y);
				prevUDelta.y = sqrt(prevUDelta.y);
				if (((uDelta.x + uDelta.y > 0 && uDelta.x + uDelta.y < 1) || (uDelta.x - uDelta.y > 0 && uDelta.x - uDelta.y < 1)) && !((prevUDelta.x + prevUDelta.y > 0 && prevUDelta.x + prevUDelta.y < 1) || (prevUDelta.x - prevUDelta.y > 0 && prevUDelta.x - prevUDelta.y < 1))) {
					vec2 dir = (circleRef + line * uDelta.x).normalised();
					impulse -= dir;
				}

			}
		}
		impulse = impulse.normalised();
		impulse = (impulse * abs(impulse.dot(velocity))) * 2;
		return impulse;
		
	}


	void potted() {
		for (int i = 0; i < sizeof(holes)/sizeof(vec4); i++)
		{
			vec2 centre = vec2(holes[i].x, holes[i].y);
			if ((position - centre).length() < holes[i].w) {
				this->inUse = false;
				this->velocity = vec2(0, 0);
				this->position = vec2(0, 0);
				this->impulse = vec2(0, 0);
			}
		}
	}

};