#pragma once
#include <fstream>
#include <sstream>
#include <stack>
#include <memory>
#include "Window.h"
#include "Brick.h"
#include "MenuState.h"
#include "TestState.h"
#include "GameState.h"
#include "WinState.h"


class BaseState;

class Game
{
public:
	Game();

	bool IsOpen() const;

	void Update();

	void Draw();

	void RestartClock();

	Window *GetWindow();

	void PushState(std::unique_ptr<BaseState> state);

	void PopState();

	void HandleInput();

	const int &GetCurrentLevel() const;

	void SwitchState(std::unique_ptr<BaseState> state);

	void SetLevel(const float &level);
	
private:

	Window mWindow;


	//Level Information
	int mCurrentLevel;

	//Keep Track of the elapsed delta time
	sf::Clock mClock;
	sf::Time mElapsed;

	//State stack
	std::stack<std::unique_ptr<BaseState>> mStates;

	

	bool mIsOpen;
};
