#pragma once

#include "IEntity.h"

// Interface with pvf's
class IUpdatable
{
public:
	virtual void Update(float delta_seconds) = 0;
};
