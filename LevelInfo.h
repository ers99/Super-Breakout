#pragma once
#include "Window.h"
#include "Observer.h"
#include "sstream"

class LevelInfo : public Observer
{
public:
	LevelInfo();
	~LevelInfo();

	void Draw(Window *window);
	void OnCreate(Window *window);
	
	int GetScore() const;

	void OnNotify(const EventType &eventType, Entity *entity) override;

private:
	void IncreaseScore(int amount);
	void IncreaseMultiplier(float amount);
	void UpdateText();
	void UpdatePosition();


	int mScore;
	float mMultiplier;
	sf::Text mScoreText;
	sf::Text mMultiplierText;
	sf::Font mFont;
	sf::Vector2u mWindowSize;
	
};

