#pragma once
#include "viewbase.h"  
#include "observer.h"  
#include "threadbase.h"  
#include "taskbase.h"  


class PrintModel;
class PrintView;
class PrintTask
	:public TaskBase
{
public:
	PrintTask(PrintView* view, PrintModel* model);
	virtual void DoTask();

private:
	PrintView * view_;
	PrintModel* model_;
};

class PrintView :
	public ViewBase, public Observer, public ThreadBase
{
public:
	PrintView(PrintModel* model);
	virtual ~PrintView(void);

	virtual void Update(ModelBase * model);

	virtual void HandleTask(TaskBase* task);

private:
	friend PrintTask;
	void DoUpdate(ModelBase * model);
private:
	PrintModel * model_;
};