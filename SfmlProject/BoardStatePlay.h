#pragma once

#include "IState.h"
#include "Board.h"
#include "SoundManager.h"

#include <glm.hpp>
#include <Windows.h>

class BoardStatePlay : public IState
{
public:
	BoardStatePlay(Board& in_board) : board(in_board)
	{

	}

	virtual void OnStateEnter() override
	{
	}

	virtual std::shared_ptr<IState> OnStateUpdate(float delta_seconds) override
	{
		// Check if ball collides with any paddles and set a new random direction
		for (int i = 0; i < this->board.paddles.size(); i++)
		{
			// Check collisions with paddles
			if (this->board.ball->GetShape()->getGlobalBounds().intersects(this->board.paddles[i]->GetShape()->getGlobalBounds()))
			{
				glm::vec2 reflected;

				// Calculate new direction for the ball based on reflected vector
				float x = this->board.ball->current_heading.x;
				float y = this->board.ball->current_heading.y;

				if (i == 0)
					reflected = glm::reflect(glm::vec2(x, y), glm::vec2(1, 0));
				else
					reflected = glm::reflect(glm::vec2(x, y), glm::vec2(-1, 0));

				this->board.ball->current_heading = sf::Vector2f(reflected.x, reflected.y);

				// Assign owner to the ball so that we know who is the actual player that can win
				this->board.ball->SetOwner(this->board.paddles[i]);
				SoundManager::Get().GetSound(eSoundType::PADDLE_BOUNCE)->play();
			}
		}

		// Check collisions with upper and bottom walls
		for (int i = 0; i < this->board.bounds.size(); i++)
		{
			// Check collisions with paddles
			if (this->board.ball->GetShape()->getGlobalBounds().intersects(this->board.bounds[i]->GetShape()->getGlobalBounds()))
			{
				glm::vec2 reflected;

				// Calculate new direction for the ball based on reflected vector
				float x = this->board.ball->current_heading.x;
				float y = this->board.ball->current_heading.y;

				if (i == 0)
					reflected = glm::reflect(glm::vec2(x, y), glm::vec2(0, 1));
				else
					reflected = glm::reflect(glm::vec2(x, y), glm::vec2(0, -1));

				this->board.ball->current_heading = sf::Vector2f(reflected.x, reflected.y);
				SoundManager::Get().GetSound(eSoundType::WALL_BOUNCE)->play();
			}
		}

		// Check in which part of the screen the ball goes off: win, losses and draw conditions

		// 1) Left screen 
		if (this->board.ball->GetShape()->getPosition().x + this->board.ball->GetShape()->getRadius() < -5 || this->board.ball->GetShape()->getPosition().x > 800)
		{
			if (!this->board.ball->GetOwner())
			{
				// draw-match
			}
			this->board.ball->SetGameOver(true);
		}

		return shared_from_this();
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
