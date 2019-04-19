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

	// 使线程正常运行，读取消息并按任务提交处理  
	void Run();

	// 提供终止线程的入口  
	void Terminate();

	// 提交异步任务给该线程操作  
	bool PostTaskThread(TaskBase* task);

	// 执行任务  


	virtual void HandleTask(TaskBase* task) = 0;

	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
private:
	HANDLE thread_;
	DWORD threadid_;

	// 任务队列  
	std::queue<TaskBase*> taskqueue_;
	CRITICAL_SECTION cs_;
	HANDLE semaphore_;


	bool runflag_;
};
