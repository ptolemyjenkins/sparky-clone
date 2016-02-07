#include "window.h"
#include "util.h"

#define NUMBER 6
#define MAX_POINTS 50000

struct Circle {
	bool inUse;
	Circle* prev;

	vec2 position;
	float radius;
	float rate;
	float theta;

	Circle() {
		inUse = false;
	}

	Circle(vec2 pos, float r, float rate, float theta) {
		this->inUse = true;

		this->position = pos;
		this->radius = r;
		this->rate = rate;
		this->theta = theta;
		this->prev = 0;
	}

	Circle(Circle* prev, float r, float rate, float theta) {
		this->inUse = true;

		this->position = prev->getPosOnR();
		this->radius = r;
		this->rate = rate;
		this->theta = theta;
		this->prev = prev;
	}

	vec2 getPosOnR() {
		return this->position + vec2(0, radius).rotate(theta);
	}

	void update(float delta) {
		theta += rate * delta;
		if (prev != 0) {
			position = prev->getPosOnR();
		}
	}
};

struct Marker {
	vec2 points[MAX_POINTS];
	int count;
	vec4 colour;
	Marker() {
		colour = vec4(0.5, 0.5, 0.5, 1);
		count = 0;
	}

	Marker(vec4 colour) {
		this->colour = colour;
		count = 0;
	}

	void add(vec2 point) {
		if (count < MAX_POINTS) {
			points[count] = point;
			count++;
		}
	}

	void clear() {
		count = 0;
	}
};

class Epicycles {
public:
	bool running;
	Window* window;
	Circle circles[1000];
	Marker mark;

	int width;
	int height;

	int frameCap;
	int inputCap;
	int	updateCap;

	int verts;
	vec4 circleColour;
	bool drawing;
	bool play;
	float speed;
	double PI;

	Epicycles(vec2 wDim, vec2 sDim) {
		window = new Window("Epicycles", wDim.x, wDim.y, false);
		window->build();
		glClearColor(0, 0, 0, 1);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, sDim.x, sDim.y, 0.0f, 1.0f, -1.0f);
		glMatrixMode(GL_MODELVIEW);
		glViewport(0, 0, window->getWidth(), window->getHeight());
		width = sDim.x;
		height = sDim.y;

		initialise();
	}

	void initialise() {
		PI = Pi();
		frameCap = 60;
		inputCap = 60;
		updateCap = 240;

		play = false;
		drawing = false;
		verts = 50;
		speed = 4;
		circleColour = vec4(0.4, 0.3, 0.8, 1);
		mark = Marker(vec4(0.0, 0.6, 0.8, 1));
		glPointSize(10.0f);

		float theta[NUMBER] = {1,2,3,4,0,0};
		float radii[NUMBER] = {300,150,100,50,20,10};
		float rates[NUMBER] = {1,2,3,4*PI,5,6};

		initCircles(vec2(500,500),radii, rates, theta);
	}

	void initCircles(vec2 pos, float radii[], float rates[], float theta[]) {
		circles[0] = Circle(pos, radii[0], rates[0], theta[0]);
		Circle* prev = &circles[0];
		for (int i = 1; i < NUMBER; i++)
		{
			circles[i] = Circle(prev, radii[i], rates[i], theta[i]);
			prev = &(circles[i]);
		}
	}

	void run() {
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

	void render() {
		glColor3f(circleColour.x, circleColour.y, circleColour.z);
		glLineWidth(5.0f);
		for (int i = 0; i < sizeof(circles)/sizeof(Circle); i++)
		{
			circle(circles[i]);
		}
		vec2 point = circles[NUMBER - 1].getPosOnR();
		glColor3f(1, 0.1, 0.1);
		glBegin(GL_POINTS);
		glVertex2f(point.x,height - point.y);
		glEnd();
		marker(mark);
	}

	void input(double delta) {
		if (window->isKeyPressed(GLFW_KEY_ESCAPE)) {
			running = false;
		}

		if (window->isKeyPressed(GLFW_KEY_SPACE)) {
			play = !play;
		}

		if (window->isKeyPressed(GLFW_KEY_M)) {
			drawing = !drawing;
			if (drawing) {
				mark.clear();
			}
		}

		window->keyUpdate(GLFW_KEY_SPACE);
		window->keyUpdate(GLFW_KEY_M);
	}

	void update(double delta) {
		if (play) {
			for (int i = 0; i < sizeof(circles) / sizeof(Circle); i++)
			{
				circles[i].update(delta * speed);
			}
			if(drawing)	mark.add(circles[NUMBER - 1].getPosOnR());
		}
	}

	void circle(Circle circle) {
		if (circle.inUse) {
			double t = (2 * PI) / verts;
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < verts; i++)
			{
				glVertex2f(circle.position.x + (float)circle.radius * sin(t*i),height -( circle.position.y + (float)circle.radius * cos(t*i)));
			}
			glEnd();
		}
	}

	void marker(Marker marker) {
		glLineWidth(2.0f);
		glColor3f(marker.colour.x, marker.colour.y, marker.colour.z);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < (marker.count -1); i++)
		{
			glVertex2f(marker.points[i].x,height - marker.points[i].y);
		}
		glEnd();
	}
};

int maain() {
	Epicycles program(vec2(2000,2000),vec2(1000,1000));
	program.run();
	return 0;
}
