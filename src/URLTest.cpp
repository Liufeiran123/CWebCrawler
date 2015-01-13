/*
 * URLTest.cpp
 *
 *  Created on: 2015年1月3日
 *      Author: lfr
 */

#include <math.h>
#include <string.h>
#include "URLTest.h"
#include "DBManager.h"


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
		addToBloomSet((char*)b,0);
	}
	else if(a == "isInBloomSet")
	{
		bool tmp =  isInBloomSet((char*)b,0);
		memcpy(g,&tmp,sizeof(bool));
	}

}

/*int URLTest::getHashValue(string str,int n)           //计算Hash值
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
}*/


unsigned long  URLTest::getHashValue(string str,int n)     //BKDRHash
{
    register unsigned long uCode=0;
    for(int i=0;i<str.size();i++)
    {
        uCode = uCode *seeds[n]  + (unsigned char)str[i];
    }
    return uCode % weishu;
}


bool URLTest::isInBloomSet(string str)                //判断是否在布隆过滤器中
{
    int i;
    for(i=0;i<funnum;i++)
    {
    	unsigned long hash=getHashValue(str,i);
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
    	unsigned long hash=getHashValue(str,i);
        db->set(hash,true);
    }
}


bool URLTest::isInBloomSet(string str,int a)                //判断是否在布隆过滤器中
{
	struct timeval tv;
	return DbManager_Singleton::instance()->readDB(0,str,&tv);
}

void URLTest::addToBloomSet(string str,int a)               //添加元素到布隆过滤器
{
	struct timeval tv;
	DbManager_Singleton::instance()->writeDB(0,str,&tv);
}
