/*
 * TimeoutControl.h
 *
 *  Created on: 2015年1月18日
 *      Author: lfr
 */

#ifndef TIMEOUTCONTROL_H_
#define TIMEOUTCONTROL_H_

#include <map>
#include "ace/Time_Value.h"
#include "Fetcher.h"
#include "ace/Synch.h"
#include "ace/Reactor.h"
 #include "ace/Event_Handler.h"
#include "ace/Log_Msg.h"

using namespace std;

class  wjtimer :  public  ACE_Event_Handler
{
public :
	virtual   int  handle_timeout( const  ACE_Time_Value &current_time,const   void  *act  /* = 0 */ )
	{
	//    const   int  *num = ACE_static_cast( const   int *,act);
   // 	const int num =  *(int*)act;
	//    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%d " ),num));

		//cout<<current_time.sec()<<"\n";

		Net_Svc_Handler *p = (Net_Svc_Handler*)act;
		ACE_DEBUG ((LM_INFO, ACE_TEXT ("handletimerout start! %T,p addr is %@,id is %d\n"),p,p->GetTimerid()));
		int i = p->getID();
		MessageBus::getInstance()->call(i,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		ACE_Reactor::instance()->remove_handler(p->get_handle(),ACE_Event_Handler::READ_MASK);

		ACE_DEBUG ((LM_INFO, ACE_TEXT ("handletimerout end\n")));

		return  -1;
	}

    virtual int handle_close (ACE_HANDLE handle,
                              ACE_Reactor_Mask close_mask)
    {
    	return 0;
    }

};

class TimeoutControl {
public:
	TimeoutControl();
	virtual ~TimeoutControl();
public:
	long registerTimer(Net_Svc_Handler*  nsh,ACE_Time_Value &val);
	void cancelTimer(long timerid);
private:
	wjtimer wj;
 };

typedef ACE_Unmanaged_Singleton<TimeoutControl,ACE_Null_Mutex>  TimeoutCtrl_Singleton;

#endif /* TIMEOUTCONTROL_H_ */
