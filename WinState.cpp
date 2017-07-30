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
	sf::Vector2u size = mGame->GetWindow()->GetSize();
	mFont.loadFromFile("Fonts/mouse.otf");
	mText.setFont(mFont);
	mText.setString("    You Win!\n  Press enter \n for next level");
	mText.setCharacterSize(size.x/10);

	sf::FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	mText.setPosition(size.x/2, size.y/2);
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
