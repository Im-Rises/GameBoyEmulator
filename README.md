# GameBoyEmulator

<p align="center">
      <img src="README_files/Logos/cmake_logo.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="README_files/Logos/SDL2_logo.png" alt="cmakeLogo" style="height:60px;"/>
</p>

## Description

GameBoy Emulator developped in C++ using SDL2.  
You can compile the program using CMake.
As of now there is no audio implemented.  
Games like pokemon aren't working due to the lack of MBC3/MBC5 cartridges implementation.  

SDL2 website:
<https://www.libsdl.org>

## Images

| Tetris | Super Mario Land 2 |
| --- | --- |
| ![tetrisTitleScreen](https://user-images.githubusercontent.com/59691442/150528557-720e411d-2e16-4cc0-9817-167364169358.png) | ![marioLand2TitleScreen](https://user-images.githubusercontent.com/59691442/150528763-29bdaaf0-ca37-4a76-87d7-290d40da1065.png) |

| Kirby's Dream Land | The Legend of Zelda Link's Awakening |
| --- | --- |
| ![kirbyDreamLandTitleScreen](https://user-images.githubusercontent.com/59691442/150528769-c1abc87b-6fae-4989-9481-b69ba493fecc.png) | ![zeldaTitleScreen](https://user-images.githubusercontent.com/59691442/150528776-c72dec37-00a2-42eb-aa3c-4cea48577342.png) |

## Video  

<https://user-images.githubusercontent.com/59691442/150530024-ac2dceee-1162-4894-bc44-334bbad2544f.mp4>

## Releases/Downloads

[Source code and releases](https://github.com/Im-Rises/GameBoyEmulator/releases)

Links :

### Windows

<a href="https://github.com/Im-Rises/GameBoyEmulator/files/7921719/GameBoyEmulator-0.6-windows.zip"><img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="cmakeLogo" style="height:40px;"/></a>

### Linux

<a href="https://github.com/Im-Rises/GameBoyEmulator/files/7921720/GameBoyEmulator-0.6-linux.zip"><img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="cmakeLogo" style="height:40px;"/></a>

## Compilation  

Emulator is supported under Linux and Windows.  
The source code provide a CMakeList.txt file to compile the emulator.  

- For windows users, you just need the SDL2.dll to run the program once it is compiled. You can find it in the release files or you can donwload it on the official SDL2 website.

- For linux users, you need to install the SDL2 package to run the emulator. You can install it by writting the following command.  

```shell
sudo apt-get install libsdl2-dev
```

## Start the emulator

To launch a game on Linux or Windows, you need to use a console and write the following command:

- GameBoyEmulator \<gameFilePath\>

You can also proceed by doing a drag and drop of the game file to the emulator executable.

On Linux you need SDL2 to start the emulator. You can install it by writing one of the two commands below:

Be carefull, **depending of your Linux distribution, the name of library can vary!**  

```shell
sudo apt-get install libsdl2-dev
```

```shell
sudo apt-get install libsdl2-2.0-0  
```

## Emulator controls

### Emulator interface

- F11 = Switch between Fullscreen and windowed mode

- Escape button/click cross to exit emulation

### Emulator game contols

|  Console buttons  | Emulator buttons   |
|--- |--- |
| A  | D  |
| B  | S  |
| Start   | Enter |
| Select  | Space |
| ←  | ←  |
| →  | →  |
| ↓  | ↓  |
| ↑  | ↑  |

## Documentations  

Video overview of the Game Boy, to understand the fundamental  
<https://www.youtube.com/watch?v=HyzD8pNlpwI>  

The main documentation about the console:  
<https://archive.org/details/GameBoyProgManVer1.1/mode/2up>  
<https://gbdev.io/pandocs/Specifications.html>

The bootrom  
<https://gbdev.gg8.se/wiki/articles/Gameboy_Bootstrap_ROM>  

Opcodes map  
<https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html>  

Rom/Ram banking  
<http://www.codeslinger.co.uk/pages/projects/gameboy/beginning.html>  

PPU  
<https://hacktixme.ga/GBEDG/ppu/>  

SPU  
<https://nightshade256.github.io/2021/03/27/gb-sound-emulation.html>  

Test roms i use to debug my emulator  
<https://gbdev.gg8.se/files/roms/blargg-gb-tests/>  
<https://github.com/mattcurrie/dmg-acid2>  

Other docs (mostly about emulation in general)  
<https://emudev.org>  
<https://emudev.de>  
