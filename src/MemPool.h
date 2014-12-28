/*
 * MemPool.h
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#ifndef MEMPOOL_H_
#define MEMPOOL_H_

#include <ace/Malloc_T.h>

template<class T>
class Mem_Pool: public ACE_Cached_Allocator<T,ACE_Thread_Mutex> ,MessageComponent{
protected:
	Mem_Pool(int size);
	virtual ~Mem_Pool();

private:
	static Mem_Pool<T> *mp;
public:
	T *getObject();
	void freeObject(T* a);
	static Mem_Pool<T> *getInstance();
};

#endif /* MEMPOOL_H_ */
