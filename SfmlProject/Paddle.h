#pragma once

#include "IUpdatable.h"
#include "IRenderable.h"

#include <vector>

#include <SFML/System/Vector2.hpp>

class Paddle :
	public IEntity,
	public IRenderable,
	public IUpdatable
{
public:
	Paddle(const sf::Vector2f& initial_position, std::vector<sf::Keyboard::Key> in_keys);
	virtual void Update(float delta_seconds) override;
	virtual void Render(std::shared_ptr<sf::RenderWindow> window) override;
	virtual void SetEnabled(bool value) override;
	virtual bool GetEnabled() const override;
	std::shared_ptr<sf::RectangleShape> GetShape() const;
private:
	bool IsEnabled;
	std::shared_ptr<sf::RectangleShape> paddle_shape;
	sf::Vector2f paddle_position;
	std::vector<sf::Keyboard::Key> keys;
};