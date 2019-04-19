#pragma once
#include <windows.h>  
#include <queue>  

#define MAX_TASK_COUNT 1024  
class TaskBase;
class ThreadBase
{
public:
	ThreadBase(void);
	virtual ~ThreadBase(void);

	// ʹ�߳��������У���ȡ��Ϣ���������ύ����  
	void Run();

	// �ṩ��ֹ�̵߳����  
	void Terminate();

	// �ύ�첽��������̲߳���  
	bool PostTaskThread(TaskBase* task);

	// ִ������  


	virtual void HandleTask(TaskBase* task) = 0;

	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
private:
	HANDLE thread_;
	DWORD threadid_;

	// �������  
	std::queue<TaskBase*> taskqueue_;
	CRITICAL_SECTION cs_;
	HANDLE semaphore_;


	bool runflag_;
};
