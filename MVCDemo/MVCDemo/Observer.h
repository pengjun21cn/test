#pragma once
class ModelBase;
class Observer
{
public:
	Observer(void) {};
	virtual ~Observer(void) {};
	virtual void Update(ModelBase * model) = 0;
};
