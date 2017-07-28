#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"


class Game;

class BaseState
{
public:

	BaseState(Game*);

	virtual ~BaseState();
	virtual void Update(const sf::Time &) = 0;

	virtual void Draw() = 0;
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void HandleInput(sf::Event&) = 0;

protected:
	Game *mGame;
	

private:


	

	
};
