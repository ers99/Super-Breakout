#include "AudioPlayer.h"
#include <iostream>
#include "Paddle.h"

AudioPlayer::AudioPlayer()
{
	LoadSound(EventType::Bounce, "Sounds/Bounce.wav");
	LoadSound(EventType::Start, "Sounds/laugh.wav");
	LoadSound(EventType::Win, "Sounds/fanfare.wav");
	LoadSound(EventType::Lose, "Sounds/lose.wav");
	LoadSound(EventType::BrickBreak, "Sounds/break.wav");
}

AudioPlayer::~AudioPlayer()
{

}

void AudioPlayer::PlaySound(const EventType& soundEffect, Entity *entity)
{
	
	auto itr = mSoundMap.find(soundEffect);
	if(itr != mSoundMap.end())
	{
		itr->second->play();
		if(soundEffect == EventType::BrickBreak)
		{
				itr->second->setPitch(itr->second->getPitch() + 0.5);
		}
	}
	else
	{
		std::cout << "Sound not found" << std::endl;
	}

	if (dynamic_cast<Paddle*>(entity) != nullptr || soundEffect == EventType::Win || soundEffect == EventType::Lose)
	{
		auto itr = mSoundMap.find(EventType::BrickBreak);
		if (itr != mSoundMap.end())
		{
			itr->second->setPitch(1);
		}
	}
}

void AudioPlayer::OnNotify(const EventType& eventType, Entity *entity)
{
	if(entity != nullptr)
	{
		PlaySound(eventType, entity);
	}
	else
	{
		PlaySound(eventType, nullptr);
	}
	
}


void AudioPlayer::LoadSound(const EventType& soundEffect, const std::string& path)
{
	std::unique_ptr<sf::SoundBuffer> currentSoundBuffer = std::make_unique<sf::SoundBuffer>();
	std::unique_ptr<sf::Sound> currentSound = std::make_unique<sf::Sound>();

	currentSoundBuffer->loadFromFile(path);
	currentSound->setBuffer(*currentSoundBuffer);

	mSoundMap.emplace(soundEffect, std::move(currentSound));
	mSoundBufferMap.emplace(soundEffect, std::move(currentSoundBuffer));
}
