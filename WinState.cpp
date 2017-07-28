#include "WinState.h"
#include "GameState.h"
#include <memory>
#include <iostream>

WinState::WinState(Game *game) : BaseState(game)
{
}


WinState::~WinState()
{
}

void WinState::Update(const sf::Time& time)
{

}

void WinState::Draw()
{
	mGame->GetWindow()->Draw(mText);
}

void WinState::OnCreate()
{
	mFont.loadFromFile("arial.ttf");
	mText.setFont(mFont);
	mText.setString("You Win!\nPress enter for next level");
	mText.setCharacterSize(30);

	sf::FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	mText.setPosition(400, 300);
}

void WinState::OnDestroy()
{
}

void WinState::HandleInput(sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Return)
		{
			mGame->SwitchState(std::make_unique<GameState>(mGame));
		}

	}
}
