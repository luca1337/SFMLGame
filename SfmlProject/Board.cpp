#include "Board.h"

#include "BoardStateSetup.h"
#include "BoardStatePlay.h"
#include "BoardStateGameOver.h"

Board::Board() : ball(nullptr), paddles(), bounds()
{
	this->state_setup = std::make_shared<BoardStateSetup>(*this);
	this->state_play = std::make_shared<BoardStatePlay>(*this);
	this->state_gameover = std::make_shared<BoardStateGameOver>(*this);

	this->state_setup->SetNextState(this->state_play);
	this->state_play->SetNextState(this->state_gameover);
	this->state_gameover->SetNextState(this->state_play);

	this->current_state = this->state_setup;
	this->current_state->OnStateEnter();
}

void Board::Update(float delta_seconds)
{
	this->current_state = current_state->OnStateUpdate(delta_seconds);
}

void Board::SetEnabled(bool value)
{
	IsEnabled = value;
}

bool Board::GetEnabled() const
{
	return IsEnabled;
}
