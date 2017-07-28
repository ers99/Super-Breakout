#include "TestState.h"
#include <iostream>


TestState::TestState(Game *game): BaseState(game)
{
}


TestState::~TestState()
{
}

void TestState::Update(const sf::Time &time)
{
	sf::Vector2f position = mRect1.getPosition();
	sf::Vector2f velocity;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = 100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = 100;
	}
	mRect1.setPosition(position + velocity * time.asSeconds());

	if (mRect1.getGlobalBounds().intersects(mRect2.getGlobalBounds()))
	{
		std::cout << "Intersecting!" << std::endl;
	}
}

void TestState::Draw()
{
	mGame->GetWindow()->Draw(mRect1);
	mGame->GetWindow()->Draw(mRect2);
}

void TestState::OnCreate()
{
	mRect1.setSize({ 100,100 });
	mRect2.setSize({ 100,50 });
	mRect1.setPosition({ 100,100 });
	mRect2.setPosition({ 400,300 });
}

void TestState::OnDestroy()
{
}

void TestState::HandleInput(sf::Event&)
{
}
