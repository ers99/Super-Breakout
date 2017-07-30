#pragma once
#include "Observer.h"
#include <memory>

class TextSpawner :
	public Observer
{
public:
	TextSpawner();
	~TextSpawner();

	void OnNotify(const EventType &eventType, Entity *entity) override;
	void Draw(Window *window);
	void Update(const sf::Time time);

private:

	void SpawnText(const sf::Vector2f &position, const std::string &text, int frames);

	void Clear();

	sf::Font mFont;
	std::vector<std::pair<int, std::unique_ptr<sf::Text>>> mTexts;
};

