#include <iostream>

#include "GameBoy.h"
#include "GLFW/include/glfw3.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	/*
	if (argc > 1)
	{
		string biosPath;
		string romPath;

		GameBoy gameBoy;

		if (true)//Debug
		{
			biosPath = "../../Bios_Games/dmg_boot.bin";
			romPath = "../../Bios_Games/Tetris.GB";
		}

		romPath = argv[1];

		//Open setting file to get bios if enable
		//If there is bios
		if (true)
		{
			gameBoy.loadBios(biosPath);
		}

		gameBoy.start();
	}
	*/





	if (!glfwInit())
	{
		std::cout << "not Working" << std::endl;
	}
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	glfwTerminate();

	return 0;
}