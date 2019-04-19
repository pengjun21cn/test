#pragma once
class TaskBase
{
public:
	TaskBase(void) {};
	virtual ~TaskBase(void) {};

	virtual void DoTask() = 0;
};
