#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/Audio.hpp>
#include <memory>
#include "Observer.h"


class AudioPlayer : public Observer
{
public:
	AudioPlayer();
	~AudioPlayer();

	void PlaySound(const EventType &soundEffect, Entity *entity);

	void OnNotify(const EventType &eventType, Entity *entity) override;

private:
	void LoadSound(const EventType& soundEffect, const std::string& path);

	std::map<EventType, std::unique_ptr<sf::SoundBuffer>> mSoundBufferMap;
	std::map<EventType, std::unique_ptr<sf::Sound>> mSoundMap;
};