# CMakeList.txt : CMake project for GameBoyEmulator

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRCS main.cpp binaryLib/binaryLib.cpp IniLoader/IniLoader.cpp Cartridge.cpp Cpu.cpp GameBoy.cpp Joypad.cpp Memory.cpp Ppu.cpp  Spu.cpp)
set(HEADERS binaryLib/binaryLib.h IniLoader/IniLoader.h Cartridge.h Cpu.h GameBoy.h Joypad.h Memory.h Ppu.h  Spu.h)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})

if(WIN32)
	set(SDL2PATH ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2PATH}x64/SDL2.lib)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2PATH}x64/SDL2main.lib)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2PATH}x64/SDL2test.lib)
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2PATH}x86/SDL2.lib)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2PATH}x86/SDL2main.lib)
		target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2PATH}x86/SDL2test.lib)
	endif()
elseif(UNIX)
	find_package(SDL2 REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
else()
	message(FATAL_ERROR "OS not configured in CMakeLists.txt")
endif()


#[[
# add SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/NesEmulator/lib/cmake/SFML")
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
#]]

#set(SDL2_DIR "${CMAKE_SOURCE_DIR}/GameBoyEmulator/SDL2/include")

#[[
find_package(SDL2 REQUIRED)

if(WIN32)
	#set(SDL2_PATH $ENV{SDL2_PATH})
	set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/GameBoyEmulator/SDL2/lib")
	target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2test)
elseif(UNIX)
	target_link_libraries(${PROJECT_NAME} SDL2)
else()
	message(FATAL_ERROR "OS not configured in CMakeLists.txt")
endif()
#]]
