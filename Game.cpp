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

void Game::Update(const sf::Time &timePerFrame)
{
	mStates.top()->Update(timePerFrame);
	mTextSpawner.Update(timePerFrame);
}

void Game::Draw()
{
	mWindow.Clear();
	mStates.top()->Draw();
	mTextSpawner.Draw(&mWindow);
	mWindow.Display();
}


Window *Game::GetWindow()
{
	return &mWindow;
}

void Game::PushState(std::unique_ptr<BaseState> state)
{
	state->RegisterObserver(&mAudioPlayer);
	state->RegisterObserver(&mTextSpawner);
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
	state->RegisterObserver(&mAudioPlayer);
	PopState();
	PushState(std::move(state));
}

void Game::SetLevel(const float &level)
{
	mCurrentLevel = level;
}


