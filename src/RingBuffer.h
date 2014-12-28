/*
 * RingBuffer.h
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include "MessageComponent.h"

template<typename T>
class RingBuffer : public MessageComponent {
public:
	RingBuffer();
	virtual ~RingBuffer();
public:
	void put(T* d);
	void get(T *d);
private:
	T _data[256];
	unsigned int in;
	unsigned int out;
};

#endif /* RINGBUFFER_H_ */
