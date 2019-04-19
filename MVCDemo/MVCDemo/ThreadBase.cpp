#include "stdafx.h"
#include "ThreadBase.h"  
#include "TaskBase.h"
#include <string>  
#include <iostream>  
#include <memory> 


using namespace std;
using std::wcout;
using std::wstring;
using std::endl;

ThreadBase::ThreadBase(void)
	:runflag_(false)
{
	thread_ = ::CreateThread(NULL,
		0,
		ThreadBase::ThreadProc,
		this,
		CREATE_SUSPENDED,
		&threadid_);

	semaphore_ = ::CreateSemaphore(NULL, MAX_TASK_COUNT, MAX_TASK_COUNT, NULL);

	InitializeCriticalSection(&cs_);
}

ThreadBase::~ThreadBase(void)
{
	DeleteCriticalSection(&cs_);
}

// ��Ҫ��list�Ĳ�������̰߳�ȫ��  
void ThreadBase::Run()
{
	runflag_ = true;
	ResumeThread(thread_);
	return;
}

void ThreadBase::Terminate()
{
	runflag_ = false;
	return;
}

// �ύ�첽��������̲߳���  
bool ThreadBase::PostTaskThread(TaskBase* task)
{
	WaitForSingleObject(semaphore_, INFINITE);//�ݲ������ش���,����Ӧ��ͬʱ�ȴ��˳��̵߳�֪ͨ  

	EnterCriticalSection(&cs_);
	taskqueue_.push(task);
	LeaveCriticalSection(&cs_);

	return false;
}

DWORD ThreadBase::ThreadProc(LPVOID lpParameter)
{
	ThreadBase* threadbase = (ThreadBase*)(lpParameter);
	threadbase->runflag_ = true;
	while (threadbase->runflag_)
	{
		EnterCriticalSection(&threadbase->cs_);
		if (!threadbase->taskqueue_.size())
		{
			LeaveCriticalSection(&threadbase->cs_);
			continue;
		}

		// ���������ȡ��������  
		TaskBase* task = threadbase->taskqueue_.front();

		threadbase->taskqueue_.pop();
		LeaveCriticalSection(&threadbase->cs_);

		if (!ReleaseSemaphore(threadbase->semaphore_, 1, NULL))
		{
			printf("ReleaseSemaphore error: %d\n", GetLastError());
		}
		threadbase->HandleTask(task);
		delete task;

	}
	return 0;
}