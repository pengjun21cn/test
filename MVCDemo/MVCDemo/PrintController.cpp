#include "stdafx.h"
#include "PrintController.h"  
#include "PrintModel.h"  

PrintController::PrintController(PrintModel* model)
	:model_(model)
{
}

PrintController::~PrintController(void)
{
}

void PrintController::Register(ModelBase* model, Observer* observer)
{
	model->Attach(observer);
	return;
}


void PrintController::HandleUserInput(const std::wstring* inputstr)
{
	model_->SetPrintString(inputstr);
	model_->Notify();
	return;
}