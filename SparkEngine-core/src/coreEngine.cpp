#include "coreEngine.h"

namespace sparky {
	CoreEngine::CoreEngine(char* title, architecture::Application* app, const int& width, const int& height, const double& frameCap)
	{
		this->title = title;
		this->isRunning = false;
		this->app = app;
		app->engine = this;
		this->width = width;
		this->height = height;
		this->frameTimeNano = (long long) (1000000000.0 / frameCap);
		this->frameTime = 1 / frameCap;
	}

	void CoreEngine::start(graphics::RenderingEngine* rendering)
	{
		this->renderingEngine = rendering;
		if (isRunning)
			return;
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
//TEMP________________________________________________________________________________________________________________________________________
		graphics::Shader shader("basic","res/shaders/basic.vert", "res/shaders/basic.frag");
		shader.bind();
		GLfloat vertices[] =
		{
			-4, -2.31f, 0,
			0,  4.62f, 0,
			4, -2.31f, 0
		};
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		maths::mat4 ortho = maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 16.0f, -8.0f, 8.0f);
		maths::mat4 persp = maths::mat4::perspective(1.22173f, (float)window->getWidth() / (float)window->getHeight(), 0.1f, 1000);
		shader.setUniformMat4("pr_matrix", ortho);
		shader.setUniformMat4("vw_matrix", maths::mat4::translation(maths::vec3(8, 8, 0)));
		maths::quaternion rotation(maths::vec3(0, 0, 1), 0);
		maths::quaternion rota(maths::vec3(0, 0, 1), 1);
		maths::quaternion rotb(maths::vec3(1, 1, 0), 2);
		maths::vec4 colour;
		float test = 0;

//____________________________________________________________________________________________________________________________________________
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
				app->input((float)frameTime);
				if (window->isKeyPressed(GLFW_KEY_L))
					stop();
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
				renderingEngine->render(app->render());
//TEMP___________________________________________________________________________________________________________________________________________
				rotation *= (rotb * rota);
				test += 0.01f;
				shader.setUniform2f("light_pos", maths::vec2(3 * cos(-test * 4), 3 * sin(-test * 4)));
				colour.set(pow(cos(test), 2), pow(sin(test + test / 2), 2), pow(sin(test + 2), 2), 1);
				shader.setUniform4f("col", colour);
				shader.setUniformMat4("ml_matrix", rotation.toRotationMatrix());
				glDrawArrays(GL_TRIANGLES, 0, 3);
//_______________________________________________________________________________________________________________________________________________
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
}