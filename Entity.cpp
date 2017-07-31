#include "Entity.h"

const sf::Vector2f& Entity::GetVelocity() const
{
	return mVelocity;
}

void Entity::SetVelocity(const sf::Vector2f& velocity)
{
	mVelocity = velocity;
}

const float& Entity::GetMagnitude() const
{
	return mMagnitude;
}

void Entity::SetMagnitude(const float& magnitude)
{
	mMagnitude = magnitude;
}


void Entity::SetMoving(bool isMoving)
{
	mIsMoving = isMoving;
}

bool Entity::IsMoving() const
{
	return mIsMoving;
}

bool Entity::IsActive() const
{
	return mIsActive;
}

void Entity::SetActive(bool active)
{
	mIsActive = active;
}

void Entity::SetScoreValue(int value)
{
	mScoreValue = value;
}

int Entity::GetScoreValue()
{
	return mScoreValue;
}

Entity::Entity(): mIsActive(true)
{

}


Entity::~Entity()
{
}

void Entity::UpdateOrigin()
{

}
