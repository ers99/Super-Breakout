#include "BaseState.h"

BaseState::BaseState(Game *game): mGame(game)
{
}

BaseState::~BaseState()
{
}

void BaseState::RegisterObserver(Observer* observer)
{
	mObservers.push_back(observer);
}

void BaseState::Notify(EventType event, Entity *entity)
{
	for (Observer* observer : mObservers)
	{
		observer->OnNotify(event, entity);
	}
}