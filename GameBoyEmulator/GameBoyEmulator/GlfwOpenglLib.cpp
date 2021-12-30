#include "GlfwOpenglLib.h"

GlfwOpenglLib::GlfwOpenglLib(int width, int height, string title)
{
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

	glfwSetKeyCallback(window, key_callback); //Set inputs Callback

	glfwMakeContextCurrent(window); //Make window context current 

	//Init glew
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW" << endl;
		exit(1);
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//Set call-back when changing window's dimensions

	glViewport(0, 0, width, height);

	//Set the background of the two buffers to white
	setBackground();
}


/*------------------------------------------SCREEN METHODS--------------------------------*/

void GlfwOpenglLib::setBackground()
{
	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GlfwOpenglLib::updateScreen()
{
	float rectangleSize = pixelSize;

	glBegin(GL_QUADS);
	for (int y = 0; y < DOTS_DISPLAY_Y; y++)
	{
		float yPos = +1.0f - y * rectangleSize;//Begin drawing on the upper part of the screen

		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			float xPos = -1.0f + x * rectangleSize;//Begin drawing from the left part of the screen

			float color = (float)colorToRGB(ppu.getLcdScreenPixel(x, y)) / (float)255;
			glColor3f(color, color, color);

			glVertex2f(xPos, yPos);
			glVertex2f(xPos + rectangleSize, yPos);
			glVertex2f(xPos + rectangleSize, yPos + rectangleSize);
			glVertex2f(xPos, yPos + rectangleSize);
		}
	}
	glEnd();
}


/*------------------------------------------CALLBACK METHODS--------------------------------*/

void GlfwOpenglLib::error_callback(int error, const char* description)
{
	cerr << "Error: " << description << "\n" << endl;
}

void GlfwOpenglLib::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Emulator controls
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		pause != pause;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		//debug = true;
	}
	//Game Boy controls
	//0: Low signal (button pressed)
	//1: High signal (button not pressed)
	inputs = 0b00000000;

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) //Right
		inputs |= 0b00010001;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) //Left
		inputs |= 0b00010010;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) //Up
		inputs |= 0b00010100;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) //Down
		inputs |= 0b00011000;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) //A
		inputs |= 0b00100001;
	if (key == GLFW_KEY_B && action == GLFW_PRESS) //B
		inputs |= 0b00100010;
	if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS) //Select
		inputs |= 0b00100100;
	if (key == GLFW_KEY_SLASH && action == GLFW_PRESS) //Start
		inputs |= 0b00101000;

	inputs = ~inputs;
}

void GlfwOpenglLib::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	setBackground();
	glViewport(0, 0, width, height);
}