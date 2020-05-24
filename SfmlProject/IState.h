#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <memory>

class IState : public std::enable_shared_from_this<IState>
{
public:
	virtual void OnStateEnter() = 0;
	virtual std::shared_ptr<IState> OnStateUpdate(float delta_seconds) = 0;
	virtual void OnStateExit() = 0;
	virtual void SetNextState(std::shared_ptr<IState> next) = 0;
	virtual std::shared_ptr<IState> GetNextState() const = 0;
};

#endif // _ISTATE_H_
