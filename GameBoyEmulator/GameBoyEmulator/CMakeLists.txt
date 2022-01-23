# CMakeList.txt : CMake project for GameBoyEmulator

cmake_minimum_required (VERSION 3.8)

set(SRCS main.cpp binaryLib.cpp Cartridge.cpp Cpu.cpp GameBoy.cpp Joypad.cpp Memory.cpp Ppu.cpp SdlLib.cpp Spu.cpp)

set(HEADERS binaryLib.h Cartridge.h Cpu.h GameBoy.h Joypad.h Memory.h Ppu.h SdlLib.h Spu.h)

add_executable(GameBoyEmulator ${SRCS} ${HEADERS})

if(WIN32)
	target_link_libraries(GameBoyEmulator ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib) # Use static lib to compile program
	target_link_libraries(GameBoyEmulator ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2main.lib)
	target_link_libraries(GameBoyEmulator ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2test.lib)
elseif(UNIX)
	# for linux, you need to install the SDL2 package; <sudo apt-get install libsdl2-dev>
	find_package(SDL2 REQUIRED) # Find SDL2 package
	target_link_libraries(GameBoyEmulator PUBLIC SDL2.so) # Use SDL2 linux's package
else()
	message(FATAL_ERROR "OS not configured in CMakeLists.txt")
endif()

target_compile_features(GameBoyEmulator PUBLIC cxx_nullptr) # Implement nullptr if compiler does not
