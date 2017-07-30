#include "Paddle.h"



Paddle::Paddle(const sf::Vector2f &size)
{
	SetSize(size);
	defaultSize = size;
}


Paddle::~Paddle()
{
}





const sf::FloatRect& Paddle::GetBounds() const
{
	return mShape.getGlobalBounds();
}

void Paddle::Draw(Window* window) const
{
	window->Draw(mShape);
}



const sf::Vector2f &Paddle::GetPosition() const
{
	return mShape.getPosition();
}

const sf::Vector2f& Paddle::GetSize() const
{
	return mShape.getSize();
}

void Paddle::SetSize(const sf::Vector2f& size)
{
	mShape.setSize(size);
	UpdateOrigin();
}

void Paddle::SetColor(const sf::Color& color)
{
	mShape.setFillColor(color);
}

void Paddle::UpdateOrigin()
{
	mShape.setOrigin(GetSize().x / 2.0f, GetSize().y / 2.0f);
}


void Paddle::SetPosition(const sf::Vector2f &position)
{
	mShape.setPosition(position);
}
