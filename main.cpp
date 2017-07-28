#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	//Start game loop
	Game game;
	const sf::Time dt = sf::seconds(1 / 144.0f);
	sf::Clock mClock;
	sf::Time sinceLastUpdate = sf::Time::Zero;

	while(game.IsOpen())
	{
		//Update is fixed timestep
		sinceLastUpdate += mClock.restart();
		while (sinceLastUpdate >= dt)
		{
			sinceLastUpdate -= dt;
			game.Update(dt);
			
		}
		//Update is variable
		game.Draw();
		game.HandleInput();
	}

	return 0;
}
