//Conway's Game of Life
//written by Ptolemy Jenkins

#include <iostream> //input and output streams
#include <sstream> //for converting string input to integer
#include <chrono> //time library
#include <iomanip> // setting precision for float/doubles
#include "window.h" //GLFW Window envelope class header

//for debug mode change to 1
#define DEBUG 0
#if DEBUG
#define LOG(x) std::cout << x;
#else
#define LOG(x)
#endif

//convenience function for current time in nanoseconds
static long long getNanoTime() {
	auto nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
	return nanoseconds_since_epoch;
}

//two input functions for strings and integers respectively
static std::string getInput(std::string message) {
	std::string line;
	std::cout << message;
	std::getline(std::cin, line);
	return line;
}

static int getIntInput(std::string message, int max, int min) {
	std::string line;
	int num;
	while (true) {
		//using temporary stream to check input type
		std::istringstream is{ getInput(message) };
		if ((is >> num) && !(is >> line)) {
			if (num <= max && num >= min) {
				break;
			}
			std::cout << "Number not within limits. Max:" << max << " Min: " << min << std::endl;
			continue;
		}
		std::cout << "Invalid input." << std::endl;
	}
	return num;
}

//struct containing all the methods to create working game of life
struct Board {
	int height;
	int width;
	bool endlessEdges;
	int delay;

	bool *boxes;
	bool *newBoxes;

	//Constructor initialises and sets all arrays to 0
	Board(int height, int width, bool endlessEdges, int delay) {
		this->height = height;
		this->width = width;
		this->delay = delay;
		this->endlessEdges = endlessEdges;

		boxes = new bool[height * width];
		newBoxes = new bool[height * width];

		for (int i = 0; i < height * width; i++) {
			boxes[i] = 0;
			newBoxes[i] = 0;
		}
	}

	~Board() {
		delete[] boxes;
		delete[] newBoxes;
	}

	//clear all arrays
	void reset() {
		for (int i = 0; i < width * height; i++)
		{
			boxes[i] = 0;
			newBoxes[i] = 0;
		}
	}

	//getters and setters for main array
	bool get(int x, int y) {
		return boxes[y * width + x];
	}

	void set(int x, int y, bool value) {
		if (x + y * width < width * height && x + y * width >= 0) {
			boxes[x + y * width] = value;
		}
	}

	//method for brush tool, sets all squares within certain radius 
	void setAround(int x, int y, bool value, double radius) {
		int r_ = ceil(radius - 0.5);
		for (int i = -r_; i <= r_; i++) {
			for (int j = -r_; j <= r_; j++)
			{
				if (distance(x, y, x - i, y - j) < radius) {
					set(x - i, y - j, value);
				}
			}
		}
	}

	//only used by setAround() to find distances
	double distance(int centrex, int centrey, int boxx, int boxy) {
		double distancex = centrex != boxx ? abs((boxx - 0.5) - (centrex + 0.5)) : 0;
		double distancex1 = abs((boxx + 0.5) - (centrex - 0.5));
		double distancey = centrey != boxy ? abs((boxy - 0.5) - (centrey + 0.5)) : 0;
		double distancey1 = abs((boxy + 0.5) - (centrey - 0.5));
		distancex = distancex > distancex1 ? distancex1 : distancex;
		distancey = distancey > distancey1 ? distancey1 : distancey;
		return sqrt(distancex * distancex + distancey * distancey);
	}

	//pass in many boxes to OpenGL to render in immediate mode
	void render() {
		glBegin(GL_QUADS);
		float x_inc = 2.0 / width;
		float y_inc = 2.0 / height;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++)
			{
				if (get(x, y)) {
					glColor3f((x *1.0) / width, (y *1.0) / height, (1 - (y *1.0) / height));

					glVertex3f(-1.f + x * x_inc, -1.f + y * y_inc, 1.f);
					glVertex3f(-1.f + x * x_inc, -1.f + (y + 1.f) * y_inc, 1.f);
					glVertex3f(-1.f + (x + 1.f) * x_inc, -1.f + (y + 1.f) * y_inc, 1.f);
					glVertex3f(-1.f + (x + 1.f) * x_inc, -1.f + y * y_inc, 1.f);
				}
			}
		}
		glEnd();
	}

	//main method to calculate next step, uses count Neighbours(EE) 
	void advance() {
		int count = 0;
		for (int i = 0; i < height * width; i++)
			newBoxes[i] = 0;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (endlessEdges)
					count = countNeighboursEE(x, y);
				else
					count = countNeighbours(x, y);
				if (boxes[x + y * width]) {
					if (count < 2 || count > 3)
					{
					}
					else {
						newBoxes[x + y * width] = 1;
					}
				}
				else {
					if (count == 3) {
						newBoxes[x + y * width] = 1;
					}
				}
			}
		}
		for (int i = 0; i < width * height; i++)
		{
			boxes[i] = newBoxes[i];
		}
	}

	//this is used when endless edges is off
	int countNeighbours(int x, int y) {
		int count = 0;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (!i && !j)
					continue;
				if (x + i >= width || x + i < 0)
					continue;
				if (y + j >= height || y + j < 0)
					continue;
				if (boxes[x + i + (y + j) * width]) {
					count++;
				}
			}
		}
		return count;
	}

	//this is used when endless edges is on
	int countNeighboursEE(int x, int y) {
		int count = 0;
		int x_ = 0;
		int y_ = 0;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				x_ = x;
				y_ = y;
				if (!i && !j)
					continue;
				if (x + i >= width)
					x_ = -1;
				else if (x + i < 0)
					x_ = width;

				if (y + j >= height)
					y_ = -1;
				else if (y + j < 0)
					y_ = height;

				if (boxes[x_ + i + (y_ + j) * width]) {
					count++;
				}
			}
		}
		return count;
	}
};



//This class deals with the window class and drawing to the board
class GameOfLife {
private:
	//pointers to allow dynamic allocation of memory
	Window* window;
	Board* board;

	bool running;
	bool render;
	bool advance;

	int frameCap = 60;
	int inputLag = 2;
	double advanceDelay = 200;

public:
	//Constructor initialises a window, a board and OpenGL with an orthographic projection
	GameOfLife(int Windowx, int Windowy, int boardx, int boardy, bool edgeless) {
		window = new Window("Game of Life", Windowx, Windowy, true);
		window->build();
		LOG(glGetString(GL_VERSION));

		board = new Board(boardx, boardy, edgeless, advanceDelay);
		board->reset();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1.f, 1.f, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

	}

	~GameOfLife() {
		delete window;
		delete board;
	}

	//start the game
	void run() {
		running = true;
		advance = false;

		//nanosecond variables to time one game loop
		long long lastTime = 0;
		long long startTime;
		long long passedTime;

		//set maximum framerate
		long long frameTimeNano = (long long)(1000000000.0 / frameCap);
		int frames = 0;
		double accFrames = 0;

		//timers allowing input, rendering and advancing to run at different frequencies to increase performance
		long long unprocessedTime_Render = 0;
		long long unprocessedTime_FPScount = 0;
		long long unprocessedTime_Advance = 0;
		long long unprocessedTime_Input = 0;

		//main loop
		while (running) {
			//ending the loop if close requested by window
			if (window->closed()) {
				running = false;
			}

			render = false;

			//if starting get current time as the previous time
			if (lastTime == 0) {
				lastTime = getNanoTime();
			}
			startTime = getNanoTime();
			passedTime = startTime - lastTime;
			lastTime = startTime;

			//incrementing the timers for each process
			unprocessedTime_Render += passedTime;
			unprocessedTime_FPScount += passedTime;
			unprocessedTime_Advance += passedTime;
			unprocessedTime_Input += passedTime;

			//check for input timer
			if (unprocessedTime_Input >= inputLag * 1000000) {
				input();
				board->delay = advanceDelay;
				unprocessedTime_Input = 0;
			}

			//check for Fps counter
			if (unprocessedTime_FPScount >= 1000000000) {
				accFrames = ((double)frames) / (double)(unprocessedTime_FPScount / 1000000000.0);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << accFrames;
				LOG(stream.str(););
				LOG(" Fps\n");
				frames = 0;
				unprocessedTime_FPScount = 0;
			}

			//check for advance timer
			if (unprocessedTime_Advance >= board->delay * 1000000) {
				if (advance)  board->advance();
				unprocessedTime_Advance = 0;
			}

			//check for render timer
			if (unprocessedTime_Render > frameTimeNano) {
				glViewport(0, 0, window->getWidth(), window->getHeight());
				glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();
				board->render();
				frames++;
				window->update();
				unprocessedTime_Render -= frameTimeNano;

			}
		}
	}

private:
	//variables for input method
	double radius = 5;

	double xPre = 0;
	double yPre = 0;
	double x = 0;
	double y = 0;

	//method to fill the gaps between returned mouse positions
	void linearInterpolate(bool value) {
		int divisions = 50 * sqrt(pow((x - xPre)* board->width * 1.0 / window->getWidth(), 2) + pow((y - yPre)* board->height * 1.0 / window->getHeight(), 2));
		for (int i = 0; i <= divisions; i++) {
			double xdiff = (xPre - x) / (divisions * 1.0);
			double ydiff = (yPre - y) / (divisions * 1.0);
			int x_ = (x + i * xdiff) * board->width * 1.0 / window->getWidth();
			int y_ = board->height - (y + i * ydiff) * board->height * 1.0 / window->getHeight();
			board->setAround(x_, y_, value, radius);
		}
	}
	// method that implements all the keyboard and mouse functionality
	void input() {
		//start and stop the simulation
		if (window->isKeyPressed(GLFW_KEY_SPACE)) {
			advance = !advance;
		}

		//these two methods cover the first click of left and right buttons to avoid interpolating with a previous point
		if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			window->getMousePosition(x, y);
			int x_ = x * board->width * 1.0 / window->getWidth();
			int y_ = board->height - y * board->height * 1.0 / window->getHeight();
			board->setAround(x_, y_, true, radius);
			xPre = x;
			yPre = y;
		}

		if (window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			window->getMousePosition(x, y);
			int x_ = x * board->width * 1.0 / window->getWidth();
			int y_ = board->height - y * board->height * 1.0 / window->getHeight();
			board->setAround(x_, y_, false, radius);
			xPre = x;
			yPre = y;
		}

		//methods to handle continous mouse input, linearly interpolating between the points
		if (window->isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			window->getMousePosition(x, y);
			if (xPre != x && yPre != y) {
				linearInterpolate(true);
			}
			xPre = x;
			yPre = y;
			advance = false;
		}

		if (window->isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
			window->getMousePosition(x, y);
			if (xPre != x && yPre != y) {
				linearInterpolate(false);
			}
			xPre = x;
			yPre = y;
			advance = false;
		}

		//four methods to increase and decrease, brush radii and simulation speed
		if (window->isKeyDown(GLFW_KEY_DOWN)) {
			radius -= inputLag * 0.01;
			if (radius <= 0) {
				radius = 0.1;
			}
		}

		if (window->isKeyDown(GLFW_KEY_UP)) {
			radius += inputLag * 0.01;
			if (radius >= 100) {
				radius = 100;
			}
		}

		if (window->isKeyDown(GLFW_KEY_RIGHT)) {
			advanceDelay -= inputLag * 0.3;
			if (advanceDelay <= 1) {
				advanceDelay = 1;
			}
		}

		if (window->isKeyDown(GLFW_KEY_LEFT)) {
			advanceDelay += inputLag * 0.3;
		}

		//calling the board's reset method on R press
		if (window->isKeyPressed(GLFW_KEY_R)) {
			board->reset();
		}

		//incrementing the simulation frame
		if (window->isKeyPressed(GLFW_KEY_ENTER)) {
			board->advance();
			advance = false;
		}

		//mapping the escape key to exit
		if (window->isKeyPressed(GLFW_KEY_ESCAPE)) {
			running = false;
		}
		window->keyUpdate(GLFW_KEY_ESCAPE);
		window->keyUpdate(GLFW_KEY_ENTER);
		window->keyUpdate(GLFW_KEY_R);
		window->keyUpdate(GLFW_KEY_LEFT);
		window->keyUpdate(GLFW_KEY_RIGHT);
		window->keyUpdate(GLFW_KEY_UP);
		window->keyUpdate(GLFW_KEY_DOWN);
		window->keyUpdate(GLFW_KEY_SPACE);
	}
};

	//main function just handles input for the desired board dimentions
	void main() {
		std::cout << "What board dimentions would you like? Max (500x500)\n";
		int x = getIntInput("x:", 500, 1);
		int y = getIntInput("y:", 500, 1);
		int e = getIntInput("Edgeless board? (yes = 1, no = 0)", 1, 0);
		std::cout << std::string(100, '\n');
		std::cout << R"(
 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//\\ \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ //\\
\\//                                                        \\//
 \/       =======================================            \/
 /\             Conways Game of Life                         /\
//\\      =======================================           //\\
\\//                                 Ptolemy Jenkins        \\//
//\\          Instructions:                                 //\\
\\//                                                        \\//
 \/                Space        - start/stop                 \/
 /\                Enter        - advance one step           /\
//\\               R            - reset board               //\\
\\//               Left Mouse   - draw live cells           \\//
//\\               Right Mouse  - erase live cells          //\\
\\//                                                        \\//
 \/                up Arrow     - increase draw radius       \/
 /\                down Arrow   - decrease draw radius       /\
//\\                                                        //\\
\\//               Left Arrow   - increase sim speed        \\//
//\\               Right Arrow  - decrease sim speed        //\\
\\//                                                        \\//
 \/                Esc          - Exit                       \/
)";
		GameOfLife game(1000, 1000, x, y, e);
		game.run();
	}