#include "Window.h"
#include <iostream>

Window::Window()
{
	sf::Vector2u windowSize;
	std::cout << "Enter resolution: (eg. 1920 1080)" << std::endl;
	std::cin >> windowSize.x >> windowSize.y;
	mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "Breakout", sf::Style::Fullscreen);
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
	mWindow.clear(sf::Color::Black);
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

void Window::SetView(const sf::View& view)
{
	mWindow.setView(view);
}

void Window::PollEvent(sf::Event& e)
{
	mWindow.pollEvent(e);
}

