#include "Pool.h"
Pool::Pool() {
	WIDTH = 2718;
	HEIGHT = 1448;
	WSIZE = 1448.0f;

	frameCap = 60;
	inputCap = 100;
	updateCap = 500;

	force = 0;
	maxForce = 2000;
	paddingWidth = 83;
	ballRadius = 41;
	width = WIDTH - 2 * paddingWidth;

	window = new Window("Pool", (int)(WSIZE * (float)WIDTH / (float)HEIGHT), (int)WSIZE, false);
	window->build();
	//glClearColor(0, 0.4, 0.2, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (GLdouble)WIDTH, (GLdouble)HEIGHT, 0.0f, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, window->getWidth(), window->getHeight());
	for (int i = 0; i < sizeof(balls) / sizeof(ball); i++)
	{
		balls[i] = ball();
	}
	table.initialise(WIDTH, HEIGHT, paddingWidth);
	triangle();
}

Pool::~Pool() {
	delete window;
}

void Pool::run() {
	running = true;

	long long lastTime = 0;
	long long startTime;
	long long passedTime;

	long long frameTimeNano = (long long)(1000000000.0 / frameCap);
	long long inputTimeNano = (long long)(1000000000.0 / inputCap);
	long long updateTimeNano = (long long)(1000000000.0 / updateCap);

	int frames = 0;
	int updates = 0;
	int inputs = 0;

	long long unprocessedTime_Render = 0;
	long long unprocessedTime_FPScount = 0;
	long long unprocessedTime_Input = 0;
	long long unprocessedTime_Update = 0;


	while (running) {
		if (window->closed()) {
			running = false;
		}

		if (lastTime == 0) {
			lastTime = getNanoTime();
		}
		startTime = getNanoTime();
		passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime_Render += passedTime;
		unprocessedTime_FPScount += passedTime;
		unprocessedTime_Input += passedTime;
		unprocessedTime_Update += passedTime;


		if (unprocessedTime_Input >= inputTimeNano) {
			input(unprocessedTime_Input / 1000000000.0);
			inputs++;
			unprocessedTime_Input = 0;
		}

		if (unprocessedTime_Update >= updateTimeNano) {
			update(unprocessedTime_Update / 1000000000.0);
			updates++;
			unprocessedTime_Update = 0;
		}

		if (unprocessedTime_Render > frameTimeNano) {
			glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();
			render();
			frames++;
			window->update();
			unprocessedTime_Render = 0;
		}

		if (unprocessedTime_FPScount >= 1000000000) {
			printf("\n%.2f fps\t", (double)frames / (double)(unprocessedTime_FPScount / 1000000000.0));
			printf("%.2f updates per second\t", (double)updates / (double)(unprocessedTime_FPScount / 1000000000.0));
			printf("%.2f inputs per second\n", (double)inputs / (double)(unprocessedTime_FPScount / 1000000000.0));
			frames = 0;
			updates = 0;
			inputs = 0;
			unprocessedTime_FPScount = 0;
		}
	}
}

void Pool::input(double delta) {
	if (window->isKeyPressed(GLFW_KEY_ESCAPE)) {
		running = false;
	}
	if (window->isKeyPressed(GLFW_KEY_R)) {
		triangle();
	}
	if (window->isKeyPressed(GLFW_KEY_P)) {
		balls[0].position.set(paddingWidth + (3 * width / 4.0), HEIGHT / 2.0);
		balls[0].velocity.set(0, 0);
		balls[0].impulse.set(0, 0);
		balls[0].inUse = true;
	}

	if (window->isKeyDown(GLFW_KEY_SPACE)) {
		force += 4000 * delta;
		if (force > maxForce) {
			force = maxForce;
		}
	}
	if (window->isKeyReleased(GLFW_KEY_SPACE)) {
		double x;
		double y;
		window->getMousePosition(x, y);
		x = x * WIDTH / (1.0 * window->getWidth());
		y = y * HEIGHT / (1.0 * window->getHeight());
		if ((vec2(x, y) - balls[0].position).length() < balls[0].radius) {
			force = 0;
			return;
		}
		vec2 impulse = (vec2(x, y) - balls[0].position).normalised() * force;
		balls[0].impulse.set(impulse);
		force = 0;
	}

	window->keyUpdate(GLFW_KEY_SPACE);
	window->keyUpdate(GLFW_KEY_R);
	window->keyUpdate(GLFW_KEY_P);
}

void Pool::render() {
	for (int k = 0; k < table.objects.size(); k++)
	{
		glBegin(GL_POLYGON);
		glColor3f(table.objects[k].colour.x, table.objects[k].colour.y, table.objects[k].colour.z);
		for (int m = 0; m < table.objects[k].numVerts; m++) {
			glVertex3f(table.objects[k].vertices[m].x, table.objects[k].vertices[m].y, 0.0f);
		}
		glEnd();
		
	}
	for (int i = 0; i < BALL_NUM; i++) {
		if (balls[i].inUse) {
			object renderable = balls[i].render(50);
			glBegin(GL_POLYGON);
			glColor3f(renderable.colour.x, renderable.colour.y, renderable.colour.z);
			for (int j = 0; j < renderable.numVerts; j++) {
				glVertex3f(renderable.vertices[j].x , renderable.vertices[j].y, 0.0f);
			}
			glEnd();
		}
	}
}

void Pool::update(double delta) {
	vec2 impulse = vec2(0, 0);
	for (int i = 0; i < BALL_NUM; i++) {

		if (balls[i].inUse) {
			impulse = balls[i].wallCollide();
			if (impulse.length() != 0) {
				balls[i].impulse += impulse;
			}
			for (int j = 0; j < BALL_NUM; j++) {
				if (!balls[j].inUse) continue;
				if (i > j) continue;
				impulse = balls[i].ballCollide(balls[j]);
				if (impulse.length() != 0) {
					balls[i].impulse += impulse;
					balls[j].impulse -= impulse;
				}
			}
		}
	}
	for (int k = 0; k < BALL_NUM; k++) {
		if (balls[k].inUse) {
			balls[k].update(delta);
			balls[k].impulse.set(0, 0);
		}
	}
}


void Pool::triangle() {
	float ballSep = 1;
	float bYCoord = HEIGHT / 2.0;
	float bXCoord = paddingWidth + (width / 4.0);
	float xInt = ballRadius * sqrt(3) + ballSep;
	float yInt = ballRadius + ballSep;
	balls[0] = ball(ballRadius, vec4(1, 1, 1, 1), vec2(paddingWidth + (3 * width / 4.0), bYCoord), 1.0f, table);
	balls[1] = ball(ballRadius, vec4(0, 0, 0, 1), vec2(bXCoord, bYCoord), 1.0f, table);
	balls[2] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord + 2 * xInt, bYCoord), 1.0f, table);
	balls[3] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord + xInt, bYCoord - yInt), 1.0f, table);
	balls[4] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord + xInt, bYCoord + yInt), 1.0f, table);
	balls[5] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord, bYCoord - 2 * yInt), 1.0f, table);
	balls[6] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord, bYCoord + 2 * yInt), 1.0f, table);
	balls[7] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord - xInt, bYCoord - 3 * yInt), 1.0f, table);
	balls[8] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord - xInt, bYCoord - yInt), 1.0f, table);
	balls[9] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord - xInt, bYCoord + yInt), 1.0f, table);
	balls[10] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord - xInt, bYCoord + 3 * yInt), 1.0f, table);
	balls[11] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord - 2 * xInt, bYCoord - 4 * yInt), 1.0f, table);
	balls[12] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord - 2 * xInt, bYCoord - 2 * yInt), 1.0f, table);
	balls[13] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord - 2 * xInt, bYCoord), 1.0f, table);
	balls[14] = ball(ballRadius, vec4(1, 1, 0, 1), vec2(bXCoord - 2 * xInt, bYCoord + 2 * yInt), 1.0f, table);
	balls[15] = ball(ballRadius, vec4(1, 0, 0, 1), vec2(bXCoord - 2 * xInt, bYCoord + 4 * yInt), 1.0f, table);
}

int main() {
	Pool table;
	table.run();
	return 0;
}

