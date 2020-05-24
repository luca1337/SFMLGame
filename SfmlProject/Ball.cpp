#include "Board.h"
#include "Ball.h"
#include "GameManager.h"
#include "BallStateMove.h"
#include "BallStateSelectDirection.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Ball::Ball(Board& in_board, const sf::Vector2f& initial_position) : position(initial_position), IsGameOver(false)
{
	SetEnabled(true);

	this->state_select_direction = std::make_shared<BallStateSelectDirection>(*this);
	this->state_move = std::make_shared<BallStateMove>(*this);

	this->state_select_direction->SetNextState(this->state_move);
	this->state_move->SetNextState(this->state_select_direction);

	this->current_state = this->state_select_direction;
	this->current_state->OnStateEnter();

	ball_shape = std::make_shared<sf::CircleShape>(this->ball_radius);
	ball_shape->setPosition(initial_position);
	
	//Set current direction to none
	current_direction = eDirectionType::NONE;
}

Ball::~Ball()
{
}

void Ball::Update(float delta_seconds)
{
	this->current_state = this->current_state->OnStateUpdate(delta_seconds);
}

void Ball::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this->ball_shape);
}

void Ball::SetEnabled(bool value)
{
	IsEnabled = value;
}

bool Ball::GetEnabled() const
{
	return IsEnabled;
}

void Ball::SetRandomDirection()
{
	this->current_direction = static_cast<eDirectionType>(std::rand() % eDirectionType::MAX_ENUM + 1);

	switch (this->current_direction)
	{
	case eDirectionType::NONE:
		this->current_heading = sf::Vector2f();
		break;
	case eDirectionType::LEFT:
		this->current_heading = sf::Vector2f(-1, -1);
		break;
	case eDirectionType::RIGHT:
		this->current_heading = sf::Vector2f(1, 1);
		break;
	default:
		this->current_heading = sf::Vector2f(-1, -1);
		break;
	}
}

eDirectionType Ball::GetCurrentDirection() const
{
	return this->current_direction;
}

std::shared_ptr<sf::CircleShape> Ball::GetShape() const
{
	return this->ball_shape;
}

void Ball::SetOwner(std::shared_ptr<Paddle> owner)
{
	this->owner = owner;
}

std::shared_ptr<Paddle> Ball::GetOwner() const
{
	return this->owner;
}

void Ball::SetGameOver(bool value)
{
	this->IsGameOver = value;
}

bool Ball::GetGameOver() const
{
	return this->IsGameOver;
}

void Ball::Reset()
{
	GameManager& gm = GameManager::Get();

	unsigned int screen_size_x = gm.GetWindowHandle()->getSize().x;
	unsigned int screen_size_y = gm.GetWindowHandle()->getSize().y;

	// Reset to default
	this->position = sf::Vector2f((screen_size_x / 2) - this->ball_shape->getRadius() / 2, (screen_size_y / 2) - this->ball_shape->getRadius() / 2);
	this->ball_shape->setPosition(this->position);
	this->current_direction = eDirectionType::NONE;
	this->IsGameOver = false;
	this->owner = nullptr;
	this->current_heading = sf::Vector2f();
}
