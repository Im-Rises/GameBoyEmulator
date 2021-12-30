#ifndef GLFWOPENGLLIB
#define GLFWOPENGLLIB

#include <iostream>

#include "glew/include/GL/glew.h"
#include "GLFW/include/glfw3.h"

using namespace std;

class GlfwOpenglLib
{
private:
	GLFWwindow* window = nullptr;

public:
	GlfwOpenglLib(int width, int height, string title);


	/*------------------------------------------SCREEN METHODS--------------------------------*/

	void setBackground();
	void updateScreen();

	/*------------------------------------------CALLBACK METHODS--------------------------------*/

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif