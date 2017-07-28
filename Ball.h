#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "Window.h"

class Ball
{
public:
	Ball(float speed, float radius);
	~Ball();

	

	void SetPosition(const sf::Vector2f &);


	void Draw(Window *window) const;

	const sf::FloatRect &GetBounds() const;

	const sf::Vector2f &GetPosition() const;

	const float &GetRadius() const;

	const sf::Vector2f &GetSpeed() const;

	void SetSpeed(const sf::Vector2f &speed);

	void SetRadius(const float &radius);

	void SetColor(const sf::Color &color);

	const float &GetMagnitude() const;

	void SetMagnitude(const float &magnitude);

	//Behavior methods

	void SetActive(const bool &active);

	const bool &IsActive() const;

private:

	float mMagnitude;
	sf::CircleShape mShape;
	sf::Vector2f mSpeed;
	bool mIsActive;
};

