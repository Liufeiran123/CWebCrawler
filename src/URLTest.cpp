/*
 * URLTest.cpp
 *
 *  Created on: 2015年1月3日
 *      Author: lfr
 */

#include "URLTest.h"
#include <math.h>
#include <string.h>

URLTest::URLTest(float p/*误判率*/,unsigned long num) {
	// TODO Auto-generated constructor stub
	cwl = p;
	urlnum = num;
	weishu = (unsigned long)(2.0*num*log(1/p)+1.0);
	db = new dynamic_bitset<>(weishu,0);
	funnum =(int)( 0.7*(weishu/urlnum)+1.0 );
}

URLTest::~URLTest() {
	// TODO Auto-generated destructor stub
	delete db;
}

void URLTest::call(string/*插件方法名*/ a,void * b,void* c,void *d,void* e,void *f,void *g,void **h/*函数返回值*/)
{
	if(a == "addToBloomSet")
	{
		addToBloomSet((char*)b);
	}
	else if(a == "isInBloomSet")
	{
		bool tmp =  isInBloomSet((char*)b);
		memcpy(g,&tmp,sizeof(bool));
	}

}

int URLTest::getHashValue(string str,int n)           //计算Hash值
{
    int result=0;
    int i;
    for(i=0;i<str.size();i++)
    {
        result=seeds[n]*result+(int)str[i];
        if(result > weishu)
            result%=weishu;
    }
    return result;
}


bool URLTest::isInBloomSet(string str)                //判断是否在布隆过滤器中
{
    int i;
    for(i=0;i<funnum;i++)
    {
        int hash=getHashValue(str,i);
        if(db->test(hash)== false)
            return false;
    }
    return true;
}

void URLTest::addToBloomSet(string str)               //添加元素到布隆过滤器
{
    int i;
    for(i=0;i<funnum;i++)
    {
        int hash=getHashValue(str,i);
        db->set(hash,1);
    }
}
