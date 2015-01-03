/*
 * URLTest.h
 *
 *  Created on: 2015年1月3日
 *      Author: lfr
 */

#ifndef URLTEST_H_
#define URLTEST_H_

#include <boost/dynamic_bitset.hpp>
#include <vector>

#include "MessageComponent.h"

using namespace std;
using namespace boost;

const int seeds[] = {3,7,11,13,17,19,23,29,31,37,41,43,47};

class URLTest : public MessageComponent  {
public:
	URLTest(float p/*误判率*/,unsigned long num);
	virtual ~URLTest();
private:
	dynamic_bitset<> *db;
	unsigned long weishu;
	float cwl;
	unsigned long urlnum;
	int funnum;
	//动态数组
public:
	virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/);
	int getHashValue(string str,int n);
	bool isInBloomSet(string str);
	void addToBloomSet(string str);
};

#endif /* URLTEST_H_ */
