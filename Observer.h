#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "Entity.h"
enum class EventType
{
	Win,
	Lose,
	Bounce,
	BrickBreak
};

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void OnNotify(const EventType &eventType, Entity *entity);
};

