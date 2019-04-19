#pragma once
#include "modelbase.h"  
#include <list>  
#include <string>  

class PrintController;
class PrintModel :
	public ModelBase
{
public:
	PrintModel(void);
	virtual ~PrintModel(void);
	void GetPrintString(std::wstring& str);

private:
	friend PrintController;
	virtual void Attach(Observer * observer);
	virtual void Detach(Observer * observer);
	virtual void Notify();

	void SetPrintString(const std::wstring* str);

private:
	std::list<Observer*> observerlist_;
	std::wstring printstring_;
};
