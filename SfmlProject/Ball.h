#pragma once

#include "IUpdatable.h"
#include "IRenderable.h"

#include <SFML/System/Vector2.hpp>
#include <memory>

class Board;
class BallStateMove;
class BallStateSelectDirection;
class IState;

/*Directions*/
enum eDirectionType {
	NONE,
	LEFT,
	RIGHT,
	MAX_ENUM,
};

class Ball : 
	public IUpdatable,
	public IRenderable,
	public IEntity
{
public:
	Ball(Board& in_board, const sf::Vector2f& initial_position);
	~Ball();
	virtual void Update(float delta_seconds) override;
	virtual void Render(std::shared_ptr<sf::RenderWindow> window) override;
	virtual void SetEnabled(bool value) override;
	virtual bool GetEnabled() const override;

	void SetRandomDirection();
	sf::Vector2f current_heading;
	eDirectionType GetCurrentDirection() const;

	std::shared_ptr<sf::CircleShape> GetShape() const;

private:
	bool IsEnabled;
	sf::Vector2f position;
	const float ball_radius = 10.0f;
	std::shared_ptr<sf::CircleShape> ball_shape;

	/*FSM*/
	std::shared_ptr<BallStateSelectDirection> state_select_direction;
	std::shared_ptr<BallStateMove> state_move;
	std::shared_ptr<IState> current_state;

	eDirectionType current_direction;
};

