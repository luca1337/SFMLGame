#pragma once

#include "IEntity.h"
#include <SFML/Graphics.hpp>

// Interface with pvf's
class IRenderable
{
public:
	virtual void Render(std::shared_ptr<sf::RenderWindow> window) = 0;
};