#include "stdafx.h"
#include "PrintView.h"  
#include "PrintModel.h"  
#include <string>  
  
#include <iostream>  
#include <memory> 

using namespace std;

using std::endl;
using std::wcout;
using std::wstring;

PrintTask::PrintTask(PrintView* view, PrintModel* model)
	:view_(view), model_(model)
{
}

void PrintTask::DoTask()
{
	view_->DoUpdate(model_);
	return;
}


PrintView::PrintView(PrintModel* model)
	:model_(model)
{
}

PrintView::~PrintView(void)
{
}

void PrintView::Update(ModelBase * model)
{
	if (model_ == model)
	{
		PrintTask *task = new PrintTask(this, model_);
	//	auto task = make_unique<PrintTask>(this, model_);
		PostTaskThread(task);
	}
	return;
}

void PrintView::DoUpdate(ModelBase * model)
{
	if (model_ == model)
	{
		wstring str;
		model_->GetPrintString(str);
		wcout << str << endl;
	}
	return;
}

void PrintView::HandleTask(TaskBase* task)
{
	wcout << L"this is calling PrintView::HandleTask" << endl;//在页面上显示  
	PrintTask* printtask = (PrintTask*)task;
	printtask->DoTask();
}