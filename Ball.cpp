#include "Ball.h"



Ball::Ball(float radius)
{
	SetRadius(radius);
	mShape.setOrigin(GetRadius(), GetRadius());
}


Ball::~Ball()
{
}

void Ball::SetPosition(const sf::Vector2f &position)
{
	mShape.setPosition(position);
}

void Ball::Draw(Window* window) const
{
	window->Draw(mShape);
}

const sf::FloatRect& Ball::GetBounds() const
{
	return mShape.getGlobalBounds();
}

const sf::Vector2f& Ball::GetPosition() const
{
	return mShape.getPosition();
}

const float &Ball::GetRadius() const
{
	return mShape.getRadius();
}

void Ball::SetRadius(const float &radius)
{
	mShape.setRadius(radius);
}

void Ball::SetColor(const sf::Color& color)
{
	mShape.setFillColor(color);
}