/*
 * DBManager.h
 *
 *  Created on: 2015年1月11日
 *      Author: lfr
 */

#ifndef DBMANAGER_H_
#define DBMANAGER_H_
#include <sys/time.h>
#include <string>
#include "ace/Synch.h"
#include "ace/Singleton.h"
#include "db_cxx.h"


using namespace std;
class DBManager {
public:
	DBManager();
	~DBManager();
public:
	void closeDB();
	void writeDB(int db,string url,struct timeval *v);
	bool readDB(int db,string url,struct timeval *v);
	void deleteDB(int db,string url);
private:
	Db	crawelurl;
	Db  urlq;
};
typedef ACE_Unmanaged_Singleton<DBManager,ACE_Null_Mutex> DbManager_Singleton;
#endif /* DBMANAGER_H_ */
