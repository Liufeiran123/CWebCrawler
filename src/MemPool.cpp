/*
 * MemPool.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#include "commondefine.h"
#include "MemPool.h"

Mem_Pool*Mem_Pool::mp = NULL;


Mem_Pool::Mem_Pool(int size):ACE_Cached_Allocator<Document,ACE_Thread_Mutex>(size)
{
	// TODO Auto-generated constructor stub

}

Mem_Pool::~Mem_Pool() {
	// TODO Auto-generated destructor stub
}


Document *Mem_Pool::getObject()
{
	while(getAvailable() < MEMPOOL * 0.2)
	{
		sleep(4);
	}
	return (Document*)this->calloc(sizeof(Document));
}

void Mem_Pool::freeObject(Document* a)
{
	this->free(a);
}


Mem_Pool* Mem_Pool::getInstance()
{
	if(mp != NULL)
	{
		return mp;
	}
	mp = new Mem_Pool(MEMPOOL);
	return mp;
}

size_t Mem_Pool::getAvailable()
{
	return this->pool_depth();
}
