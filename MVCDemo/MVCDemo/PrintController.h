#pragma once
#include "controllerbase.h"  
#include <string>  

class PrintModel;
class PrintController :
	public ControllerBase
{
public:
	PrintController(PrintModel* model);
	virtual ~PrintController(void);

	virtual void Register(ModelBase* model, Observer* observer);

	void HandleUserInput(const std::wstring* inputstr);
private:
	PrintModel * model_;
};
