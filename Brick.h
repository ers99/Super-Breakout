#pragma once
#include "Window.h"
#include "Entity.h"

class Brick : public Entity
{
public:
	Brick();
	~Brick();

	void SetColor(const sf::Color &color) override;

	void SetPosition(const sf::Vector2f &position) override;

	void SetSize(const sf::Vector2f &size);

	void Draw(Window *window) const override;

	const sf::FloatRect &GetBounds() const override;
	
	const sf::Vector2f &GetPosition() const override;


private:

	sf::Vector2f mVelocity;

	sf::RectangleShape mShape;
};

