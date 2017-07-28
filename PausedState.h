#pragma once
#include "BaseState.h"
class PausedState :
	public BaseState
{
public:
	PausedState(Game *game);
	~PausedState();

	void Update(const sf::Time&) override;

	void Draw() override;

	void OnCreate() override;

	void OnDestroy() override;

	void HandleInput(sf::Event &) override;

private:
	sf::Font mFont;
	sf::Text mText;
};

