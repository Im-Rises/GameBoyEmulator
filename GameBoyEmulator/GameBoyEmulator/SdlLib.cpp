#include "SdlLib.h"

SdlLib::SdlLib(int windowWidth, int windowHeight, int numberPixelsX, int numberPixelsY, string title)
{
	windowTitle = title;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Error SDL video init.\n" << SDL_GetError() << std::endl;
		stopSdl();
		exit(EXIT_FAILURE);
	}

	if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
	{
		std::cout << "Error window creation.\n" << SDL_GetError() << std::endl;
		stopSdl();
		exit(EXIT_FAILURE);
	}


	SDL_SetWindowTitle(window, title.c_str());

	running = true;

	this->numberPixelsX = numberPixelsX;
	this->numberPixelsY = numberPixelsY;

	setPixelsSize(windowWidth, windowHeight);
	windowingWidth = windowWidth;
	windowingHeigth = windowHeight;

	//keystate = SDL_GetKeyboardState(NULL);//Get pointer to the state of all keys of the keayboard

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	//SDL_SetWindowResizable(window, SDL_TRUE);

	gameBoyInputs = 0b11111111;

	windowing = true;
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

void SdlLib::setPixelsSize(const int& width, const int& height)
{
	if (width > height)
	{
		pixelsSize = height / numberPixelsY;

		float pixelsSizeFloat = (float)height / numberPixelsY;

		if (pixelsSizeFloat > pixelsSize)
		{
			yOffset = (pixelsSizeFloat * numberPixelsY - pixelsSize * numberPixelsY) / 2;
		}
		else
		{
			yOffset = 0;
		}

		xOffset = (width - pixelsSize * numberPixelsX) / 2;
	}
	else
	{
		pixelsSize = width / numberPixelsX;

		float pixelsSizeFloat = (float)width / numberPixelsX;

		if (pixelsSizeFloat > pixelsSize)
		{
			xOffset = (pixelsSizeFloat * numberPixelsX - pixelsSize * numberPixelsX) / 2;
		}
		else
		{
			xOffset = 0;
		}

		yOffset = (height - pixelsSize * numberPixelsY) / 2;
	}

	//int numberPixelMaxXY = std::max(numberPixelsX, numberPixelsY);
	//pixelsSize = height / numberPixelMaxXY;
	//float pixelsSizeFloat = (float)height / numberPixelMaxXY;
	//yOffset = (height - pixelsSize * numberPixelsY) / 2;
	//xOffset = (width - pixelsSize * numberPixelsX) / 2;

	//cout << width << " " << height << " " << pixelsSize << endl;
	//cout << xOffset << " " << yOffset << endl;
}

void SdlLib::drawSquare(const int& x, const int& y, const int& color)
{
	//SDL_Rect rect = { x * pixelsSize,y * pixelsSize, pixelsSize, pixelsSize };
	SDL_Rect rect = { xOffset + x * pixelsSize,yOffset + y * pixelsSize, pixelsSize, pixelsSize };

	SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);

	SDL_RenderFillRect(renderer, &rect);
}

void SdlLib::renderPresent()
{
	SDL_RenderPresent(renderer);
}

//uint8 SdlLib::readGameBoyInputs()
//{
//	SDL_PumpEvents();
//
//	(keystate[SDL_SCANCODE_RIGHT]) ? gameBoyInputs = resetBit(gameBoyInputs, 0) : gameBoyInputs = setBit(gameBoyInputs, 0);
//	(keystate[SDL_SCANCODE_LEFT]) ? gameBoyInputs = resetBit(gameBoyInputs, 1) : gameBoyInputs = setBit(gameBoyInputs, 1);
//	(keystate[SDL_SCANCODE_UP]) ? gameBoyInputs = resetBit(gameBoyInputs, 2) : gameBoyInputs = setBit(gameBoyInputs, 2);
//	(keystate[SDL_SCANCODE_DOWN]) ? gameBoyInputs = resetBit(gameBoyInputs, 3) : gameBoyInputs = setBit(gameBoyInputs, 3);
//	(keystate[SDL_SCANCODE_D]) ? gameBoyInputs = resetBit(gameBoyInputs, 4) : gameBoyInputs = setBit(gameBoyInputs, 4);
//	(keystate[SDL_SCANCODE_S]) ? gameBoyInputs = resetBit(gameBoyInputs, 5) : gameBoyInputs = setBit(gameBoyInputs, 5);
//	(keystate[SDL_SCANCODE_SPACE]) ? gameBoyInputs = resetBit(gameBoyInputs, 6) : gameBoyInputs = setBit(gameBoyInputs, 6);
//	(keystate[SDL_SCANCODE_RETURN]) ? gameBoyInputs = resetBit(gameBoyInputs, 7) : gameBoyInputs = setBit(gameBoyInputs, 7);
//
//	return gameBoyInputs;
//}


uint32 SdlLib::getTicks()
{
	return SDL_GetTicks();
}



bool SdlLib::readEmulatorInputs()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_F11)
			toggleFullScreen();

		//Cause issue in linux by closing window instantly
		//if (event.key.keysym.sym == SDLK_ESCAPE)//Exit on Escape press
		//	return false;
	}
	return !(event.type == SDL_QUIT);
}


bool SdlLib::isRunning()
{
	return running;
}

void SdlLib::setFps(const int fps)
{
	string temp = windowTitle + " (fps : " + to_string(fps).c_str() + ")";
	SDL_SetWindowTitle(window, temp.c_str());
}

void SdlLib::toggleFullScreen()
{
	if (windowing)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, windowingWidth, windowingHeigth);//This line is needed for linux to reset correctly the dimensions of the screen
	}

	setPixelsSize(SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h);

	windowing = !windowing;
}