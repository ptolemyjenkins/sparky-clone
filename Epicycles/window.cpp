#include "window.h"

void window_resize(GLFWwindow *window, int width, int height);

Window::Window(const char * title, int width, int height, bool resizable)
{
	m_Title = title;
	m_Width = width;
	m_Height = height;
	m_resizable = resizable;
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
	if (!init())
		glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
		std::cerr << "ERROR: glfw init failed" << std::endl;
	if(!m_resizable) glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window)
	{
		std::cerr << "ERROR: Failed to create GLFW Window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, mouse_position_callback);
	return true;
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

bool Window::closed() const
{
	return glfwWindowShouldClose(m_Window) == 1;
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::isKeyDown(unsigned int keycode) const
{
	if (keycode >= MAX_KEYS)
		return false;
	return m_KeysDown[keycode];
}

bool Window::isKeyPressed(unsigned int keycode)
{
	if (keycode >= MAX_KEYS)
		return false;
	bool pressed = m_KeysDown[keycode] && !m_LastKeysDown[keycode];
	if (pressed)
		m_LastKeysDown[keycode] = 1;
	return pressed;
}

bool Window::isKeyReleased(unsigned int keycode)
{
	if (keycode >= MAX_KEYS)
		return false;
  	bool released = !m_KeysDown[keycode] && m_LastKeysDown[keycode];
	if (released)
		m_LastKeysDown[keycode] = 0;
	return released;
}

void Window::keyUpdate(unsigned int keycode)
{
	if (keycode >= MAX_KEYS)
		return;
	if (m_KeysDown[keycode] && !m_LastKeysDown[keycode])
		m_LastKeysDown[keycode] = 1;
	if (!m_KeysDown[keycode] && m_LastKeysDown[keycode])
		m_LastKeysDown[keycode] = 0;
}

bool Window::isMouseButtonDown(unsigned int button) const
{
	if (button >= MAX_BUTTONS)
		return false;
	return m_MouseButtonsDown[button];
}

bool Window::isMouseButtonPressed(unsigned int button)
{
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

void window_resize(GLFWwindow *window, int width, int height)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Height = height;
	win->m_Width = width;
	glViewport(0, 0, width, height);
}