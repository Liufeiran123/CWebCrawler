/*
 * MemPool.h
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#ifndef MEMPOOL_H_
#define MEMPOOL_H_

#include <ace/Malloc_T.h>
#include "MessageComponent.h"
#include "Document.h"

class Mem_Pool: public ACE_Cached_Allocator<Document,ACE_Thread_Mutex> {
protected:
	Mem_Pool(int size);
	virtual ~Mem_Pool();
private:
	static Mem_Pool *mp;
public:
	Document *getObject();
	void freeObject(Document* a);
	static Mem_Pool *getInstance();
	size_t getAvailable();
	void freeMemPool();
};

#endif /* MEMPOOL_H_ */
