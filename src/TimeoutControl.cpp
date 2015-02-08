/*
 * TimeoutControl.cpp
 *
 *  Created on: 2015年1月18日
 *      Author: lfr
 */

#include "TimeoutControl.h"

TimeoutControl::TimeoutControl() {
	// TODO Auto-generated constructor stub

}

TimeoutControl::~TimeoutControl() {
	// TODO Auto-generated destructor stub
}

long TimeoutControl::registerTimer(Net_Svc_Handler*  nsh,ACE_Time_Value &val)
{
	long ret  = -1;
	if(nsh != NULL)
	{
		ACE_DEBUG ((LM_INFO, ACE_TEXT ("create timer is %T\n")));
		ret = ACE_Reactor::instance()->schedule_timer(&wj,(void*)nsh,val);
	}
	return ret;
}
void TimeoutControl::cancelTimer(long timerid)
{
	ACE_DEBUG ((LM_INFO, ACE_TEXT ("cancel Timer  is %T\n")));
	int i = ACE_Reactor::instance()->cancel_timer(timerid);
	ACE_DEBUG ((LM_INFO, ACE_TEXT ("cancelTimer id is %d,i is %d\n"),timerid,i));

}
