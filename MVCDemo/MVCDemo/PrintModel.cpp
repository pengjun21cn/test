#include "stdafx.h"
#include "PrintModel.h"  
#include "Observer.h"  

PrintModel::PrintModel(void)
{
}

PrintModel::~PrintModel(void)
{
}

void PrintModel::Attach(Observer * observer)
{
	observerlist_.push_front(observer);
}

void PrintModel::Detach(Observer * observer)
{
	observerlist_.remove(observer);
}

void PrintModel::Notify()
{
	std::list<Observer*>::iterator it = observerlist_.begin();
	while (it != observerlist_.end())
	{
		(*it)->Update(this);
		++it;
	}
	return;
}

void PrintModel::GetPrintString(std::wstring& str)
{
	str = printstring_;
}

void PrintModel::SetPrintString(const std::wstring* str)
{
	printstring_ = *str;
}