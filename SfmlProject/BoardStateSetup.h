#pragma once

#include "GameManager.h"
#include "IState.h"
#include "Board.h"
#include "Ball.h"
#include "Paddle.h"
#include "Bound.h"

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <array>

class BoardStateSetup : public IState
{
public:
	BoardStateSetup(Board& in_board) : board(in_board)
	{

	}

	virtual void OnStateEnter() override
	{
		// GM instance
		GameManager& gm = GameManager::Get();

		// Screen size for the object positions
		unsigned int screen_size_x = gm.GetWindowHandle()->getSize().x;
		unsigned int screen_size_y = gm.GetWindowHandle()->getSize().y;

		// Ball
		sf::Vector2f starting_ball_pos = sf::Vector2f(screen_size_x / 2, screen_size_y / 2);
		this->board.ball = std::make_shared<Ball>(this->board, starting_ball_pos);

		// Paddles: Right, Left
		auto left_paddle_pos = sf::Vector2f(0.0f, (screen_size_y - 25.0f) / 2);
		auto right_paddle_pos = sf::Vector2f(screen_size_x - 10.0f, (screen_size_y - 25.0f) / 2);

		//Key maps
		std::vector<sf::Keyboard::Key> left_paddle_keymaps = { sf::Keyboard::W, sf::Keyboard::S };
		std::vector<sf::Keyboard::Key> right_paddle_keymaps = { sf::Keyboard::Up, sf::Keyboard::Down };

		this->board.paddles = std::array<std::shared_ptr<Paddle>, 2>();
		this->board.paddles[0] = std::make_shared<Paddle>("Left Paddle", left_paddle_pos, left_paddle_keymaps);
		this->board.paddles[1] = std::make_shared<Paddle>("Right Paddle", right_paddle_pos, right_paddle_keymaps);

		// Walls: Upper, Bottom
		this->board.bounds = std::array<std::shared_ptr<Bound>, 2>();
		this->board.bounds[0] = std::make_shared<Bound>(sf::Vector2f(screen_size_x, 5.0f), sf::Vector2f(0.0f, 0.0f));
		this->board.bounds[1] = std::make_shared<Bound>(sf::Vector2f(screen_size_x, 5.0f), sf::Vector2f(0.0f, screen_size_y - 5.0f));

		gm.Add(this->board.ball);
		gm.Add(this->board.paddles[0]);
		gm.Add(this->board.paddles[1]);
		gm.Add(this->board.bounds[0]);
		gm.Add(this->board.bounds[1]);
	}

	virtual std::shared_ptr<IState> OnStateUpdate(float delta_seconds) override
	{
		next_state->OnStateEnter();
		return next_state;
	}

	virtual void OnStateExit() override
	{

	}

	virtual void SetNextState(std::shared_ptr<IState> next) override
	{
		this->next_state = next;
	}

	virtual std::shared_ptr<IState> GetNextState() const override
	{
		return this->next_state;
	}
private:
	Board& board;
	std::shared_ptr<IState> next_state;
};

