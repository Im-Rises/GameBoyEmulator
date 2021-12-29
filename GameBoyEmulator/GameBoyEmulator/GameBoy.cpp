#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;
uint8_t GameBoy::inputs = 0b00111111;
bool GameBoy::pause = false;

GameBoy::GameBoy() : cpu(&memory, &ppu), ppu(&memory)
{
	fullScreen = FULL_SCREEN;
	useSaveFile = USE_SAVE_FILE;
	pause = false;
	fullSpeed = false;
	pixelSize = 2.0f / (float)DOTS_DISPLAY_X;
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
	ppu.reset();
}

void GameBoy::loadBios(const string& biosPath)
{
	if (memory.loadBiosInMemory(biosPath) == false)
		exit(1);
}

void GameBoy::loadGame(const string& gamePath)
{
	if (memory.getBiosInMemeory()) //If there is a bios
	{
		memory.loadRomInMemory(gamePath, 0x100);
	}
	else //If there's no bios
	{
		memory.loadRomInMemory(gamePath, 0);
		//Set memory and CPU like after bios
	}
}

void GameBoy::launch()
{
	/// <summary>
	/// GLFW initialisation
	/// </summary>
	if (!glfwInit()) //Init GLFW
	{
		cerr << "Initialization failed" << endl;
		exit(1);
	}

	glfwSetErrorCallback(error_callback); //Set callback error function

	GLFWwindow* window = glfwCreateWindow(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, PROJECT_NAME, NULL, NULL); //Create a window

	if (!window)
	{
		cerr << "Window or OpenGL context creation failed" << endl;
		exit(1);
	}

	glfwSetKeyCallback(window, key_callback); //Set inputs Callback

	glfwMakeContextCurrent(window); //Make window current context

	//Init glew
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW" << endl;
		exit(1);
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//Set call-back when changing window's dimensions

	glViewport(0, 0, EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y);

	//Set the background of the two buffers to white
	setBackground(window);

	float timeRefresh = 1.0f / SCREEN_FREQUENCY;
	int timeRefreshInt = timeRefresh * 1000;
	auto timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
	auto timeRefresthScreenFinish = std::chrono::high_resolution_clock::now();

	auto timeCpuStart = std::chrono::high_resolution_clock::now();
	auto timeCpuFinish = std::chrono::high_resolution_clock::now();
	double timeCycle = (1.0 / CPU_FREQUENCY_NORMAL_MODE) * 1000000000; //time of a cyle in nanoseconds
	int cycles = 0;													   //Machine cycle for the precedent operation

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		//execute bios until its end. Once done replace the memory from 0 to 0x100 by the cartridge
		//for (int i = 0; i < 0x100; i++)
		//{

		//}
	}
	else
	{
		//cpu.setPc(ROM_DATA_AREA);
		//cpu.setCpuWithoutBios();
		//memory.setMemoryWithoutBios();
	}

	if (useSaveFile && cpu.getPc() == 0x100) //Once game is launching put save into ram
	{
		loadSaveGame();
	}

	while (!glfwWindowShouldClose(window)) //While window not closed
	{
		//Debug
		if (true)
		{
			if (debug)
			{
				writeScreenToFile();
				writeAllTiles();
				debug = false;
			}

			//if (cpu.getPc() == 0x00E9)
			//{
			//	writeScreenToFile();
			//	writeAllTiles();
			//	cerr << "Security block game" << endl;
			//}
		}

		//Write inputs to cpu that writes it to memory
		timeCpuFinish = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::nanoseconds>(timeCpuFinish - timeCpuStart).count() > (cycles * timeCycle))
		{
			cpu.writeInputs(inputs);
			timeCpuStart = std::chrono::high_resolution_clock::now();
			cycles = cpu.doCycle();
		}

		//Update screen
		timeRefresthScreenFinish = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeRefresthScreenFinish - timeRefresthScreenStart).count() > timeRefreshInt)
		{
			updateScreen();
			glfwSwapBuffers(window);
			timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
		}

		//Get evenements
		glfwPollEvents();
	}

	glfwDestroyWindow(window); //Destroy window and context
	glfwTerminate();		   //Terminate GLFW
}

/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/

void GameBoy::updateScreen()
{
	//float rectangleSize = 2.0f / (float)DOTS_DISPLAY_X;
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

uint8_t GameBoy::colorToRGB(uint8_t colorGameBoy)
{
	switch (colorGameBoy)
	{
	case (0b00):
	{
		return 0xFF;
		break;
	}
	case (0b01):
	{
		return 0xCC;
		break;
	}
	case (0b10):
	{
		return 0x77;
		break;
	}
	case (0b11):
	{
		return 0x00;
		break;
	}
	default:
		cerr << "Error wrong data color";
		exit(1);
		break;
	}
}

/*------------------------------------------CALLBACK FUNCTIONS--------------------------------*/

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

void GameBoy::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	setBackground(window);
	glViewport(0, 0, width, height);
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
	return (byte >> bitIndex) & 0x1;
}

/*------------------------------------------SAVESTATE AND SAVEFILE--------------------------------*/

void GameBoy::writeSaveGame()
{
	string fileLocation = "test.gb";
	fileLocation = fileLocation.substr(0, fileLocation.find('.')) + ".sav";
	ofstream monFlux(fileLocation.c_str());

	if (monFlux)
	{
		for (int i = 0; i < 0x2000; i++)
		{
			monFlux << memory.read(ETERNAL_EXPANSION_WORKING_RAM + i) << endl;
		}
		cout << "Save file created" << endl;
	}
	else
	{
		cout << "Error save file not created." << endl;
	}
}

void GameBoy::loadSaveGame()
{
	string fileLocation = "test.gb";
	//fileLocation.sub
	ifstream monFlux(fileLocation.c_str());

	if (monFlux)
	{
		uint8_t line;
		for (int i = 0; i < 0x2000; i++)
		{
			monFlux >> line;
			//memory.write(ETERNAL_EXPANSION_WORKING_RAM + i, );
		}
		cout << "Save file loaded" << endl;
	}
	else
	{
		cout << "Error save file not loaded" << endl;
	}
}

void GameBoy::writeSaveState()
{
	//cpu.dump();
	//memory.dump;
	//Write data to file
}

void GameBoy::loadSaveState()
{
	//Read savestate
	//Set every data
}


/*------------------------------------------OPENGL FUNCTIONS--------------------------------*/

void GameBoy::setBackground(GLFWwindow* window)
{
	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}