#include "..\src\core.h"
#include "DebugScene.h"
#include "../src/physics/physics.h"
const int WIDTH = (int) (1900 * 1.4);
const int HEIGHT = (int)(1200 * 1.4);
int main()
{
	sparky::DebugScene scene;
	sparky::CoreEngine engine("SparkEngine v0.1", WIDTH, HEIGHT, 60);
	engine.start(&sparky::graphics::RenderingEngine(), &scene);
	return 0;
}