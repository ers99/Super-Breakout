#include "Brick.h"



Brick::Brick()
{

}


Brick::~Brick()
{
}

void Brick::SetColor(const sf::Color& color)
{
	mShape.setFillColor(color);
}

void Brick::SetPosition(const sf::Vector2f& position)
{
	mShape.setPosition(position);
}

void Brick::SetSize(const sf::Vector2f& size)
{
	mShape.setSize(size);
}

void Brick::Draw(Window* window) const
{
	window->Draw(mShape);
}

const sf::FloatRect& Brick::GetBounds() const
{
	return mShape.getGlobalBounds();
}

const sf::Vector2f& Brick::GetPosition() const
{
	return mShape.getPosition();
}