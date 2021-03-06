# GameBoyEmulator

<p align="center">
      <img src="README_files/Logos/cmake_logo.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="README_files/Logos/SDL2_logo.png" alt="cmakeLogo" style="height:60px;"/>
</p>

## Description

Game Boy Emulator developed in C++ using SDL2.  
You can compile the program using CMake.  
Games like Pokémon aren't working due to the lack of MBC3/MBC5 cartridges implementation.

SDL2 website:
<https://www.libsdl.org>

> **Note**  
> C++ version 17  
> SDL2 version 2.0.14.

## Features

The Emulator features :

- Save-state
- Screenshots
- Different color modes
- Audio
- Xbox/PlayStation controller

## Images

| Tetris | Super Mario Land 2 |
| --- | --- |
| ![tetrisTitleScreen](https://user-images.githubusercontent.com/59691442/150528557-720e411d-2e16-4cc0-9817-167364169358.png) | ![marioLand2TitleScreen](https://user-images.githubusercontent.com/59691442/150528763-29bdaaf0-ca37-4a76-87d7-290d40da1065.png) |

| Kirby's Dream Land | The Legend of Zelda Link's Awakening |
| --- | --- |
| ![kirbyDreamLandTitleScreen](https://user-images.githubusercontent.com/59691442/150528769-c1abc87b-6fae-4989-9481-b69ba493fecc.png) | ![zeldaTitleScreen](https://user-images.githubusercontent.com/59691442/150528776-c72dec37-00a2-42eb-aa3c-4cea48577342.png) |

## Video

<https://user-images.githubusercontent.com/59691442/150530024-ac2dceee-1162-4894-bc44-334bbad2544f.mp4>

## Quickstart

To use the emulator it depends on your system. Please follow the steps in section `Windows` or `Linux`.

All the releases can be found in the link below:  
[Source code and releases](https://github.com/Im-Rises/GameBoyEmulator/releases)

You can download the emulator using clicking to the links below depending on your operating system.

### Windows

<a href="https://github.com/Im-Rises/GameBoyEmulator/releases/download/v0.8/GameBoyEmulator-0.8-windows.zip"><img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="cmakeLogo" style="height:40px;"/></a>

Once download make sure you have the sdl2.dll file next to the emulator .exe file), you can start the emulator by doing
a drag and drop of a rom to the .exe file, it will automatically start the game. You can also start the emulator by
typing the following command in your terminal.

```bash
./GameBoyEmulator.exe <romPath>
```

### Linux

<a href="https://github.com/Im-Rises/GameBoyEmulator/releases/download/v0.8/GameBoyEmulator-0.8-linux.zip"><img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="cmakeLogo" style="height:40px;"/></a>

Once download you'll need to install the `SDL2 library` by typing one of the following commands :

```shell
sudo apt-get install libsdl2-dev
```

or

```shell
sudo apt-get install libsdl2-2.0-0  
```

> **Warning**
> Depending on your Linux distribution the command to install SDL2 may change.

Once it's done, you can start the emulator by doing a drag and drop of a rom on the emulator file, or you can type the
following command:

```bash
./GameBoyEmulator.exe <romPath>
```

## Emulator controls

### Emulator interface

- F10 : Switch GameBoy color mode (GreenScale or Grayscale)

- F11 : Switch between Fullscreen and windowed mode

- Escape button/click cross to exit emulation

- Imp : Create a screenshot of the game in the folder next to tha app (screenshots/<gameName>)

- P : Pause emulation

- U : Increase emulator audio volume

- J : Decrease emulator audio volume

- B : create save-state

- N : load save-state

- Tab : restart game/emulator

### Use save states

To use a save-state press the B button on your keyboard, it will create a bmp image file named with the name of the game
and the extension .gb.state.bmp. To load it, just press the N on your keyboard to load it when the game is playing.

The save-state is a screenshot of the game, allowing you to know where you're going to resume the game if you use it.

### Screenshots feature

The emulator allow you to do screenshot of the game everytime. You can create one by pushing the IMP key on your
keyboard. The screenshots will be saved in the folder next to the Emulator `screenshots/<gameName>`.

### Emulator game controls

You can play games with your keyboard and also with Xbox or Playstation controller.

The controller must be connected before you start the emulator. The selected controller will Rumble for you to know
which controller has been selected (for PlayStation user the controller's led will be green).

| Console buttons | Emulator buttons | Xbox Controller | Playstation Controller |
|-----------------|------------------|-----------------|------------------------|
| A               | D                | B               | O                      |
| B               | S                | A               | X                      |
| Start           | Enter            | start           | options                |
| Select          | Space            | select          | share                  |
| ←               | ←                | arrow/joystick  | arrow/joystick         |
| →               | →                | arrow/joystick  | arrow/joystick         |
| ↓               | ↓                | arrow/joystick  | arrow/joystick         |
| ↑               | ↑                | arrow/joystick  | arrow/joystick         |

## Ini file

When you download/start the emulator you will get a GameBoyEmulator.ini file. This file allow you to change some
parameters about the emulator.

| Ini file setting | Description                     |
|------------------|---------------------------------|
| startBios        | load or not bios                |
| biosPath         | set boot-rom path               |
| width            | window width                    |
| height           | window height                   |
| colorMode        | change color mode (from 0 to 3) |

You can modify each of these parameters manually. To disable the bios load, put the value 0 in

Original .ini file:

```inifile
startBios='0'
biosPath='./dmg_boot.bin'
width='640'
height='576'
colorMode='0'
```

## Emulation color modes

| Zelda Link's Awakening in grayscale | Zelda Link's Awakening in greenscale |
|-------------------------------------|--------------------------------------|
|![zelda_grayscale](https://user-images.githubusercontent.com/59691442/179115301-a6d756c2-f519-459a-ab73-5dd16173e470.png)|![zelda_greenscale](https://user-images.githubusercontent.com/59691442/179115353-5f27ad9a-29df-45f9-82e4-feab011a58b4.png)|

## Compilation

Emulator is supported under Linux and Windows.  
The source code provide a CMakeList.txt file to compile the emulator.

You can download Cmake here:  
<https://cmake.org>

Linux's users need to install the developer version of SDL2 to compile the Emulator. To install it type the following
command in your terminal:

```shell
sudo apt-get install libsdl2-dev
```

## GitHub Actions

[![CMake](https://github.com/Im-Rises/GameBoyEmulator/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/GameBoyEmulator/actions/workflows/cmake.yml)

The repository has a GitHub Actions file to verify the good behaviour of the project before merging/pusing to the main
branch with a wrong code.

## Documentations

Cmake:  
<https://cmake.org>

SDL wiki:  
<https://wiki.libsdl.org>

Video overview of the Game Boy, to understand the fundamental:  
<https://www.youtube.com/watch?v=HyzD8pNlpwI>

The main documentation about the console:  
<https://archive.org/details/GameBoyProgManVer1.1/mode/2up>  
<https://gbdev.io/pandocs/Specifications.html>

The boot-rom:  
<https://gbdev.gg8.se/wiki/articles/Gameboy_Bootstrap_ROM>

Opcodes map:  
<https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html>

Rom/Ram banking:  
<http://www.codeslinger.co.uk/pages/projects/gameboy/beginning.html>

PPU:  
<https://hacktixme.ga/GBEDG/ppu/>

SPU:  
<https://nightshade256.github.io/2021/03/27/gb-sound-emulation.html>  
<https://emudev.de>  
<https://www.youtube.com/watch?v=a52p6ji1WZs>

Audio and sound:  
<https://xiph.org/video/vid1.shtml>

Test roms i use to debug my emulator:  
<https://gbdev.gg8.se/files/roms/blargg-gb-tests/>  
<https://github.com/mattcurrie/dmg-acid2>

Automatic-Releases script:  
<https://github.com/marvinpinto/action-automatic-releases>

Other docs (mostly about emulation in general):  
<https://emudev.org>    
<http://emulator101.com/>

## Contributors

Quentin MOREL :

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/GameBoyEmulator)](https://github.com/Im-Rises/GameBoyEmulator/graphs/contributors)
