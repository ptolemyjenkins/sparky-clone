#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../maths/maths.h"
namespace sparky { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS 32
	class Window
	{
	private:
		friend struct GLFWwindow;
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_KeysDown[MAX_KEYS];
		bool m_LastKeysDown[MAX_KEYS];
		bool m_MouseButtonsDown[MAX_BUTTONS];
		bool m_LastMouseButtonsDown[MAX_BUTTONS];
		double m_mx, m_my;
	public:
		Window(const char *name, int width, int height);
		~Window();
		void build();
		bool closed() const;
		void update();

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		static void error();

		bool isKeyDown(unsigned int keycode) const;
		bool isKeyPressed(unsigned int keycode);
		bool isMouseButtonDown(unsigned int button) const;
		bool isMouseButtonPressed(unsigned int button);
		void getMousePosition(double& x, double& y) const;
		maths::vec2 getMousePosition();
		void setMousePosition(double x, double y);
	private:
		bool init();
		friend void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
		friend void mouse_position_callback(GLFWwindow * window, double xpos, double ypos);
		friend void window_resize(GLFWwindow *window, int width, int height);
	};	
} }