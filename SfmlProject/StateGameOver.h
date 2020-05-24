#pragma once

#include "IState.h"
#include "Board.h"

class StateGameOver : public IState
{
public:
	StateGameOver(const Board& in_owner) : owner(in_owner), next_state(nullptr)
	{

	}

	virtual void OnStateEnter() override
	{

	}

	virtual std::shared_ptr<IState> OnStateUpdate(float delta_seconds) override
	{
		return nullptr;
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
	const Board& owner;
};