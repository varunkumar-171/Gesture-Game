/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

//#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "game_master.hpp"

int main ()
{

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	//SearchAndSetResourceDir("resources");

	InitWindow(screenWidth, screenHeight, static_cast<std::string>(title).c_str());
	InitAudioDevice();      // Initialize audio device

	GameMaster gameMaster;

	gameMaster.initSockets();
	gameMaster.initGame();
	gameMaster.gameLoop();
	return 0;
}
