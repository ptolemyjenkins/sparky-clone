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
		util::Logging::logPath = "./Log.txt";
		util::Logging::clearLog();
		this->app = app;
		if (isRunning) {
			app->setRenderingEngine(renderingEngine);
			return;
		}
		this->window = &graphics::Window(title, width, height);
		window->build();
		this->renderingEngine = new graphics::RenderingEngine();
		app->setRenderingEngine(renderingEngine);
		app->init();

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
				inputTimer.stopInvocation();

				updateTimer.startInvocation();
				app->update((float)frameTime);
				updateTimer.stopInvocation();

				if (frameCounter >= 1000000000) {
					accFrames = ((double)frames) / (double) (frameCounter / 1000000000.0);
					char frames_c_str[24];
					sprintf(frames_c_str, "%.2f", accFrames);
					std::string a = frames_c_str;
					util::Logging::log(a + " Fps--");
					unaccounted = totalTimer.displayAndReset(" Total:", accFrames);
					unaccounted -= inputTimer.displayAndReset(" Input:", accFrames);
					unaccounted -= updateTimer.displayAndReset(" Update:", accFrames);
					unaccounted -= renderTimer.displayAndReset(" Render:", accFrames);
					unaccounted -= windowTimer.displayAndReset(" Window:", accFrames);
					unaccounted -= sleepTimer.displayAndReset(" Sleep:", accFrames);
					sprintf(frames_c_str, "%.2f", unaccounted);
					a = frames_c_str;
					util::Logging::log(" Unaccounted: " + a + "\n");
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
		util::Logging::log("[Core Engine Terminated]");
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