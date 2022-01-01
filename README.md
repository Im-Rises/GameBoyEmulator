# GameBoyEmulator

GameBoy Emulator developped in C++ with Visual Studio 2019 using the GLFW and OpenGL libraries.

https://user-images.githubusercontent.com/59691442/147654838-0d3e11d2-5b09-46fa-ac63-f884d138ea05.mp4

## Console specifications

## Task order

1. CPU opcodes implementation
2. Interrupts
3. Controls
4. Video (PPU)
5. Audio

## Documentations  

Video overview of the Game Boy, to understand the fundamental:
<https://www.youtube.com/watch?v=HyzD8pNlpwI>  

Main documentation i used:
<https://archive.org/details/GameBoyProgManVer1.1/mode/2up>  
<https://gbdev.gg8.se/wiki/articles/Gameboy_Bootstrap_ROM>  
<https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html>

Helped me a lot to understand PPU timing and Rom/Ram banking:
<http://www.codeslinger.co.uk/pages/projects/gameboy/beginning.html>  ❤️  


## To do

Background is working, sprites also seem to work.
There's an issue with the Video register, in particulat LY (0xFF44) that is not incrememented like it should preventing the prog from leaving loop that are waiting for the last line of the screen from being drawn.
