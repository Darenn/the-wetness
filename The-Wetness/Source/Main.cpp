/// \file       Main.cpp
/// \date       08/10/2017
/// \package    None
/// \author     Vincent STEHLY--CALISTO

#include "Engine/GameEngine.hpp"
#include "Game/State/GameState.hpp"

/// \brief	Game entry point
///			Command line helper
///			-d 0 Disables debug mode
///			-d 1 Enables  debud mode
int main(int argc, char ** argv)
{
	// Creating an instance of the game engine
	// to initialize from command line params.
	GameEngine gameEngine(argv[0]);

	// Default initialization
	gameEngine.SetInitFrameRate(90);
	gameEngine.SetInitUpdateRate(90);
	gameEngine.SetInitWindowTitle("The Witness");
	gameEngine.SetInitWindowSize(Vector2u(1024, 768));
	 
	if(argc == 3)
	{
		if(strcmp(argv[1], "-d") == 0 && argv[2][0] == '1')
		{
			gameEngine.SetInitDebug(true);
		}
	}
	Grid grid = Grid(3, 4);
	std::cout << grid << std::endl;

	// The game engine is now initialized.
	gameEngine.Initialize();

	// Pushing the first state : WIP
	Engine::pStateMachine->PushState<GameState>("GameState");

	// Starting the game loop
	gameEngine.Start();
	
	return EXIT_SUCCESS;
}