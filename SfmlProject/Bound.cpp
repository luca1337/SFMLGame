#include "Bound.h"
#include <SFML/Graphics.hpp>

Bound::Bound(const sf::Vector2f & size, const sf::Vector2f & static_position, const sf::Color& color)
{
	this->SetEnabled(true);

	this->bound_shape = std::make_shared<sf::RectangleShape>(size);
	this->bound_shape->setPosition(static_position);
	this->bound_shape->setFillColor(color);
}

void Bound::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this->bound_shape);
}

void Bound::SetEnabled(bool value)
{
	this->IsEnabled = value;
}

bool Bound::GetEnabled() const
{
	return this->IsEnabled;
}

std::shared_ptr<sf::RectangleShape> Bound::GetShape() const
{
	return this->bound_shape;
}
