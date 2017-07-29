#pragma once
#include <SFML/System/Vector2.hpp>
#include "Window.h"
//Any physical entity
class Entity
{
public:

	virtual void SetPosition(const sf::Vector2f &) = 0;

	virtual void Draw(Window *window) const = 0;

	virtual const sf::FloatRect &GetBounds() const = 0;

	virtual const sf::Vector2f &GetPosition() const = 0;

	const sf::Vector2f &GetVelocity() const;

	void SetVelocity(const sf::Vector2f &velocity);

	virtual void SetColor(const sf::Color &color) = 0;

	const float &GetMagnitude() const;

	void SetMagnitude(const float &magnitude);

	void SetMoving(bool isMoving);

	bool IsMoving() const;

	bool IsActive() const;

	void SetActive(bool active);




	Entity();
	virtual ~Entity();

protected:
	virtual void UpdateOrigin();

	float mMagnitude;
	sf::Vector2f mVelocity;

	bool mIsActive;
	bool mIsMoving;


};

