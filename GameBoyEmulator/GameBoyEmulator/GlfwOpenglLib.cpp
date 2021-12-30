#include "GlfwOpenglLib.h"

GlfwOpenglLib::GlfwOpenglLib(int width, int height, string title)
{
	/// <summary>
	/// Init GLFW and OpenGL window
	/// </summary>
	/// <param name="width">Width of the window</param>
	/// <param name="height">Height of the window</param>
	/// <param name="title">Title of the window</param>
	

	//Init screen parameters
	this->width = width;
	this->height = width;
	fullScreen = false;

	
	//INIT GLFW
	if (!glfwInit()) //Init GLFW
	{
		cerr << "Initialization failed" << endl;
		exit(1);
	}
	glfwSetErrorCallback(error_callback); //Set callback error function
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL); //Create a window
	if (!window)//Test window
	{
		cerr << "Window or OpenGL context creation failed" << endl;
		exit(1);
	}
	//glfwSetKeyCallback(window, key_callback); //Set inputs Callback
	glfwMakeContextCurrent(window); //Make window context current 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//Set call-back when changing window's dimensions


	//INIT GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW" << endl;
		exit(1);
	}

	glViewport(0, 0, width, height);//Set viewport
}

GlfwOpenglLib::~GlfwOpenglLib()
{
	glfwDestroyWindow(window); //Destroy window and context
	glfwTerminate();		   //Terminate GLFW
}


/*------------------------------------------GET EVENEMENTS--------------------------------*/
void GlfwOpenglLib::getEvenements()
{
	//Get evenements
	glfwPollEvents();
}

bool GlfwOpenglLib::windowIsActive()
{
	return !glfwWindowShouldClose(window);
}


/*------------------------------------------SCREEN METHODS--------------------------------*/
void GlfwOpenglLib::setBackground()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GlfwOpenglLib::toggleWindowedFullScreen()
{
	//glfwSetWindowMonitor(window);
}

void GlfwOpenglLib::drawRectangle(const float& pixelSize, const int& x, const int& y, const int& color)
{
	glBegin(GL_QUADS);//Draw a rectangle

	float yPos = +1.0f - y * pixelSize;//Begin drawing on the upper part of the screen
	float xPos = -1.0f + x * pixelSize;//Begin drawing from the left part of the screen

	glColor3f(color, color, color);//Set color

	//Draw points
	glVertex2f(xPos, yPos);
	glVertex2f(xPos + pixelSize, yPos);
	glVertex2f(xPos + pixelSize, yPos + pixelSize);
	glVertex2f(xPos, yPos + pixelSize);

	glEnd();//end drawing
}

void GlfwOpenglLib::updateScreen()
{
	glfwSwapBuffers(window);
}


/*------------------------------------------CALLBACK METHODS--------------------------------*/
void GlfwOpenglLib::error_callback(int error, const char* description)
{
	cerr << "Error: " << description << "\n" << endl;
}

void GlfwOpenglLib::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//setBackground(1);
	glViewport(0, 0, width, height);
}

//void GlfwOpenglLib::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	//Emulator controls
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//		pause != pause;
//	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
//	{
//		//debug = true;
//	}
//	//Game Boy controls
//	//0: Low signal (button pressed)
//	//1: High signal (button not pressed)
//	inputs = 0b00000000;
//
//	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) //Right
//		inputs |= 0b00010001;
//	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) //Left
//		inputs |= 0b00010010;
//	if (key == GLFW_KEY_UP && action == GLFW_PRESS) //Up
//		inputs |= 0b00010100;
//	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) //Down
//		inputs |= 0b00011000;
//	if (key == GLFW_KEY_A && action == GLFW_PRESS) //A
//		inputs |= 0b00100001;
//	if (key == GLFW_KEY_B && action == GLFW_PRESS) //B
//		inputs |= 0b00100010;
//	if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS) //Select
//		inputs |= 0b00100100;
//	if (key == GLFW_KEY_SLASH && action == GLFW_PRESS) //Start
//		inputs |= 0b00101000;
//
//	inputs = ~inputs;
//}
//

