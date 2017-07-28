#include "GameState.h"
#include <iostream>
#include "MenuState.h"
#include "PausedState.h"
#include "WinState.h"
#include <functional>


GameState::GameState(Game *game): BaseState(game), mIsOver(false), mBlockSize({100,50}), mBlockPadding({1,1}), mBall(400.f, 10)
{
}

void GameState::Update(const sf::Time &time)
{
	
	//Define variables needed for movement
	sf::Vector2f oldPlayerPos = mPlayerPaddle.GetPosition();
	sf::Vector2u windowSize = mGame->GetWindow()->GetSize();
	sf::Vector2f oldBallPos = mBall.GetPosition();
	sf::Vector2f oldSpeed = mBall.GetSpeed();

	HandleKeyboardState();
	if (mPlayerPaddle.IsMoving())
	{
		if (mPlayerPaddle.GetSize().x > 0)
		{
			mPlayerPaddle.SetSize(sf::Vector2f(mPlayerPaddle.GetSize().x - time.asSeconds() * 100, mPlayerPaddle.GetSize().y));
		}
		else
		{
			mPlayerPaddle.SetSize(sf::Vector2f(0, mPlayerPaddle.GetSize().y));
		}

	}
	else if (mPlayerPaddle.GetSize().x < mPlayerPaddle.DEFAULTSIZE.x)
	{
		mPlayerPaddle.SetSize(sf::Vector2f(mPlayerPaddle.GetSize().x + time.asSeconds() * 100, mPlayerPaddle.GetSize().y));
	}

	mPlayerPaddle.SetPosition(sf::Vector2f(oldPlayerPos.x + mPlayerPaddle.GetSpeed() * time.asSeconds(), oldPlayerPos.y));
	
	sf::Vector2f newPlayerPos = mPlayerPaddle.GetPosition();
	sf::Vector2f newBallPos = mBall.GetPosition();
	float ballRadius = mBall.GetRadius();
	sf::Vector2f newSpeed = mBall.GetSpeed();


	if(mBall.IsActive())
	{
		//Set the new ball position, but don't move it until collisions are checked
		newBallPos = oldBallPos + newSpeed * time.asSeconds();
	}

	//Handle Wall Collisions
	bool bounced = false;
 	if (newBallPos.x + ballRadius > windowSize.x)
	{
		bounced = true;
		newSpeed.x = -std::abs(newSpeed.x);
	}
	else if(newBallPos.x - mBall.GetRadius() < 0)
	{
		bounced = true;
		newSpeed.x = std::abs(newSpeed.x);
	}
	else if(newBallPos.y - mBall.GetRadius() < 0)
	{
		bounced = true;
		newSpeed.y = std::abs(newSpeed.y);
	}


	//Get the four sides of the ball to check collision direction
	float pi = std::acos(-1);
	sf::Vector2f ballLeft(newBallPos.x - ballRadius, newBallPos.y);
	sf::Vector2f ballRight(newBallPos.x + ballRadius, newBallPos.y);
	sf::Vector2f ballDown(newBallPos.x, newBallPos.y + ballRadius);
	sf::Vector2f ballUp(newBallPos.x, newBallPos.y - ballRadius);
	sf::Vector2f topLeft(newBallPos.x - ballRadius * std::sqrt(2) /2, newBallPos.y - ballRadius * std::sqrt(2) / 2);
	sf::Vector2f topRight(newBallPos.x + ballRadius * std::sqrt(2) / 2, newBallPos.y - ballRadius * std::sqrt(2) / 2);
	sf::Vector2f bottomLeft(newBallPos.x - ballRadius * std::sqrt(2) / 2, newBallPos.y + ballRadius * std::sqrt(2) / 2);
	sf::Vector2f bottomRight(newBallPos.x + ballRadius * std::sqrt(2) / 2, newBallPos.y + ballRadius * std::sqrt(2) / 2);


	//Handle Paddle collisions
	auto playerBounds = mPlayerPaddle.GetBounds();
	auto ballBounds = mBall.GetBounds();
	if (playerBounds.intersects(ballBounds))
	{
		bounced = true;
		if(playerBounds.contains(ballDown))
		{
			newSpeed.y = -std::abs(newSpeed.y);

			//Use distance between middle of ball and middle of paddle to determine ball direction
			sf::Vector2f distance = mBall.GetPosition() - mPlayerPaddle.GetPosition();
			newSpeed = distance;
		}
		if (playerBounds.contains(ballLeft))
		{
			newSpeed.x = std::abs(newSpeed.x);
		}
		if (playerBounds.contains(ballRight))
		{
			newSpeed.x = -std::abs(newSpeed.x);
		}
		
	}

	//Handle Brick collisions
	if(!mLevel.empty())
	{
		
		for (auto itr = mLevel.begin(); itr != mLevel.end(); ++itr)
		{
			if(!(*itr)->IsActive())
			{
				continue;
			}
			auto brickBounds = (*itr)->GetBounds();
			auto brickPosition = (*itr)->GetPosition();
			auto ballPosition = newBallPos;

				if(brickBounds.contains(ballLeft) || brickBounds.contains(ballRight) || brickBounds.contains(ballUp) || brickBounds.contains(ballDown))
				{
					bounced = true;
					if (brickBounds.contains(ballLeft))
					{
						newSpeed.x = std::abs(newSpeed.x);
					}
					if (brickBounds.contains(ballRight))
					{
						newSpeed.x = -std::abs(newSpeed.x);
					}
					if (brickBounds.contains(ballUp))
					{
						newSpeed.y = std::abs(newSpeed.y);
					}
					if (brickBounds.contains(ballDown))
					{
						newSpeed.y = -std::abs(newSpeed.y);
					}
					(*itr)->SetActive(false);

					break;
				}
				else if(brickBounds.contains(topLeft) || brickBounds.contains(topRight) || brickBounds.contains(bottomLeft) || brickBounds.contains(bottomRight))
				{
					bounced = true;
					if (brickBounds.contains(topLeft))
					{
						newSpeed.x = std::abs(newSpeed.x);
						newSpeed.y = std::abs(newSpeed.y);
					}
					if (brickBounds.contains(topRight))
					{
						newSpeed.x = -std::abs(newSpeed.x);
						newSpeed.y = std::abs(newSpeed.y);
					}
					if (brickBounds.contains(bottomLeft))
					{
						newSpeed.x = std::abs(newSpeed.x);
						newSpeed.y = -std::abs(newSpeed.y);
					}
					if (brickBounds.contains(bottomRight))
					{
						newSpeed.x = -std::abs(newSpeed.x);
						newSpeed.y = -std::abs(newSpeed.y);
					}
					(*itr)->SetActive(false);

					break;
				}
		}
	}
	if(bounced)
	{
		Notify(EventType::Bounce);
	}

	//Handle losing condition
	if (newBallPos.y - mBall.GetRadius() > windowSize.y)
	{
		for(auto &itr : mLevel)
		{
			itr->SetActive(true);
		}
		mGame->PopState();
	}

	//Get unit vector and then multiply by magnitude
	float magnitude = std::sqrt(std::pow(newSpeed.x, 2) + std::pow(newSpeed.y, 2));
	newSpeed.x /= magnitude;
	newSpeed.y /= magnitude;
	newSpeed = newSpeed * mBall.GetMagnitude();

	//Finally update the balls position if active
	mBall.SetSpeed(newSpeed);

	if (mBall.IsActive())
	{
		newBallPos = oldBallPos + newSpeed * time.asSeconds();
		mBall.SetPosition(newBallPos);
	}

	mIsOver = true;

	if (!mLevel.empty())
	{
		for (auto itr = mLevel.begin(); itr != mLevel.end(); ++itr)
		{
			if ((*itr)->IsActive())
			{
				mIsOver = false;
				break;
			}
		}
	}
	else
	{
		mIsOver = false;
	}
	if (mIsOver && mBall.IsActive())
	{
		mGame->SetLevel(mGame->GetCurrentLevel() + 1);
		mGame->SwitchState(std::make_unique<WinState>(mGame));
	}
}

void GameState::Draw()
{
	
	if(mLevel.empty())
	{
		return;
	}
	for(auto &itr : mLevel)
	{
		if((*itr).IsActive())
		{
			itr->Draw(mGame->GetWindow());
		}
		
	}
	mPlayerPaddle.Draw(mGame->GetWindow());
	mBall.Draw(mGame->GetWindow());
}

void GameState::OnCreate()
{
	if(!LoadLevel("levels/level"))
	{
		mGame->SetLevel(0);
		mGame->PopState();
		return;
	}
	sf::Vector2u winSize =  mGame->GetWindow()->GetSize();
	mPlayerPaddle.SetPosition(sf::Vector2f(winSize.x / 2.0f, winSize.y - mPlayerPaddle.GetSize().y / 2.0f));
	mPlayerPaddle.SetColor(sf::Color::Green);
	mBall.SetPosition(sf::Vector2f(winSize.x / 2.0f, winSize.y - mPlayerPaddle.GetSize().y - mBall.GetRadius()));
	mBall.SetActive(false);
	mBall.SetSpeed(sf::Vector2f(mBall.GetMagnitude(), -mBall.GetMagnitude()));
}

void GameState::OnDestroy()
{
}

void GameState::HandleInput(sf::Event &event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Space)
		{
			if(!mBall.IsActive())
			{
				mBall.SetActive(true);
			}
			
		}
		if(event.key.code == sf::Keyboard::Escape)
		{
			mGame->PushState(std::make_unique<PausedState>(mGame));
		}


	}
}




GameState::~GameState()
{
}

void GameState::HandleKeyboardState()
{
	//Define variables needed for movement
	sf::Vector2f playerPos = mPlayerPaddle.GetPosition();
	sf::Vector2f playerSize = mPlayerPaddle.GetSize();
	sf::Vector2u windowSize = mGame->GetWindow()->GetSize();

	//Handle KeyboardState and move player within bounds
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!(playerPos.x + playerSize.x / 2 < windowSize.x))
		{
			mPlayerPaddle.SetPosition(sf::Vector2f(windowSize.x - playerSize.x / 2.0f, playerPos.y));
			mPlayerPaddle.SetMoving(false);
			mPlayerPaddle.SetSpeed(0);
		}
		else
		{
			mPlayerPaddle.SetMoving(true);
			mPlayerPaddle.SetSpeed(mPlayerPaddle.SPEED);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!(playerPos.x - playerSize.x / 2 > 0))
		{
			mPlayerPaddle.SetPosition(sf::Vector2f(playerSize.x / 2.0f, playerPos.y));
			mPlayerPaddle.SetMoving(false);
			mPlayerPaddle.SetSpeed(0);
		}		
		else
		{
			mPlayerPaddle.SetMoving(true);
			mPlayerPaddle.SetSpeed(-mPlayerPaddle.SPEED);
		}
	}
	else
	{
		mPlayerPaddle.SetMoving(false);
		mPlayerPaddle.SetSpeed(0);
	}
	
}

bool GameState::LoadLevel(const std::string &path)
{
		std::ifstream inLevel;
		std::string filePath = path + std::to_string(mGame->GetCurrentLevel());
		inLevel.open(filePath);
		if (!inLevel.is_open())
		{
			std::cerr << "Level could not be opened" << std::endl;
			return false;
		}
		int currentBlock = 0;
		while (!inLevel.eof())
		{
			std::string currentLine;
			std::getline(inLevel, currentLine);
			std::stringstream linestream(currentLine);
			std::string red, green, blue, alpha, x, y;
			linestream >> red >> green >> blue >> alpha >> x >> y;
			std::shared_ptr<Brick> brick = std::make_shared<Brick>();
			brick->SetSize(mBlockSize - mBlockPadding);
			brick->SetColor(sf::Color(std::stoi(red), std::stoi(green), std::stoi(blue)));
			brick->SetPosition(sf::Vector2f(std::stoi(x) * mBlockSize.x, std::stoi(y) * mBlockSize.y));
			mLevel.push_back(std::move(brick));
		}
		inLevel.close();
		return true;
}