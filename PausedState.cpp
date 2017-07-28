#include "PausedState.h"
#include "GameState.h"
#include <memory>
#include <iostream>

PausedState::PausedState(Game *game) : BaseState(game)
{
}


PausedState::~PausedState()
{
}

void PausedState::Update(const sf::Time& time)
{

}

void PausedState::Draw()
{
	mGame->GetWindow()->Draw(mText);
}

void PausedState::OnCreate()
{
	mFont.loadFromFile("arial.ttf");
	mText.setFont(mFont);
	mText.setString("Paused");
	mText.setCharacterSize(30);

	sf::FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	mText.setPosition(400, 300);
}

void PausedState::OnDestroy()
{
}

void PausedState::HandleInput(sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			mGame->PopState();
		}

	}
}
