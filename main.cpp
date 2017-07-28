#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	while(game.IsOpen())
	{
		game.Update();
		game.Draw();
		game.HandleInput();
		game.RestartClock();
	}

	return 0;
}
