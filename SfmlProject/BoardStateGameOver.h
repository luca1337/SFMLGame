#pragma once

#include "IState.h"
#include "Board.h"

#include <memory>

class BoardStateGameOver : public IState
{
public:
	BoardStateGameOver(Board& in_board) : board(in_board)
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
