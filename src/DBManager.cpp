/*
 * DBManager.cpp
 *
 *  Created on: 2015年1月11日
 *      Author: lfr
 */

#include "DBManager.h"

DBManager::DBManager():crawelurl(NULL,0),urlq(NULL,0)
{
	// TODO Auto-generated constructor stub
	try
	{
	// Redirect debugging information to std::cerr
		//crawelurl.set_error_stream(&std::cerr);
	// Open the database
		crawelurl.open(NULL, "/home/lfr/workspace3/crawler/crawlerurl.db", NULL, DB_BTREE, DB_CREATE, 0);
		urlq.open(NULL,"/home/lfr/workspace3/crawler/urlq.db",NULL,DB_BTREE,DB_CREATE,0);
	}
	// DbException is not a subclass of std::exception, so we
	// need to catch them both.
	catch(DbException &e)
	{
	std::cerr << "Error opening database: crawlerurl.db" << "\n";
	std::cerr << e.what() << std::endl;
	}
	catch(std::exception &e)
	{
	std::cerr << "Error opening database: crawlerurl.db"  << "\n";
	std::cerr << e.what() << std::endl;
	}

}

DBManager::~DBManager() {
	// TODO Auto-generated destructor stub
}
void DBManager::closeDB()
{
	try
	{
		crawelurl.close(0);
		urlq.close(0);
	}
	catch(DbException &e)
	{
	std::cerr << "Error closing database: crawlerurl.db" << "\n";
	std::cerr << e.what() << std::endl;
	}
	catch(std::exception &e)
	{
	std::cerr << "Error closing database:crawlerurl.db "  << "\n";
	std::cerr << e.what() << std::endl;
	}
}
void DBManager::writeDB(int db,string url,struct timeval *v)
{
	int ret;
	Dbt key(const_cast<char*>(url.c_str()), url.size()+1);
	Dbt data(v, sizeof(timeval));
	if(db == 0) //craweldb
	{
		ret = crawelurl.put(NULL, &key, &data, 0);
		if (ret == DB_KEYEXIST) {
		printf("Put crawelurl failed because key %s already exists",url.c_str());
		}
	}
	else
	{
		ret = urlq.put(NULL, &key, &data, 0);
		if (ret == DB_KEYEXIST) {
		printf("Put urlq failed because key %s already exists",url.c_str());
		}
	}
}
bool DBManager::readDB(int db,string url,struct timeval *v)
{
	int ret;
	Dbt key(const_cast<char*>(url.c_str()), url.size()+1);
	Dbt data(v, sizeof(timeval));
	if(db == 0) //craweldb
	{
		ret = crawelurl.get(NULL, &key, &data, 0);
		if (ret == DB_NOTFOUND) {
			return false;
		}
	}
	else
	{
		ret = urlq.get(NULL, &key, &data, 0);
		if (ret == DB_NOTFOUND) {
			return false;
		}
	}
	return true;
}
void DBManager::deleteDB(int db,string url)
{
	int ret;
	Dbt key(const_cast<char*>(url.c_str()), url.size()+1);
	if(db == 0) //craweldb
	{
		ret = crawelurl.del(NULL, &key,0);
	}
	else
	{
		ret = urlq.del(NULL, &key,0);
	}
}

