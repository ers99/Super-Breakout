#pragma once
#include "BaseState.h"
#include <fstream>
#include <sstream>
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include <memory>
#include "Game.h"


class GameState :
	public BaseState
{
public:
	explicit GameState(Game *game);

	void Update(const sf::Time &) override;

	void Draw() override;

	void OnCreate() override;

	void OnDestroy() override;

	void HandleInput(sf::Event &) override;



	~GameState();

private:

	void HandleKeyboardState();
	bool LoadLevel(const std::string& path);

	std::vector<std::unique_ptr<Brick>> mLevel;
	sf::Vector2f mBlockSize, mBlockPadding;

	Paddle mPlayerPaddle;

	Ball mBall;

	bool mIsOver;

};

