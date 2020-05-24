#pragma once

class IEntity
{
public:
	virtual void SetEnabled(bool value) = 0;
	virtual bool GetEnabled() const = 0;
};