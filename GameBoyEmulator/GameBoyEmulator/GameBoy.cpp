#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;

GameBoy::GameBoy() :cpu(&memory)
{

}


GameBoy* GameBoy::getInstance()
{
	if (gameboyInstance == 0)
	{
		gameboyInstance = new GameBoy();
	}

	return gameboyInstance;
}

void GameBoy::reset()
{
	cpu.reset();
	memory.reset();
}

void GameBoy::loadBios(const string& biosPath)
{
	if (memory.loadBiosInMemory(biosPath) == false)
		exit(1);
}

void GameBoy::loadGame(const string& gamePath)
{
	if (memory.getBiosInMemeory())//If there is a bios
	{

	}
	else//If there's no bios
	{
		memory.loadRomInMemory(gamePath);
		//Set memory and CPU like after bios
	}
}

void GameBoy::launch()
{
	if (!glfwInit())//Init GLFW
	{
		cout << "Initialization failed" << endl;
		exit(1);
	}
	glfwSetErrorCallback(error_callback);//Set callback function
	GLFWwindow* window = glfwCreateWindow(640, 480, PROJECT_NAME, NULL, NULL);//Create a window
	if (!window)
	{
		cout << "Window or OpenGL context creation failed" << endl;
		exit(1);
	}
	glfwMakeContextCurrent(window);//Make wndow current context
	glfwSetKeyCallback(window, key_callback);//Set inputs Callback

	//gladLoadGL(glfwGetProcAddress);//Init openGL with Glad
	//int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	//glViewport(0, 0, width, height);

	int cycles = 0;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	//cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
	double test = cpu.getTimeCycle() * cycles;
	while (!glfwWindowShouldClose(window))//While window not closed
	{
		begin = chrono::steady_clock::now();
		//while ((cpu.getTimeCycle() * cycles) >= (end - begin).count())
		//{ }

		//Read one opcode
		cycles = cpu.doCycle();

		//Get inputs and send them to CPU
		//this->setinputes();

		//if (readInputs(window))

		//Update screen
		//updateScreen();
		//If escape button is pressed leave function

		glfwPollEvents();//Get evenements
		end = chrono::steady_clock::now();
	}
	glfwDestroyWindow(window);//Destroy window and context
	glfwTerminate();//Terminate GLFW
}

void GameBoy::updateScreen()
{
	for (int y = 0; y < DOTS_NUMBER_Y; y++)
	{
		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			//Get memory data
			//memory.read
		}
	}
}

/*------------------------------------------GLFW FUNCTIONS--------------------------------*/

void GameBoy::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void GameBoy::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}