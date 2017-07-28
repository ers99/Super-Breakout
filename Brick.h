#pragma once
#include "Window.h"

class Brick
{
public:
	Brick();
	~Brick();

	void SetColor(const sf::Color &color);

	void SetPosition(const sf::Vector2f &position);

	void SetSize(const sf::Vector2f &size);

	void Draw(Window *window) const;

	const sf::FloatRect &GetBounds() const;
	
	const sf::Vector2f &GetPosition() const;

	void SetActive(const bool&);

	const bool &IsActive() const;

private:

	sf::RectangleShape mShape;
	bool mIsActive;
};

