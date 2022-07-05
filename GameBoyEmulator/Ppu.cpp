#include "Ppu.h"

#include <iostream>
#include <string>

#include "SDL2/include/SDL.h"

Ppu::Ppu(Memory* memory, ColorMode colorMode)
{
	currentColorMode = 0;

	int windowWidth = 640;
	int windowHeight = 576;

	// Connection to memory
	this->memory = memory;

	//GameBoy screen
	reset();
	setGameBoyColorMode(colorMode);

	//SDL

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Error SDL video init.\n" << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth,
	                          windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cerr << "Error window creation.\n" << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cerr << "Error renderer creation using hardware.\n" << SDL_GetError() << std::endl;
		std::cerr << "Use of software instead.\n" << SDL_GetError() << std::endl;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
		if (renderer == NULL)
		{
			std::cerr << "Error renderer creation using software.\n" << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << "Screen Software mode" << std::endl;
	}
	else
	{
		std::cout << "Screen Hardware mode" << std::endl;
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 160, 144);
	if (texture == NULL)
	{
		std::cerr << "Error texture creation.\n" << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Deactivate the controller reading while pooling events to prevent program from queuing to many inputs from controller's axis resulting in blocking the app from exiting
	// https://wiki.libsdl.org/SDL_EventState
	// Or not working so writing one line for one deactivation
	SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);

	SDL_EventState(SDL_CONTROLLERAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERBUTTONUP, SDL_IGNORE);

	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	windowing = true;
}

Ppu::~Ppu()
{
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);

	if (NULL != window)
		SDL_DestroyWindow(window);

	if (NULL != texture)
		SDL_DestroyTexture(texture);

	SDL_Quit();
}


/*-------------------------------------------------------------SDL window handling------------------------------------------------------------------------------*/

void Ppu::updateScreen()
{
	// Method 1:
	SDL_UpdateTexture(texture, NULL, lcd, 160 * 3);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	// // // Method 2: (https://wiki.libsdl.org/SDL_LockTexture)
	// int pitch = 160 * sizeof(uint8) * 3;
	// SDL_LockTexture(texture, NULL, (void**)&lcd, &pitch);
	// SDL_UnlockTexture(texture);
}

void Ppu::displayFramerate(const int& value) const
{
	string temp = windowTitle + " (fps : " + std::to_string(value).c_str() + ")";
	SDL_SetWindowTitle(window, temp.c_str());
}

bool Ppu::windowHandling()
{
	// bool myexit;
	static bool switchColorMode = false;
	static bool switchWindowMode = false;
	// static bool switchPause = false;

	if (SDL_PollEvent(&event))
		cout << "issue" << endl;

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_F11)
			switchWindowMode = true;

		if (event.key.keysym.sym == SDLK_F10)
			switchColorMode = true;

		// if (event.key.keysym.sym == SDLK_p)
		// 	switchPause = true;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_F11 && switchWindowMode)
		{
			switchWindowMode = false;
			toggleFullScreen();
		}

		if (event.key.keysym.sym == SDLK_F10 && switchColorMode)
		{
			switchColorMode = false;
			currentColorMode++;
			setGameBoyColorMode(currentColorMode);
		}

		// if (event.key.keysym.sym == SDLK_p && switchPause)
		// {
		// 	do
		// 	{
		// 		SDL_WaitEvent(&event);
		// 		string message;
		// 		switch (event.key.keysym.sym)
		// 		{
		// 		case(SDLK_p):
		// 			switchPause = false;
		// 			break;
		// 		case(SDLK_ESCAPE):
		// 			return false;
		// 		}
		//
		// 		if (event.type == SDL_QUIT)
		// 			return false;
		// 	}
		// 	while (switchPause);
		// }

		// myexit = !(event.key.keysym.sym == SDLK_ESCAPE);
		// cout << myexit << endl;
		// return myexit;
		return !(event.key.keysym.sym == SDLK_ESCAPE);
	}

	if (event.type==SDL_CONTROLLERAXISMOTION)
	{
		cout << "here de merde" << endl;
	}
	// myexit = !(event.type == SDL_QUIT);
	// cout << myexit << endl;
	// return myexit;
	return !(event.type == SDL_QUIT);
}

void Ppu::toggleFullScreen()
{
	if (windowing)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, windowingWidth, windowingHeigth);
		//This line is needed for linux to reset correctly the dimensions of the screen
	}

	windowing = !windowing;
}


/*-------------------------------------------------------------GAMEBOY screen emulation------------------------------------------------------------------------------*/

void Ppu::reset()
{
	for (int j = 0; j < DOTS_DISPLAY_Y; j++)
	{
		for (int i = 0; i < DOTS_DISPLAY_X; i++)
		{
			setPixel(i, j, 0xFF, 0xFF, 0xFF);

			lcdTransparent[(j * 160 * 3) + i] = false;
		}
	}
	scanLineCounter = 456; //Number of clock cycles to draw one scanline
	LY = LYC = 0;
}

void Ppu::setGameBoyColorMode(const int& colorMode)
{
	//GameBoy color mode
	switch (colorMode)
	{
	case(grayscaleReal):
		GameBoyColorMode.darkest = {0x00, 0x00, 0x00};
		GameBoyColorMode.dark = {0x77, 0x77, 0x77};
		GameBoyColorMode.light = {0xCC, 0xCC, 0xCC};
		GameBoyColorMode.lightest = {0xff, 0xff, 0xff};
		break;
	case(grayscaleNative):
		GameBoyColorMode.darkest = {0x00, 0x00, 0x00};
		GameBoyColorMode.dark = {0x55, 0x55, 0x55};
		GameBoyColorMode.light = {0xaa, 0xaa, 0xaa};
		GameBoyColorMode.lightest = {0xff, 0xff, 0xff};
		break;
	case(greenscaleReal):
		GameBoyColorMode.darkest = {0x0f, 0x38, 0x0f};
		GameBoyColorMode.dark = {0x30, 0x62, 0x30};
		GameBoyColorMode.light = {0x8b, 0xac, 0x0f};
		GameBoyColorMode.lightest = {0x9b, 0xbc, 0x0f};
		break;
	case(greenscaleNative):
		GameBoyColorMode.darkest = {0x40, 0x50, 0x10};
		GameBoyColorMode.dark = {0x70, 0x80, 0x28};
		GameBoyColorMode.light = {0xa0, 0xa8, 0x40};
		GameBoyColorMode.lightest = {0xd0, 0xd0, 0x58};
		break;
	// case(4): // Negative
	// 	GameBoyColorMode.darkest = { 0xe3,0xe6,0xc9 };
	// 	GameBoyColorMode.dark = { 0xc3,0xc4,0xa5 };
	// 	GameBoyColorMode.light = { 0x8e,0x8b,0x61 };
	// 	GameBoyColorMode.lightest = { 0x6c,0x6c,0x4e };
	// 	break;
	default:
		currentColorMode = 0;
		setGameBoyColorMode(0);
		break;
	}
}

void Ppu::setPixel(const int& x, const int& y, const uint8& r, const uint8& g, const uint8& b)
{
	lcd[(y * 160 * 3) + x * 3] = r;
	lcd[(y * 160 * 3) + x * 3 + 1] = g;
	lcd[(y * 160 * 3) + x * 3 + 2] = b;
}

void Ppu::draw(const int& cycles)
{
	//ERROR
	updateStatRegister();
	//ERRROR
	uint8 lcdc = memory->read(LCDC_ADDRESS);
	uint8 ly = memory->read(0xFF44);

	if (testBit(lcdc, 7))
	{
		scanLineCounter -= cycles;
	}

	if (ly > 153)
	{
		memory->write(0xFF44, 0);
	}

	if (scanLineCounter <= 0)
	{
		if (!testBit(lcdc, 7))
			return;

		memory->write(LY_ADDRESS, memory->read(LY_ADDRESS) + 1);
		uint8 scanLine = memory->read(LY_ADDRESS);
		scanLineCounter = 456;


		if (scanLine == 144)
			requestInterrupt(0);
		else if (scanLine > 153)
			memory->directWrite(LY_ADDRESS, 0);
		else if (scanLine < 144)
			drawLine();
	}
}

void Ppu::updateStatRegister()
{
	uint8 lcdc = memory->read(LCDC_ADDRESS);
	uint8 stat = memory->read(STAT_ADDRESS);

	if (!testBit(lcdc, 7)) //If LCD is disable reset it
	{
		scanLineCounter = 456;
		memory->directWrite(LY_ADDRESS, 0);
		stat &= 0b11111100;
		stat = setBit(stat, 0);
		memory->write(STAT_ADDRESS, stat);
	}
	else
	{
		uint8 scanLine = memory->read(LY_ADDRESS);
		uint8 currentMode = stat & 0b00000011;
		uint8 mode = 0;
		bool requestInterruptBool = 0;

		if (scanLine >= 144)
		{
			mode = 1;
			stat = setBit(stat, 0);
			stat = resetBit(stat, 1);
			requestInterruptBool = testBit(stat, 4);
		}
		else
		{
			int mode2bounds = 456 - 80;
			int mode3bounds = mode2bounds - 172;

			if (scanLineCounter >= mode2bounds)
			{
				mode = 2;
				stat = setBit(stat, 1);
				stat = resetBit(stat, 0);
				requestInterruptBool = testBit(stat, 5);
			}
			else if (scanLineCounter >= mode3bounds)
			{
				mode = 3;
				stat = setBit(stat, 1);
				stat = setBit(stat, 0);
			}
			else
			{
				mode = 0;
				stat = resetBit(stat, 1);
				stat = resetBit(stat, 0);
				requestInterruptBool = testBit(stat, 3);
			}
		}

		if (requestInterruptBool && (mode != currentMode))
		{
			requestInterrupt(1);
		}

		if ((LY != memory->read(LY_ADDRESS) || LYC != memory->read(LYC_ADDRESS)))
		//Check LY==LYC if LY or LYC have change since last time
		{
			if (scanLine == memory->read(LYC_ADDRESS))
			{
				stat = setBit(stat, 2);
				if (testBit(stat, 6))
				{
					requestInterrupt(1);
				}
			}
			else
			{
				stat = resetBit(stat, 2);
			}

			LY = memory->read(LY_ADDRESS);
			LYC = memory->read(LYC_ADDRESS);
		}


		memory->write(STAT_ADDRESS, stat);
	}
}

void Ppu::drawLine()
{
	uint8 lcdc = memory->read(LCDC_ADDRESS);
	drawBackgroundLine(lcdc);
	drawSpritesLine(lcdc);
}

void Ppu::drawBackgroundLine(const uint8& lcdc)
{
	uint8 scx = memory->read(SCX_ADDRESS);
	uint8 scy = memory->read(SCY_ADDRESS);
	uint8 wx = memory->read(WX_ADDRESS) - 7;
	uint8 wy = memory->read(WY_ADDRESS);

	uint8 ly = memory->read(LY_ADDRESS);

	bool windowing = false;

	uint16 tileDataArea;
	bool unsignedValue = true;

	uint16 backgroundMemoryCode;


	if (testBit(lcdc, 5) && wy <= ly)
		windowing = true;

	if (testBit(lcdc, 4)) //Get tile data address
	{
		tileDataArea = 0x8000;
		unsignedValue = true;
	}
	else
	{
		tileDataArea = 0x8800;
		unsignedValue = false;
	}

	if (windowing) //Get tile code address
	{
		if (testBit(lcdc, 6))
			backgroundMemoryCode = 0x9C00;
		else
			backgroundMemoryCode = 0x9800;
	}
	else
	{
		if (testBit(lcdc, 3))
			backgroundMemoryCode = 0x9C00;
		else
			backgroundMemoryCode = 0x9800;
	}

	uint8 yPos;
	if (windowing)
		yPos = ly - wy; //WHY THAT ?
	else
		yPos = scy + ly;

	uint16 tileRow = (yPos / 8) * 32; //Contains all precedents row 

	for (int pixel = 0; pixel < DOTS_DISPLAY_X; pixel++)
	{
		uint8 xPos = pixel + scx;

		if (windowing && pixel >= wx)
			xPos = pixel - wx; //Why that

		uint8 tileColumn = xPos / 8;

		int16_t tileNum; //Can be signed or unsigend depending of the tileDataArea

		if (unsignedValue)
			tileNum = (uint8)memory->read(backgroundMemoryCode + tileRow + tileColumn);
		else
			tileNum = (int8_t)memory->read(backgroundMemoryCode + tileRow + tileColumn);

		uint16 tileLocation;
		if (unsignedValue)
			tileLocation = tileDataArea + tileNum * 16;
		else
			tileLocation = tileDataArea + (tileNum + 128) * 16;

		uint8 line = (yPos % 8) * 2;
		uint8 dataLine1 = memory->read(tileLocation + line);
		uint8 dataLine2 = memory->read(tileLocation + line + 1);

		uint8 bitIndex = (((xPos % 8) - 7) * -1);
		uint8 colorCode = getBit(dataLine1, bitIndex) + (getBit(dataLine2, (bitIndex)) << 1);

		uint8 color = transformDotDataToColor(colorCode, BG_PALETTE_DATA);

		if (testBit(lcdc, 0))
		{
			auto colorRgb = colorToRGB(color);
			setPixel(pixel, ly, colorRgb.r, colorRgb.g, colorRgb.b);

			lcdTransparent[(ly * 160 * 3) + pixel] = (colorCode == 0);
		}
		else
		{
			uint8 color = transformDotDataToColor(0, BG_PALETTE_DATA);

			for (int pixel = 0; pixel < DOTS_DISPLAY_X; pixel++)
			{
				auto colorRgb = colorToRGB(color);
				setPixel(pixel, ly, colorRgb.r, colorRgb.g, colorRgb.b);
				lcdTransparent[(ly * 160 * 3) + pixel] = true;
			}
		}
	}
}

void Ppu::drawSpritesLine(const uint8& lcdc)
{
	if (testBit(lcdc, 1)) //if OBJ FLAG is ON
	{
		bool sprite8x16Dots = testBit(lcdc, 2); //0: 8 x 8 dots		1 : 8 x 16 dots

		int numberSpritesPerLine = 0;

		for (int i = 0; i < SPRITES_NUMBER; i++)
		{
			int index = i * 4; //Sprites data are composed of 4 bytes of data

			if (sprite8x16Dots)
				//if it is a 8x16 sprite than bit 0 is ignored to use the data of even obj not the odd part
				index &= 0b11111110;

			uint8 yCoordinate = memory->read(OAM_Y_COODINATE + index) - 16;
			//In the official documentation it is written 10 because it is in hexa 0x10 so 16 in decimal
			uint8 xCoordinate = memory->read(OAM_X_COODINATE + index) - 8;
			uint8 chrCode = memory->read(OAM_CHR_CODE + index);
			uint8 attributeFlag = memory->read(OAM_ATTRIBUTE_FLAG + index);

			bool horizontalFlip = testBit(attributeFlag, 5); //xFlip
			bool verticalFlip = testBit(attributeFlag, 6); //yFlip
			bool displayPriorityBG = testBit(attributeFlag, 7); //Display priority


			uint8 ly = memory->read(LY_ADDRESS);

			uint8 spriteSize = sprite8x16Dots ? 16 : 8;

			if ((ly >= yCoordinate) && (ly < (yCoordinate + spriteSize)))
			//Before drawing sprite, we verify if it is not out of screen
			{
				numberSpritesPerLine++;

				uint8 lineSprite = ly - yCoordinate;
				//Get line to draw depending if the sprite is flipped horizontally or vertically

				if (verticalFlip)
					lineSprite = (lineSprite - spriteSize) * -1;

				lineSprite *= 2;
				uint8 dataLine1 = memory->read(0x8000 + chrCode * 16 + lineSprite); //Data line 1
				uint8 dataLine2 = memory->read(0x8000 + chrCode * 16 + lineSprite + 1); //Data line 2

				for (int pixel = 0; pixel < 8; pixel++)
				{
					int pixelIndex = pixel;

					if (!horizontalFlip)
						pixelIndex = (pixelIndex - 7) * -1;

					uint8 colorCode = getBit(dataLine1, pixelIndex) + (getBit(dataLine2, (pixelIndex)) << 1);

					bool transparent = (colorCode == 0);

					//Another way would be to stock in the lcdScreen the colorCode
					int x = xCoordinate + pixel;
					if (0 <= x && x < 160)
					{
						//Following the priority p
						// if ((((!displayPriorityBG && !transparent) || (displayPriorityBG && !transparent && lcdScreen[x][ly].backgroundTransparent)) && (numberSpritesPerLine <= 10)))
						if ((((!displayPriorityBG && !transparent) || (displayPriorityBG && !transparent &&
							lcdTransparent[(ly * 160 * 3) + pixel])) && (numberSpritesPerLine <= 10)))
						{
							uint8 color;
							if (!testBit(attributeFlag, 4))
								color = transformDotDataToColor(colorCode, OPB0_PALETTE_DATA);
							else
								color = transformDotDataToColor(colorCode, OPB1_PALETTE_DATA);

							auto colorRgb = colorToRGB(color);
							setPixel(x, ly, colorRgb.r, colorRgb.g, colorRgb.b);
						}
						// else //Display BG' pixel
						// {
						// 	//if (ly >= 8 && ly <= 15)
						// 	//	cout << "test" << endl;
						// }
					}
				}
			}
		}
	}
}

uint8 Ppu::transformDotDataToColor(const uint8& dotData, const uint16& dataPaletteAddress)
{
	switch (dotData)
	{
	case(0b00):
		{
			return ((memory->read(dataPaletteAddress) & 0b00000011));
		}
	case(0b01):
		{
			return ((memory->read(dataPaletteAddress) & 0b00001100) >> 2);
		}
	case(0b10):
		{
			return ((memory->read(dataPaletteAddress) & 0b00110000) >> 4);
		}
	case(0b11):
		{
			return ((memory->read(dataPaletteAddress) & 0b11000000) >> 6);
		}
	default:
		cerr << "Error wrong data color code";
		exit(1);
	}
}

ColorRGB Ppu::colorToRGB(uint8 colorGameBoy)
{
	switch (colorGameBoy)
	{
	case (0b00):
		{
			return GameBoyColorMode.lightest;
		}
	case (0b01):
		{
			return GameBoyColorMode.light;
		}
	case (0b10):
		{
			return GameBoyColorMode.dark;
		}
	case (0b11):
		{
			return GameBoyColorMode.darkest;
		}
	default:
		cerr << "Error wrong data color";
		exit(1);
	}
}

void Ppu::requestInterrupt(const uint8& bitIndex)
{
	uint8 ifRegister = memory->read(INTERRUPT_FLAG_IF_ADDRESS);
	ifRegister = setBit(ifRegister, bitIndex);
	memory->write(INTERRUPT_FLAG_IF_ADDRESS, ifRegister);
}

bool Ppu::checkLyEqualsLyc()
{
	return (memory->read(LY_ADDRESS) == memory->read(LYC_ADDRESS));
}
