#pragma once
#include "BaseState.h"
class WinState :
	public BaseState
{
public:
	WinState(Game *game, int score);
	~WinState();

	void Update(const sf::Time&) override;

	void Draw() override;

	void OnCreate() override;

	void OnDestroy() override;

	void HandleInput(sf::Event &) override;

private:
	sf::Font mFont;
	sf::Text mText;

	int mScore;
};

