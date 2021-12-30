#ifndef GLFWOPENGLLIB
#define GLFWOPENGLLIB

#include <iostream>

#include "glew/include/GL/glew.h"
#include "GLFW/include/glfw3.h"

using namespace std;

/// <summary>
/// GLFW and OPENGL library to create window
/// </summary>

class GlfwOpenglLib
{
private:
	/*------------------------------------------WINDOW--------------------------------*/
	GLFWwindow* window = nullptr;
	int width;
	int height;
	bool fullScreen;

public:
	/*------------------------------------------CONSTRUCTOR AND DESTRUCTOR--------------------------------*/
	GlfwOpenglLib(int width, int height, string title);//Constructor
	~GlfwOpenglLib();//Destructor

	/*------------------------------------------GET EVENEMENTS--------------------------------*/
	void getEvenements();
	bool windowIsActive();

	/*------------------------------------------SCREEN METHODS--------------------------------*/

	void setBackground();
	void toggleWindowedFullScreen();
	void drawRectangle(const float& pixelSize, const int& x, const int& y, const int& color);
	void updateScreen();

	/*------------------------------------------CALLBACK METHODS--------------------------------*/

	static void error_callback(int error, const char* description);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

#endif