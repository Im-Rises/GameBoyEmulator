#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;
uint8_t GameBoy::inputs = 0b00111111;
bool GameBoy::pause = false;

GameBoy::GameBoy() :cpu(&memory, &ppu), ppu(&memory)
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
		cerr << "Initialization failed" << endl;
		exit(1);
	}

	glfwSetErrorCallback(error_callback);//Set callback error function

	GLFWwindow* window = glfwCreateWindow(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, PROJECT_NAME, NULL, NULL);//Create a window

	if (!window)
	{
		cerr << "Window or OpenGL context creation failed" << endl;
		exit(1);
	}

	glfwSetKeyCallback(window, key_callback);//Set inputs Callback

	glfwMakeContextCurrent(window);//Make window current context

	//Init glew
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		exit(1);
	}

	int pixelSize = std::min(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y) / SCREEN_RESOLUTION_X;

	//glViewport(0, 0, SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, 250.0, 0, 250.0, 0, 0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	int cycles = 0;
	while (!glfwWindowShouldClose(window))//While window not closed
	{
		if (debug)
		{
			writeScreenToFile();
			writeAllTiles();
			debug = false;
		}

		auto start = std::chrono::high_resolution_clock::now();


		//Update screen


		//Write inputs to cpu that writes it to memory
		cpu.writeInputs(inputs);

		//Read one opcode
		cycles = cpu.doCycle();
		//cycles *= 4;


		//SwapBuffers
		//glfwSwapBuffers(window);

		//Get evenements
		glfwPollEvents();
		// operation to be timed ...

		auto finish = std::chrono::high_resolution_clock::now();

		//std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
	}

	glfwDestroyWindow(window);//Destroy window and context
	glfwTerminate();//Terminate GLFW
}


/*------------------------------------------GLFW FUNCTIONS--------------------------------*/

void GameBoy::error_callback(int error, const char* description)
{
	cerr << "Error: " << description << "\n" << endl;
}

void GameBoy::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Emulator controls
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		pause != pause;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		debug = true;
	}
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

void GameBoy::updateScreen()
{
	for (int y = 0; y < DOTS_NUMBER_Y; y++)
	{
		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			ppu.getLcdScreenPixel(x, y);
			//Get memory data
			//memory.read
		}
	}
}

void GameBoy::RenderGame()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//glRasterPos2i(-1, 1);
	//glPixelZoom(1, -1);
	//glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, ppu.lcdScreen);
}


/*-----------------------------------------DEBUG----------------------------------------------*/

bool GameBoy::debug = false;

void GameBoy::writeScreenToFile()
{
	string const nomFichier("screenDebug.txt");
	ofstream monFlux(nomFichier.c_str());

	if (monFlux)
	{
		for (int i = 0; i < 144; i++)
		{
			for (int j = 0; j < 160; j++)
			{
				monFlux << (int)ppu.getLcdScreenPixel(j, i) << " ";
			}
			monFlux << endl;
		}
		cout << "Debug file created" << endl;
	}
	else
	{
		cout << "Error debug file not created." << endl;
	}

}

void GameBoy::writeAllTiles()
{
	string const nomFichier("tilesDebug.txt");
	ofstream monFlux(nomFichier.c_str());

	if (monFlux)
	{
		for (int i = 0; i < 0x2000; i++)
		{
			uint8_t line1 = memory.read(i + 0x8000);
			uint8_t line2 = memory.read(i + 1 + 0x8000);
			i++;

			for (int j = 0; j < 16; j++)
			{
				uint8_t bitLine1 = getBit(line1, j);
				uint8_t bitLine2 = getBit(line2, j);
				monFlux << (bitLine1 + (bitLine2 << 1));
			}

			monFlux << endl;
			if (!(((i + 1) % 16) > 0))
				monFlux << endl;
		}
		cout << "Debug file created" << endl;
	}
	else
	{
		cout << "Error debug file not created." << endl;
	}

}

uint8_t GameBoy::getBit(uint8_t byte, int bitIndex)
{
	return ((byte & (0b00000001 << bitIndex)) >> bitIndex);
}