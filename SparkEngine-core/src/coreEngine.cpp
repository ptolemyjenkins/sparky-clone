#include "coreEngine.h"


namespace sparky {
	CoreEngine::CoreEngine(char* title, const int& width, const int& height, const double& frameCap)
	{
		this->title = title;
		this->isRunning = false;
		this->width = width;
		this->height = height;
		this->frameTimeNano = (long long) (1000000000.0 / frameCap);
		this->frameTime = 1 / frameCap;
	}

	void CoreEngine::start(architecture::Application* app)
	{

		this->app = app;
		if (isRunning) {
			app->setRenderingEngine(renderingEngine);
			return;
		}
		this->renderingEngine = new graphics::RenderingEngine();
		app->setRenderingEngine(renderingEngine);
		this->window = &graphics::Window(title, width, height);
		window->build();
		run();
	}

	void CoreEngine::stop()
	{
		if (!isRunning)
			return;
		isRunning = false;
	}

	void CoreEngine::run()
	{
		isRunning = true;
		bool render;

		int frames = 0;
		long long frameCounter = 0;
		double accFrames = 0;
		double unaccounted = 0;
		app->init();
		renderingEngine->initShaders();
		long long lastTime = util::Time::getNanoTime();
		long long startTime;
		long long passedTime;
		long long unprocessedTime = 0;

		profiling::ProfileTimer totalTimer;
		profiling::ProfileTimer inputTimer;
		profiling::ProfileTimer updateTimer;
		profiling::ProfileTimer renderTimer;
		profiling::ProfileTimer windowTimer;
		profiling::ProfileTimer sleepTimer;
		while (isRunning) {
			totalTimer.startInvocation();
			render = false;
			
			startTime = util::Time::getNanoTime();
			passedTime = startTime - lastTime;
			lastTime = startTime;

			unprocessedTime += passedTime;
			frameCounter += passedTime;


			while (unprocessedTime > frameTimeNano) {
				render = true;
				unprocessedTime -= frameTimeNano;

				inputTimer.startInvocation();
				app->input((float)frameTime, window);
//_________________________________________________________________________
				if (window->isKeyDown(GLFW_KEY_ESCAPE) && window->isKeyDown(GLFW_KEY_LEFT_SHIFT))
					stop();
//_________________________________________________________________________
				inputTimer.stopInvocation();

				updateTimer.startInvocation();
				app->update((float)frameTime);
				updateTimer.stopInvocation();

				if (frameCounter >= 1000000000) {
					accFrames = ((double)frames) / (double) (frameCounter / 1000000000.0);
					printf("%.2f Fps--", accFrames);
					unaccounted = totalTimer.displayAndReset(" Total:", accFrames);
					unaccounted -= inputTimer.displayAndReset(" Input:", accFrames);
					unaccounted -= updateTimer.displayAndReset(" Update:", accFrames);
					unaccounted -= renderTimer.displayAndReset(" Render:", accFrames);
					unaccounted -= windowTimer.displayAndReset(" Window:", accFrames);
					unaccounted -= sleepTimer.displayAndReset(" Sleep:", accFrames);
					printf(" Unaccounted: %.2f\n", unaccounted);
					frames = 0;
					frameCounter = 0;
					unaccounted = 0;
				}
			}

			if (window->closed()) {
				stop();
			}

			if (render) {
				renderTimer.startInvocation();
				renderingEngine->render();
				renderTimer.stopInvocation();
				windowTimer.startInvocation();
				
				window->update();
				windowTimer.stopInvocation();
				frames++;
			}
			else {
				sleepTimer.startInvocation();
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				sleepTimer.stopInvocation();
			}
			totalTimer.stopInvocation();
			
		}
		delete renderingEngine;
		std::cout << "[Core Engine Terminated]" << std::endl;
	}

	graphics::RenderingEngine * CoreEngine::getRenderingEngine()
	{
		return renderingEngine;
	}

	architecture::Application * CoreEngine::getApplication()
	{
		return app;
	}

	graphics::Window * CoreEngine::getWindow()
	{
		return window;
	}
}