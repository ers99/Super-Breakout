#include "LevelInfo.h"
#include "Paddle.h"
#include <iomanip>


LevelInfo::LevelInfo(): mScore(0), mMultiplier(1.0f)
{
	
}


LevelInfo::~LevelInfo()
{
}

void LevelInfo::Draw(Window* window)
{
	window->Draw(mScoreText);
	window->Draw(mMultiplierText);
}

void LevelInfo::OnCreate(Window* window)
{
	mWindowSize = window->GetSize();
	mFont.loadFromFile("Fonts/mouse.otf");
	mScoreText.setFont(mFont);
	mMultiplierText.setFont(mFont);
	mScoreText.setCharacterSize(mWindowSize.x / 20.0f);
	mMultiplierText.setCharacterSize(mWindowSize.x / 20.0f);
	UpdateText();
}

void LevelInfo::IncreaseScore(int amount)
{
	mScore += amount * mMultiplier;
	UpdateText();
}

void LevelInfo::IncreaseMultiplier(float amount)
{
	mMultiplier += amount;
	UpdateText();
}

int LevelInfo::GetScore() const
{
	return mScore;
}

void LevelInfo::OnNotify(const EventType& eventType, Entity* entity)
{
	switch(eventType)
	{
	case EventType::BrickBreak:
		{
			IncreaseScore(100);
			IncreaseMultiplier(0.5f);
			break;
		}
	case EventType::Bounce:
		{
			if(dynamic_cast<Paddle*>(entity) != nullptr)
			{
				mMultiplier = 1.0f;
				UpdateText();
			}
			break;
		}
	}
}

void LevelInfo::UpdateText()
{
	mScoreText.setString(std::to_string(mScore));
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << mMultiplier;
	mMultiplierText.setString(stream.str() + "x");
	UpdatePosition();
}

void LevelInfo::UpdatePosition()
{
	sf::FloatRect textRect = mScoreText.getLocalBounds();
	mScoreText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	mScoreText.setPosition(mWindowSize.x / 2, textRect.height);
	textRect = mMultiplierText.getLocalBounds();
	mMultiplierText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	mMultiplierText.setPosition(textRect.width, textRect.height);
}
