#pragma once
#include "architecture\application.h"
#include "graphics\window.h"
#include "profiling\profileTimer.h"
#include <thread>

namespace sparky {
	class CoreEngine
	{
	private:
		char* title;
		bool isRunning;
		architecture::Application* app = 0;
		graphics::Window *window = 0;
		graphics::RenderingEngine *renderingEngine;
		int width;
		int height;
		double frameTime;
		long long frameTimeNano;
	public:
		CoreEngine(char* title, const int& width = 400, const int& height = 400, const double& frameCap = 60);
		void start(architecture::Application* app);
		void stop();
		void run();
		
		graphics::RenderingEngine* getRenderingEngine();
		architecture::Application* getApplication();
		graphics::Window* getWindow();
	};
}