#pragma once

#include "IState.h"
#include "Ball.h"

class BallStateMove : public IState
{
public:
	BallStateMove(Ball& in_owner) : owner(in_owner), next_state(nullptr), timer(0.0f)
	{
	}

	virtual void OnStateEnter() override
	{

	}

	virtual std::shared_ptr<IState> OnStateUpdate(float delta_seconds) override
	{
		if (owner.GetGameOver())
		{
			// Wait some seconds before resetting defaults and play some sound
			timer += delta_seconds;
			if (timer >= max_time)
			{
				this->OnStateExit();
				next_state->OnStateEnter();
				return next_state;
			}

			return shared_from_this();
		}

		owner.GetShape()->move(owner.current_heading * 400.0f * delta_seconds);

		return shared_from_this();
	}

	virtual void OnStateExit() override
	{
		timer = 0.0f;
		this->owner.Reset();
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
	float timer;
	const float max_time = 2.0f;
};