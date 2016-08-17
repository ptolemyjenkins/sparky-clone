#include "window.h"
namespace sparky { namespace graphics {
	void window_resize(GLFWwindow *window, int width, int height);
	Window::Window(const char * title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_KeysDown[i] = false;
			m_LastKeysDown[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtonsDown[i] = false;
		}
	}
	void Window::build() {
		if (!init()) {
			glfwTerminate();
			exit(1);
		}
	}

	bool Window::init()
	{
		if (!glfwInit())
			util::Logging::log_exit("ERROR: glfw init failed", 1);
		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL/*glfwGetPrimaryMonitor()*/, NULL);
		if (!m_Window)
		{
			util::Logging::log("ERROR: Failed to create GLFW Window");
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, mouse_position_callback);
		glfwSwapInterval(0);
		if (glewInit() != GLEW_OK)
		{
			util::Logging::log_exit("ERROR: Glew failed to initialise",1);
			return false;
		}
		std::string glVendor = reinterpret_cast< char const * >(glGetString(GL_VENDOR));
		std::string glVersion = reinterpret_cast< char const * >(glGetString(GL_VERSION));
		std::string glRenderer = reinterpret_cast< char const * >(glGetString(GL_RENDERER));
		std::string glShaderVersion = reinterpret_cast< char const * >(glGetString(GL_SHADING_LANGUAGE_VERSION));
		//std::string glExtensions = reinterpret_cast< char const * >(glGetString(GL_EXTENSIONS));

		util::Logging::log(glVendor + " - " + glVersion + "\n");
		util::Logging::log(glRenderer + " - " + glShaderVersion + "\n");
		//util::Logging::log(glExtensions + "\n");
		return true;
	}
	
	void Window::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			util::Logging::log_exit("OpenGL Error: " + error ,1);

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1 || shouldClose;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::error()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			util::Logging::log_exit("OpenGL Error: " + error, 1);
	}

	//input handling
	bool Window::isKeyDown(unsigned int keycode) const
	{
		// TODO: Log this...
		if (keycode >= MAX_KEYS)
			return false;
		return m_KeysDown[keycode];
	}

	bool Window::isKeyPressed(unsigned int keycode)
	{
		// TODO: Log this...
		if (keycode >= MAX_KEYS)
			return false;
		bool pressed = m_KeysDown[keycode] && !m_LastKeysDown[keycode];
		if (pressed)
			m_LastKeysDown[keycode] = 1;
		else if (!m_KeysDown[keycode] && m_LastKeysDown[keycode])
			m_LastKeysDown[keycode] = 0;
		return pressed;
	}

	bool Window::isMouseButtonDown(unsigned int button) const
	{
		// TODO: Log this...
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseButtonsDown[button];
	}

	bool Window::isMouseButtonPressed(unsigned int button)
	{
		// TODO: Log this...
		if (button >= MAX_BUTTONS)
			return false;
		bool pressed = m_MouseButtonsDown[button] && !m_LastMouseButtonsDown[button];
		if (pressed)
			m_LastMouseButtonsDown[button] = 1;
		else if (!m_MouseButtonsDown[button] && m_LastMouseButtonsDown[button])
			m_LastMouseButtonsDown[button] = 0;
		return pressed;
	}

	void Window::getMousePosition(double& x, double& y) const
	{
		x = m_mx;
		y = m_my;
	}

	maths::vec2 Window::getMousePosition()
	{
		return maths::vec2((float) m_mx, (float) m_my);
	}

	void Window::setMousePosition(double x, double y)
	{
		glfwSetCursorPos(m_Window, x, y);
	}

	void Window::close()
	{
		shouldClose = true;
	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_KeysDown[key] = (action != GLFW_RELEASE);
	}
	
	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtonsDown[button] = action != GLFW_RELEASE;
	}
	void mouse_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mx = xpos;
		win->m_my = ypos;
	}


// Window Functions
	void window_resize(GLFWwindow *window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Height = height;
		win->m_Width = width;
		glViewport(0, 0, width, height);
	} 
} }