/*
 * MemPool.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#include "MemPool.h"

template<T>
Mem_Pool<T> *Mem_Pool<T>::mp = NULL;

template<class T>
Mem_Pool<T>::Mem_Pool(int size):ACE_Cached_Allocator<T,ACE_Thread_Mutex>(size)
{
	// TODO Auto-generated constructor stub

}
template<class T>
Mem_Pool<T>::~Mem_Pool() {
	// TODO Auto-generated destructor stub
}

template<class T>
T *Mem_Pool<T>::getObject()
{
	return (T*)this->malloc(sizeof(T));
}
template<class T>
void Mem_Pool<T>::freeObject(T* a)
{
	this->free(a);
}

template<class T>
Mem_Pool<T>* Mem_Pool<T>::getInstance()
{
	if(mp != NULL)
	{
		return mp;
	}
	mp = new Mem_Pool<T>(256);
	return mp;
}
