#include "MenuState.h"
#include "GameState.h"
#include <memory>
#include <iostream>

MenuState::MenuState(Game *game): BaseState(game)
{
}


MenuState::~MenuState()
{
}

void MenuState::Update(const sf::Time& time)
{

}

void MenuState::Draw()
{
	mGame->GetWindow()->Draw(mText);
}

void MenuState::OnCreate()
{
	sf::Vector2u size = mGame->GetWindow()->GetSize();
	mFont.loadFromFile("Fonts/mouse.otf");
	mText.setFont(mFont);
	mText.setString("Breakout");
	mText.setCharacterSize(size.x / 10);
	
	sf::FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	
	mText.setPosition(size.x / 2, size.y / 2);
	Notify(EventType::Start, nullptr);
}

void MenuState::OnDestroy()
{
}

void MenuState::HandleInput(sf::Event &event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Return)
		{
			mGame->PushState(std::make_unique<GameState>(mGame));
		}

	}
}
