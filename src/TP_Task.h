#ifndef DATABUS_KERNEL_TP_TASK
#define DATABUS_KERNEL_TP_TASK

#include "Kernel_Task.h"
#include "ace/Reactor.h"
#include "ace/Thread_Semaphore.h"

class TP_Task :  public ACE_Task
{
public:
	TP_Task(int t_num);
	virtual ~TP_Task(void);
public:
	virtual int svc();

	int start();
	int stop();

public:
	ACE_Thread_Semaphore sem_;
private:
	int thread_number;
};

#endif
