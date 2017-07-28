#include "Game.h"
#include <iostream>


Game::Game(): mCurrentLevel(0)
{
	PushState(std::make_unique<MenuState>(this));
}

bool Game::IsOpen() const
{
	return mIsOpen;
}

void Game::Update()
{
	mStates.top()->Update(mElapsed);
}

void Game::Draw()
{
	mWindow.Clear();
	mStates.top()->Draw();
	mWindow.Display();
}

void Game::RestartClock()
{
	mElapsed = mClock.restart();
}

Window *Game::GetWindow()
{
	return &mWindow;
}

void Game::PushState(std::unique_ptr<BaseState> state)
{
	mStates.push(std::move(state));
	mStates.top()->OnCreate();
}

void Game::PopState()
{
	mStates.top()->OnDestroy();
	mStates.pop();
}

void Game::HandleInput()
{
	sf::Event event;
	mWindow.PollEvent(event);
	if(event.type == sf::Event::Closed)
	{
		mIsOpen = false;
	}
	mStates.top()->HandleInput(event);
}

const int &Game::GetCurrentLevel() const
{
	return mCurrentLevel;
}

void Game::SwitchState(std::unique_ptr<BaseState> state)
{
	PopState();
	PushState(std::move(state));
}

void Game::SetLevel(const float &level)
{
	mCurrentLevel = level;
}

