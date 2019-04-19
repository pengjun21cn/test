#pragma once
class Observer;

class ControllerBase;
class PrintController;

class ModelBase
{
public:
	ModelBase(void) {};
	virtual ~ModelBase(void) {};

private:
	friend ControllerBase;
	friend PrintController;
	virtual void Attach(Observer * observer) = 0;
	virtual void Detach(Observer * observer) = 0;
	virtual void Notify() = 0;
};
