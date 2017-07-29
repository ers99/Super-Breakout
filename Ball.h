#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "Window.h"
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(float radius);
	~Ball();

	void SetPosition(const sf::Vector2f &) override;


	void Draw(Window *window) const override;

	const sf::FloatRect &GetBounds() const override;

	const sf::Vector2f &GetPosition() const override;

	void SetColor(const sf::Color &color) override;

	//Behavior methods

	const float &GetRadius() const;
	void SetRadius(const float &radius);

private:
	sf::CircleShape mShape;
};

