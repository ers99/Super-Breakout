#include "TextSpawner.h"
#include <iostream>


TextSpawner::TextSpawner()
{
	mFont.loadFromFile("Fonts/mouse.otf");
}


TextSpawner::~TextSpawner()
{
}

void TextSpawner::OnNotify(const EventType& eventType, Entity* entity)
{
	if (eventType == EventType::Lose || eventType == EventType::Win)
	{
		Clear();
	}

	if(eventType == EventType::BrickBreak && entity != nullptr)
	{
		SpawnText(sf::Vector2f(entity->GetPosition().x + entity->GetBounds().width / 2, entity->GetPosition().y + entity->GetBounds().height / 2), "100", 85);
	}

	
}

void TextSpawner::Draw(Window* window)
{
	for(auto itr = mTexts.begin(); itr != mTexts.end(); ++itr)
	{
		window->Draw(*itr->second);
	}
}

void TextSpawner::Update(const sf::Time time)
{
	if(mTexts.empty())
	{
		return;
	}

	auto itr = mTexts.begin();
	while(itr != mTexts.end())
	{
		if (itr->first < 0)
		{
			itr = mTexts.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	for(auto itr = mTexts.begin(); itr != mTexts.end(); ++itr)
	{
		if(itr->first > 0)
		{
			sf::Vector2f textPos = itr->second->getPosition();
			sf::Color textColor = itr->second->getFillColor();
			itr->second->setPosition(sf::Vector2f(textPos.x, textPos.y - time.asSeconds() * 40));
			textColor.a -= 3;
			itr->second->setFillColor(textColor);
			itr->first--;
		}
	}
}

void TextSpawner::SpawnText(const sf::Vector2f &position, const std::string &text, int frames)
{
	std::unique_ptr<sf::Text> currentText = std::make_unique<sf::Text>();
	currentText->setFont(mFont);
	currentText->setString(text);
	currentText->setCharacterSize(30);
	currentText->setOrigin(currentText->getLocalBounds().width / 2, currentText->getLocalBounds().height / 2);
	currentText->setPosition(position);
	mTexts.push_back(std::make_pair(frames, std::move(currentText)));
}

void TextSpawner::Clear()
{
	mTexts.clear();
}

