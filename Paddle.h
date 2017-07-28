#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Window.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	const float SPEED = 600;
	const sf::Vector2f DEFAULTSIZE = { 200,50 };

	void SetPosition(const sf::Vector2f &);
	

	void Draw(Window *window) const;

	const sf::FloatRect &GetBounds() const;

	const sf::Vector2f &GetPosition() const;

	const sf::Vector2f &GetSize() const;

	const float &GetSpeed() const;

	void SetSpeed(const float &speed);

	void SetSize(const sf::Vector2f &size);

	void SetColor(const sf::Color &color);

	void SetMoving(bool isMoving);

	bool IsMoving() const;
	


private:

	void UpdateOrigin();

	sf::RectangleShape mShape;
	float mSpeed;
	
	bool mIsMoving;

};

