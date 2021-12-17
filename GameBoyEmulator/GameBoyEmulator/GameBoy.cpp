#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;
uint8_t GameBoy::inputs = 0b00111111;
bool GameBoy::pause = false;

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
	/// <summary>
	/// GLFW initialisation
	/// </summary>
	if (!glfwInit())//Init GLFW
	{
		cout << "Initialization failed" << endl;
		exit(1);
	}
	glfwSetErrorCallback(error_callback);//Set callback function
	GLFWwindow* window = glfwCreateWindow(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, PROJECT_NAME, NULL, NULL);//Create a window
	if (!window)
	{
		cout << "Window or OpenGL context creation failed" << endl;
		exit(1);
	}
	glfwMakeContextCurrent(window);//Make window current context
	glfwSetKeyCallback(window, key_callback);//Set inputs Callback

	/// <summary>
	/// OpenGL initialisation
	/// </summary>
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(1);
	}


	/// <summary>
	/// Cycles
	/// </summary>
	int cycles = 0;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	//cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
	double test = cpu.getTimeCycle() * cycles;
	while (!glfwWindowShouldClose(window))//While window not closed
	{
		begin = chrono::steady_clock::now();
		//while ((cpu.getTimeCycle() * cycles) >= (end - begin).count())
		//{ 
		// glfwPollEvents();//Get evenements
		//}

		//Write inputs to cpu that write it to memory
		cpu.writeInputs(inputs);

		//Read one opcode
		cycles = cpu.doCycle();

		//Update screen
		//updateScreen();

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
	//Emulator controls
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		pause != pause;

	//Game Boy controls
	//0: Low signal (button pressed)
	//1: High signal (button not pressed)
	inputs = 0b00000000;

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)//Right
		inputs |= 0b00010001;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)//Left
		inputs |= 0b00010010;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)//Up
		inputs |= 0b00010100;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)//Down
		inputs |= 0b00011000;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)//A
		inputs |= 0b00100001;
	if (key == GLFW_KEY_B && action == GLFW_PRESS)//B
		inputs |= 0b00100010;
	if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS)//Select
		inputs |= 0b00100100;
	if (key == GLFW_KEY_SLASH && action == GLFW_PRESS)//Start
		inputs |= 0b00101000;

	inputs = ~inputs;
}


/*-----------------------------------------OPENGL FUNCTIONS----------------------------------------------*/
