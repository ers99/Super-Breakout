#include "GameState.h"
#include <iostream>
#include "MenuState.h"
#include "PausedState.h"
#include "WinState.h"
#include <functional>


GameState::GameState(Game *game) : BaseState(game), 
mIsOver(false), mBlockSize({ mGame->GetWindow()->GetSize().x / 10.0f, mGame->GetWindow()->GetSize().y / 10.0f }),
mBlockPadding({ 1,1 }), mBall(mGame->GetWindow()->GetSize().x / 100.0f), mPlayerPaddle({ mGame->GetWindow()->GetSize().x / 5.0f, mGame->GetWindow()->GetSize().y / 10.0f })
{
}

void GameState::Update(const sf::Time &time)
{
	
	//Define variables needed for movement
	sf::Vector2f oldPlayerPos = mPlayerPaddle.GetPosition();
	const sf::Vector2u windowSize = mGame->GetWindow()->GetSize();
	sf::Vector2f oldBallPos = mBall.GetPosition();

	float playerMagnitude = HandleKeyboardState();
	if (mPlayerPaddle.IsMoving())
	{
		if (mPlayerPaddle.GetSize().x > 0)
		{
			mPlayerPaddle.SetSize(sf::Vector2f(mPlayerPaddle.GetSize().x - time.asSeconds() * windowSize.x / 10, mPlayerPaddle.GetSize().y));
		}
		else
		{
			mPlayerPaddle.SetSize(sf::Vector2f(0, mPlayerPaddle.GetSize().y));
		}

	}
	else if (mPlayerPaddle.GetSize().x < mPlayerPaddle.defaultSize.x)
	{
		mPlayerPaddle.SetSize(sf::Vector2f(mPlayerPaddle.GetSize().x + time.asSeconds() * windowSize.x / 10, mPlayerPaddle.GetSize().y));
	}

	mPlayerPaddle.SetPosition(sf::Vector2f(oldPlayerPos.x + playerMagnitude * time.asSeconds() * windowSize.x, oldPlayerPos.y));
	sf::Vector2f newBallPos = mBall.GetPosition();
	float ballRadius = mBall.GetRadius();
	sf::Vector2f newVelocity = mBall.GetVelocity();


	if(mBall.IsActive())
	{
		//Set the new ball position, but don't move it until collisions are checked
		newBallPos = oldBallPos + newVelocity * time.asSeconds();
	}
	else
	{
		mBall.SetPosition(sf::Vector2f(mPlayerPaddle.GetPosition().x, mPlayerPaddle.GetPosition().y - mPlayerPaddle.GetSize().y / 2 - ballRadius));
	}

	//Handle Wall Collisions
	bool bounced = false;
 	if (newBallPos.x + ballRadius > windowSize.x)
	{
		bounced = true;
		newVelocity.x = -std::abs(newVelocity.x);
	}
	else if(newBallPos.x - mBall.GetRadius() < 0)
	{
		bounced = true;
		newVelocity.x = std::abs(newVelocity.x);
	}
	else if(newBallPos.y - mBall.GetRadius() < 0)
	{
		bounced = true;
		newVelocity.y = std::abs(newVelocity.y);
	}
	if(bounced)
	{
		Notify(EventType::Bounce, &mBall);
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
		Notify(EventType::Bounce, &mPlayerPaddle);
		if(playerBounds.contains(ballDown))
		{
			//Use distance between middle of ball and middle of paddle to determine ball direction
			sf::Vector2f distance = mBall.GetPosition() - mPlayerPaddle.GetPosition();
			newVelocity = distance;
		}
		if (playerBounds.contains(ballLeft))
		{
			newVelocity.x = std::abs(newVelocity.x);
		}
		if (playerBounds.contains(ballRight))
		{
			newVelocity.x = -std::abs(newVelocity.x);
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
					Notify(EventType::BrickBreak, &**itr);
					if (brickBounds.contains(ballLeft))
					{
						newVelocity.x = std::abs(newVelocity.x);
					}
					if (brickBounds.contains(ballRight))
					{
						newVelocity.x = -std::abs(newVelocity.x);
					}
					if (brickBounds.contains(ballUp))
					{
						newVelocity.y = std::abs(newVelocity.y);
					}
					if (brickBounds.contains(ballDown))
					{
						newVelocity.y = -std::abs(newVelocity.y);
					}
					(*itr)->SetActive(false);

					break;
				}
				else if(brickBounds.contains(topLeft) || brickBounds.contains(topRight) || brickBounds.contains(bottomLeft) || brickBounds.contains(bottomRight))
				{
					Notify(EventType::BrickBreak, &**itr);

					if (brickBounds.contains(topLeft))
					{
						newVelocity.x = std::abs(newVelocity.x);
						newVelocity.y = std::abs(newVelocity.y);
					}
					if (brickBounds.contains(topRight))
					{
						newVelocity.x = -std::abs(newVelocity.x);
						newVelocity.y = std::abs(newVelocity.y);
					}
					if (brickBounds.contains(bottomLeft))
					{
						newVelocity.x = std::abs(newVelocity.x);
						newVelocity.y = -std::abs(newVelocity.y);
					}
					if (brickBounds.contains(bottomRight))
					{
						newVelocity.x = -std::abs(newVelocity.x);
						newVelocity.y = -std::abs(newVelocity.y);
					}
					(*itr)->SetActive(false);

					break;
				}
		}
	}

	//Handle losing condition
	if (newBallPos.y - mBall.GetRadius() > windowSize.y)
	{
		Notify(EventType::Lose, nullptr);
		for(auto &itr : mLevel)
		{
			itr->SetActive(true);
		}
		mGame->PopState();
		return;
	}

	//Get unit vector and then multiply by magnitude
	float magnitude = std::sqrt(std::pow(newVelocity.x, 2) + std::pow(newVelocity.y, 2));
	newVelocity.x /= magnitude;
	newVelocity.y /= magnitude;
	newVelocity *= mBall.GetMagnitude();
	//Finally update the balls position if active
	mBall.SetVelocity(newVelocity);

	if (mBall.IsActive())
	{
		mBall.SetPosition(sf::Vector2f(oldBallPos.x + mBall.GetVelocity().x * time.asSeconds() * windowSize.x, oldBallPos.y + mBall.GetVelocity().y * time.asSeconds() * windowSize.y));
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
		Notify(EventType::Win, nullptr);
		mGame->SetLevel(mGame->GetCurrentLevel() + 1);
		mGame->SwitchState(std::make_unique<WinState>(mGame, mLevelInfo.GetScore()));
		
	}
}

void GameState::Draw()
{
	Window* window = mGame->GetWindow();
	if(mLevel.empty())
	{
		return;
	}
	for(auto &itr : mLevel)
	{
		if((*itr).IsActive())
		{
			itr->Draw(window);
		}
		
	}
	mPlayerPaddle.Draw(window);
	mBall.Draw(window);
	mLevelInfo.Draw(window);
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
	mPlayerPaddle.SetMagnitude(1);
	mBall.SetPosition(sf::Vector2f(winSize.x / 2.0f, winSize.y - mPlayerPaddle.GetSize().y - mBall.GetRadius()));
	mBall.SetActive(false);
	mBall.SetMagnitude(1);
	mBall.SetVelocity(sf::Vector2f(mBall.GetMagnitude(), -mBall.GetMagnitude()));
	mLevelInfo.OnCreate(mGame->GetWindow());
	RegisterObserver(&mLevelInfo);
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

float GameState::HandleKeyboardState()
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
			return 0;
		}
		else
		{
			mPlayerPaddle.SetMoving(true);
			return mPlayerPaddle.GetMagnitude();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!(playerPos.x - playerSize.x / 2 > 0))
		{
			mPlayerPaddle.SetPosition(sf::Vector2f(playerSize.x / 2.0f, playerPos.y));
			mPlayerPaddle.SetMoving(false);
			return 0;
		}		
		else
		{
			mPlayerPaddle.SetMoving(true);
			return -mPlayerPaddle.GetMagnitude();
		}
	}
	else
	{
		mPlayerPaddle.SetMoving(false);
		return 0;
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
		int debugCounter = 0;
		while (!inLevel.eof())
		{
			std::cout << debugCounter++ << std::endl;
			std::string currentLine;
			std::getline(inLevel, currentLine);
			std::stringstream linestream(currentLine);
			std::string red, green, blue, alpha, x, y;
			linestream >> red >> green >> blue >> alpha >> x >> y;
			std::unique_ptr<Brick> brick = std::make_unique<Brick>();
			brick->SetSize(mBlockSize - mBlockPadding);
			brick->SetColor(sf::Color(std::stoi(red), std::stoi(green), std::stoi(blue)));
			brick->SetPosition(sf::Vector2f(std::stoi(x) * mBlockSize.x, std::stoi(y) * mBlockSize.y));
			brick->SetScoreValue(100);
			mLevel.push_back(std::move(brick));
			
		}
		inLevel.close();
		return true;
}