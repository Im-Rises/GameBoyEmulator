#include <iostream>

#include "Cpu.h"

#include "GLFW/include/glfw3.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	//string biosPath = "../../Bios_Games/dmg_boot.bin";
	//string romPathDebug = "../../Bios_Games/Tetris.GB";	
	//Cpu cpu(biosPath);
	//cpu.start();
	//cpu.loadRom(romPathDebug);
	//cpu.start();

	if (!glfwInit())
	{
		cout << "not Working" << endl;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	glfwTerminate();

	return 0;
}