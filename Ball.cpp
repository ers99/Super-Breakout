#include "Ball.h"



Ball::Ball(float speed, float radius): mMagnitude(speed)
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

const sf::Vector2f& Ball::GetSpeed() const
{
	return mSpeed;
}

void Ball::SetSpeed(const sf::Vector2f &speed)
{
	mSpeed = speed;
}

void Ball::SetRadius(const float &radius)
{
	mShape.setRadius(radius);
}

void Ball::SetColor(const sf::Color& color)
{
	mShape.setFillColor(color);
}

const float &Ball::GetMagnitude() const
{
	return mMagnitude;
}

void Ball::SetMagnitude(const float& magnitude)
{
	mMagnitude = magnitude;
}

void Ball::SetActive(const bool& active)
{
	mIsActive = active;
}

const bool& Ball::IsActive() const
{
	return mIsActive;
}
