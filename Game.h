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
#include "AudioPlayer.h"
#include "TextSpawner.h"


class BaseState;

class Game
{
public:
	Game();

	bool IsOpen() const;

	void Update(const sf::Time &timePerFrame);

	void Draw();


	Window *GetWindow();

	void PushState(std::unique_ptr<BaseState> state);

	void PopState();

	void HandleInput();

	const int &GetCurrentLevel() const;

	void SwitchState(std::unique_ptr<BaseState> state);

	void SetLevel(const float &level);

	const sf::Time GetElapsed();

	void SetElapsed(sf::Time elapsed);
	
private:

	Window mWindow;
	AudioPlayer mAudioPlayer;
	TextSpawner mTextSpawner;

	//Level Information
	int mCurrentLevel;
	std::vector<int> mLevelScores;

	//State stack
	std::stack<std::unique_ptr<BaseState>> mStates;

	

	bool mIsOpen;
};
