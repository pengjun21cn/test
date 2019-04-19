#pragma once
class Observer;
class ModelBase;
class ControllerBase
{
public:
	ControllerBase(void) {};
	virtual ~ControllerBase(void) {};
	virtual void Register(ModelBase* model, Observer* observer) = 0;
};
