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

// 需要把list的操作搞成线程安全的  
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

// 提交异步任务给该线程操作  
bool ThreadBase::PostTaskThread(TaskBase* task)
{
	WaitForSingleObject(semaphore_, INFINITE);//暂不处理返回错误,这里应该同时等待退出线程的通知  

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

		// 从任务队列取出任务处理  
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