#pragma once
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();
	
	const sf::RenderWindow *GetRenderWindow() const;

	void Clear();
	void Draw(const sf::Drawable&);
	void Display();

	const sf::Vector2u &GetSize() const;

	void PollEvent(sf::Event &e);

private:
	sf::RenderWindow mWindow;
};