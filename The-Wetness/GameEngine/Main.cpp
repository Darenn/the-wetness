/// \file       Main.cpp
/// \date       08/10/2017
/// \package    None
/// \author     Vincent STEHLY--CALISTO

#include "GameEngine.hpp"

/// \brief	Game entry point
///			Command line helper
///			-d 0 Disables debug mode
///			-d 1 Enables  debud mode
int main(int argc, char ** argv)
{
	// Creating an instance of the game engine
	// to initialize from command line params.
	GameEngine gameEngine;

	// Default initialization
	gameEngine.SetInitDebug(true);
	gameEngine.SetInitFrameRate(90);
	gameEngine.SetInitUpdateRate(60);
	gameEngine.SetInitWindowTitle("The Witness");
	gameEngine.SetInitWindowSize(Vector2u(1024, 768));
	 
	if(argc == 3)
	{
		if(strcmp(argv[1], "-d") == 0)
		{
			// Arg sets to true
			if(argv[2][0] == '1')
			{
				// The user wants the debug mode
				gameEngine.SetInitDebug(true);
			}
		}
	}

	// The game engine is now initialized.
	// Starting the game loop
	gameEngine.Initialize();
	gameEngine.Start();

	return EXIT_SUCCESS;
}