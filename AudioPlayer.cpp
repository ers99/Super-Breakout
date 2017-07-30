#include "AudioPlayer.h"
#include <iostream>

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

void AudioPlayer::PlaySound(const EventType& soundEffect)
{
	auto itr = mSoundMap.find(soundEffect);
	if(itr != mSoundMap.end())
	{
		(itr->second)->play();
	}
	else
	{
		std::cout << "Sound not found" << std::endl;
	}
}

void AudioPlayer::OnNotify(const EventType& eventType, Entity *entity)
{
	PlaySound(eventType);
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
