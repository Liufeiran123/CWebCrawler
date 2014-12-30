#ifndef DATABUS_KERNEL_TP_TASK
#define DATABUS_KERNEL_TP_TASK

#include "ace/Reactor.h"
#include "ace/Thread_Semaphore.h"
#include "ace/Task_T.h"

class TP_Task :  public ACE_Task<ACE_NULL_SYNCH>
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
