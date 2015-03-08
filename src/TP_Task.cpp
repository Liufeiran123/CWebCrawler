#include "TP_Task.h"

TP_Task::TP_Task()
{

}

TP_Task::~TP_Task(void)
{

}

int TP_Task::svc()
{
// 	ACE_DEBUG((LM_DEBUG,
// 		ACE_TEXT("(%t) Runing the event loop\n")));         //by fzq
	//LOGGER->AddLogger(LT_DEBUG_TIP,ACE_TEXT("Runing the event loop\n")) ;

	if(ACE_Reactor::instance() != 0)
	{
		while(ACE_Reactor::instance()->reactor_event_loop_done() == 0)
		{
			int result = ACE_Reactor::instance()->run_reactor_event_loop();
			if (result == -1)
			{
				printf("run event loop error\n");
				return  -1 ;

			}
		}
		printf("event loop exit\n");
	}
	return 0;
}

int TP_Task::start()
{
	if(this->activate(THR_NEW_LWP | THR_JOINABLE, 1) == -1)
	{
		std::cout<<"start tp task error\n";
		return -1 ;		
	}
	return 0;
}

int TP_Task::stop()
{
	ACE_Reactor::instance()->end_reactor_event_loop();
	return 0;
}

