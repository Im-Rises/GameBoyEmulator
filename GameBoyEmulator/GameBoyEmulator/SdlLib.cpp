#include "SdlLib.h"

SdlLib::SdlLib(int width, int height, string title)
{
	windowTitle = title;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Error SDL init.\n" << SDL_GetError() << std::endl;
		stopSdl();
		exit(EXIT_FAILURE);
	}

	if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
	{
		std::cout << "Error window creation.\n" << SDL_GetError() << std::endl;
		stopSdl();
		exit(EXIT_FAILURE);
	}

	SDL_SetWindowTitle(window, title.c_str());

	running = true;

	pixelsSize = std::max(width, height) / 144;

	keystate = SDL_GetKeyboardState(NULL);//Get pointer to the state of all keys of the keayboard

	gameBoyInputs = 0b11111111;
}

SdlLib::~SdlLib()
{
	stopSdl();
}

void SdlLib::stopSdl()
{
	/*
	* Fonction d'arrêt de la SDL
	*/

	running = false;

	if (NULL != renderer)
	{
		SDL_DestroyRenderer(renderer);
	}

	if (NULL != window)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}

void SdlLib::drawSquare(const float& pixelSize, const int& x, const int& y, const int& color)
{
	SDL_Rect rect = { x * pixelsSize,y * pixelsSize, pixelsSize, pixelsSize };

	SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);

	SDL_RenderFillRect(renderer, &rect);
}

void SdlLib::renderPresent()
{
	SDL_RenderPresent(renderer);
}

uint8 SdlLib::readGameBoyInputs()
{
	SDL_PumpEvents();

	(keystate[SDL_SCANCODE_RIGHT]) ? gameBoyInputs = resetBit(gameBoyInputs, 0) : gameBoyInputs = setBit(gameBoyInputs, 0);
	(keystate[SDL_SCANCODE_LEFT]) ? gameBoyInputs = resetBit(gameBoyInputs, 1) : gameBoyInputs = setBit(gameBoyInputs, 1);
	(keystate[SDL_SCANCODE_UP]) ? gameBoyInputs = resetBit(gameBoyInputs, 2) : gameBoyInputs = setBit(gameBoyInputs, 2);
	(keystate[SDL_SCANCODE_DOWN]) ? gameBoyInputs = resetBit(gameBoyInputs, 3) : gameBoyInputs = setBit(gameBoyInputs, 3);
	(keystate[SDL_SCANCODE_D]) ? gameBoyInputs = resetBit(gameBoyInputs, 4) : gameBoyInputs = setBit(gameBoyInputs, 4);
	(keystate[SDL_SCANCODE_S]) ? gameBoyInputs = resetBit(gameBoyInputs, 5) : gameBoyInputs = setBit(gameBoyInputs, 5);
	(keystate[SDL_SCANCODE_SPACE]) ? gameBoyInputs = resetBit(gameBoyInputs, 6) : gameBoyInputs = setBit(gameBoyInputs, 6);
	(keystate[SDL_SCANCODE_RETURN]) ? gameBoyInputs = resetBit(gameBoyInputs, 7) : gameBoyInputs = setBit(gameBoyInputs, 7);

	return gameBoyInputs;
}


uint32 SdlLib::getTicks()
{
	return SDL_GetTicks();
}



bool SdlLib::readExitInputs()
{
	SDL_PollEvent(&event);

	//return !(event.type == SDL_QUIT) && !(event.key.keysym.sym == SDLK_ESCAPE);
	return !(event.type == SDL_QUIT);
}


bool SdlLib::isRunning()
{
	return running;
}

void SdlLib::setFps(const int fps)
{
	//string temp = windowTitle.;
	//SDL_SetWindowTitle(window, fps);
}