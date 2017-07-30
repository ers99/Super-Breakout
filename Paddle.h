#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Window.h"
#include "Entity.h"

class Paddle: public Entity
{
public:
	Paddle(const sf::Vector2f &size);
	~Paddle();

	sf::Vector2f defaultSize;
	const float DEFAULTMAGNITUDE = 400;

	void SetPosition(const sf::Vector2f &) override;
	

	void Draw(Window *window) const override;

	const sf::FloatRect &GetBounds() const override;

	const sf::Vector2f &GetPosition() const override;

	const sf::Vector2f &GetSize() const;

	void SetSize(const sf::Vector2f &size);

	void SetColor(const sf::Color &color) override;

private:

	void UpdateOrigin() override;

	sf::RectangleShape mShape;

};

