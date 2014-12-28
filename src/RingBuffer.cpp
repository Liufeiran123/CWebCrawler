/*
 * RingBuffer.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#include "RingBuffer.h"

template<typename T>
RingBuffer<T>::RingBuffer() {
	// TODO Auto-generated constructor stub
	in = out = 0;

}

template<typename T>
RingBuffer<T>::~RingBuffer() {
	// TODO Auto-generated destructor stub
	//min = max = 0 ;
}

template<typename T>
void RingBuffer<T>::put(T *d)
{
	if(256 - in + out >0)
	{
		memcpy(&_data[in & 255],d,sizeof(d));
		++in;
	}
}

template<typename T>
void RingBuffer<T>::get(T *d)
{
	if(in-out>0)
	{
		memcpy(d,&_data[out & 255],sizeof(d));
		++out;
	}

}

