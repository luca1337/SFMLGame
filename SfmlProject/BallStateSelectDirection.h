#pragma once

#include "IState.h"
#include "Ball.h"

class BallStateSelectDirection : public IState
{
public:
	BallStateSelectDirection(Ball& in_owner) : owner(in_owner), next_state(nullptr)
	{
	}

	virtual void OnStateEnter() override
	{
	}

	virtual std::shared_ptr<IState> OnStateUpdate(float delta_seconds) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			owner.SetRandomDirection();
			next_state->OnStateEnter();
			return next_state;
		}

		return shared_from_this();
	}

	virtual void OnStateExit() override
	{
	}

	/*Getter and Setter*/

	virtual void SetNextState(std::shared_ptr<IState> next) override
	{
		next_state = next;
	}

	virtual std::shared_ptr<IState> GetNextState() const override
	{
		return next_state;
	}

private:
	std::shared_ptr<IState> next_state;
	Ball& owner;
};