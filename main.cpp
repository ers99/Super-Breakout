#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	const sf::Time dt = sf::seconds(1 / 60.0f);
	sf::Clock mClock;
	sf::Time sinceLastUpdate = sf::Time::Zero;
	while(game.IsOpen())
	{
		sinceLastUpdate += mClock.restart();
		while (sinceLastUpdate >= dt)
		{
			sinceLastUpdate -= dt;
			game.Update(dt);
			
		}
		
		game.Draw();
		game.HandleInput();
	}

	return 0;
}
