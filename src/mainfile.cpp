/*
 * mainfile.cpp

 *
 *  Created on: 2014年12月29日
 *      Author: lfr
 */
#include <stdio.h>
#include "ace/Reactor.h"
#include "ace/Dev_Poll_Reactor.h"
#include "CrawlerEntity.h"
#include "TP_Task.h"


int main()
{
	ACE_Dev_Poll_Reactor * reactor_impl;
	ACE_Reactor *reactor;
	ACE_NEW_RETURN(reactor_impl, ACE_Dev_Poll_Reactor(), -1);
	ACE_NEW_RETURN(reactor, ACE_Reactor(reactor_impl, 1), -1);
	ACE_Reactor::instance(reactor);


	CrawlerEntity ce;


	TP_Task tp(1);
	tp.start();
	int a;
	scanf("%d",&a);
	return 0;
}
