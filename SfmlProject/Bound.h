#pragma once

#include "IEntity.h"
#include "IRenderable.h"

class Bound : public IEntity, public IRenderable
{
public:
	Bound(const sf::Vector2f& size, const sf::Vector2f& static_position, const sf::Color& color = sf::Color::White);
	virtual void Render(std::shared_ptr<sf::RenderWindow> window) override;
	virtual void SetEnabled(bool value) override;
	virtual bool GetEnabled() const override;
	std::shared_ptr<sf::RectangleShape> GetShape() const;

private:
	bool IsEnabled;
	std::shared_ptr<sf::RectangleShape> bound_shape;
};
