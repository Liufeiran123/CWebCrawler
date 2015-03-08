#ifndef DATABUS_KERNEL_TP_TASK
#define DATABUS_KERNEL_TP_TASK

#include <iostream>
#include "ace/Reactor.h"
#include "ace/Thread_Semaphore.h"
#include "ace/Task_T.h"

using namespace std;

class TP_Task :  public ACE_Task<ACE_NULL_SYNCH>
{
public:
	TP_Task();
	virtual ~TP_Task(void);
public:
	virtual int svc();
	int start();
	int stop();
};

#endif
