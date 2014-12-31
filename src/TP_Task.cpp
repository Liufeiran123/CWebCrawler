#include "TP_Task.h"

TP_Task::TP_Task(int t_num)
{
	thread_number = t_num;
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
// 				ACE_ERROR_RETURN((LM_ERROR, 
// 					ACE_TEXT("(%t) %p\n"),
// 					ACE_TEXT("Error handling event")),
// 					0);                                      //by fzq
		//		LOGGER->AddLogger(LT_DEBUG_ERROR,ACE_TEXT("Error handling event")) ;
				return 0 ;
// 				ACE_DEBUG((LM_DEBUG,
// 					ACE_TEXT("(%t) Done handling events.\n")));  //by fzq
// 				LOGGER->AddLogger(LT_DEBUG_TIP,ACE_TEXT("(%t) Done handling events.\n")) ;
// 				break;
			}
		}
	}
	return 0;
}

int TP_Task::start()
{
	if(this->activate(THR_NEW_LWP | THR_JOINABLE, thread_number) == -1)
	{
// 		ACE_ERROR_RETURN ((LM_ERROR,
// 							ACE_TEXT ("%p.\n"),
// 							ACE_TEXT ("unable to activate thread pool")),
// 							-1);                            //by fzq
	//	LOGGER->AddLogger(LT_DEBUG_ERROR,ACE_TEXT("unable to activate thread pool")) ;
		return -1 ;		
	}
	
	return 0;
}

int TP_Task::stop()
{
	if (this->reactor() != 0)
	{
// 		ACE_DEBUG ((LM_DEBUG,
// 					ACE_TEXT ("End TP_Reactor event loop\n")));
		//LOGGER->AddLogger(LT_DEBUG_TIP,ACE_TEXT("End TP_Reactor event loop\n")) ;

		this->reactor()->end_reactor_event_loop();
	}

	if (this->wait () == -1)
	{
// 		ACE_ERROR_RETURN ((LM_ERROR,
// 							ACE_TEXT ("%p.\n"),
// 							ACE_TEXT ("unable to stop thread pool")),
// 							-1);                            //by fzq
		//LOGGER->AddLogger(LT_DEBUG_ERROR,ACE_TEXT("unable to stop thread pool")) ;
		return -1 ;		
	}

	return 0;
}

