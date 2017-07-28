#include "Window.h"

Window::Window(): mWindow(sf::VideoMode(800,600), "Breakout")
{
	mWindow.setVerticalSyncEnabled(true);
}

Window::~Window()
{
}

const sf::RenderWindow* Window::GetRenderWindow() const
{
	return &mWindow;
}

void Window::Clear()
{
	mWindow.clear();
}

void Window::Draw(const sf::Drawable &drawable)
{
	mWindow.draw(drawable);
}

void Window::Display()
{
	mWindow.display();
}

const sf::Vector2u& Window::GetSize() const
{
	return mWindow.getSize();
}

void Window::PollEvent(sf::Event& e)
{
	mWindow.pollEvent(e);
}
