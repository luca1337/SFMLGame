#pragma once

#include "IUpdatable.h"

#include <memory>
#include <array>
#include <iostream>
#include <SFML/Audio.hpp>

class Ball;
class Paddle;
class Bound;
class IState;
class BoardStateSetup;
class BoardStatePlay;
class BoardStateGameOver;

class Board : public IEntity, public IUpdatable
{ 
public:
	Board();
	virtual void Update(float delta_seconds) override;
	virtual void SetEnabled(bool value) override;
	virtual bool GetEnabled() const override;

	/*Entities*/
	std::shared_ptr<Ball> ball;
	std::array<std::shared_ptr<Paddle>, 2> paddles;
	std::array<std::shared_ptr<Bound>, 2> bounds;

private:
	bool IsEnabled;

	/*FSM*/
	std::shared_ptr<IState> current_state;
	std::shared_ptr<BoardStateSetup> state_setup;
	std::shared_ptr<BoardStatePlay> state_play;
	std::shared_ptr<BoardStateGameOver> state_gameover;
};