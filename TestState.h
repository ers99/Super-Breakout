#pragma once
#include "BaseState.h"
#include "Game.h"
class TestState :
	public BaseState
{
public:
	TestState(Game *game);
	~TestState();

	void Update(const sf::Time &) override;
	void Draw() override;
	void OnCreate() override;
	void OnDestroy() override;

	void HandleInput(sf::Event &) override;

	sf::RectangleShape mRect1, mRect2;
};

