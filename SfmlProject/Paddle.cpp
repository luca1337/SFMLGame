#include "Paddle.h"
#include <glm.hpp>


Paddle::Paddle(std::string in_tag, const sf::Vector2f & initial_position, std::vector<sf::Keyboard::Key> in_keys)
{
	this->SetEnabled(true);

	this->paddle_position = initial_position;
	this->paddle_shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(10.0f, 50.0f));
	this->paddle_shape->setFillColor(sf::Color::White);
	this->paddle_shape->setPosition(initial_position);

	this->keys = in_keys;
	this->name_tag = in_tag;
}

void Paddle::Update(float delta_seconds)
{
	glm::vec2 clamped_movement = glm::clamp(glm::vec2(this->paddle_position.x, this->paddle_position.y), glm::vec2(this->paddle_position.x, 5), glm::vec2(this->paddle_position.x, 545));

	if (sf::Keyboard::isKeyPressed(this->keys[0])) // up
	{
		clamped_movement += glm::vec2(0, -1) * 400.0f * delta_seconds;
	}
	
	if (sf::Keyboard::isKeyPressed(this->keys[1])) // down
	{
		clamped_movement += glm::vec2(0, 1) * 400.0f * delta_seconds;
	}

	// Update old position with clamped one
	this->paddle_position = sf::Vector2f(clamped_movement.x, clamped_movement.y);
	this->paddle_shape->setPosition(sf::Vector2f(clamped_movement.x, clamped_movement.y));
}

void Paddle::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this->paddle_shape);
}

void Paddle::SetEnabled(bool value)
{
	this->IsEnabled = value;
}

bool Paddle::GetEnabled() const
{
	return this->IsEnabled;
}

std::string Paddle::GetNameTag() const
{
	return this->name_tag;
}

std::shared_ptr<sf::RectangleShape> Paddle::GetShape() const
{
	return this->paddle_shape;
}
