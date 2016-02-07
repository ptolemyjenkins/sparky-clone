#pragma once
#include "window.h"
#include "ball.h"

#define BALL_NUM 16

class Pool {
private:
	Window* window;
private:
	int WIDTH;
	int HEIGHT;
	float WSIZE;

	Table table;
	ball balls[BALL_NUM];

	bool running;

	int frameCap;
	int inputCap;
	int updateCap;


	float force;
	float maxForce;
	double paddingWidth;
	double ballRadius;
	double width;

public:
	Pool();
	~Pool();
	void run();

private:
	void input(double delta);
	void render();
	void update(double delta);
	void triangle();
};