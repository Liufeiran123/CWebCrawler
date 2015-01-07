/*
 * ImageURLFIlter.cpp
 *
 *  Created on: 2015年1月7日
 *      Author: lfr
 */

#include "ImageURLFIlter.h"
#include <fstream>
using namespace std;

ImageURLFIlter::ImageURLFIlter() {
	// TODO Auto-generated constructor stub
	initfilter();
}

ImageURLFIlter::~ImageURLFIlter() {
	// TODO Auto-generated destructor stub
}

bool ImageURLFIlter::doFilter(string c)
{
	for(list<string>::iterator iter = strfilter.begin();iter!= strfilter.end();++iter)
	{
		if(c.rfind(*iter) != string::npos)
		{
			return false;
		}
	}
	return true;
}
void ImageURLFIlter::initfilter()
{
	ifstream ifs("/home/lfr/workspace3/crawler/config/imagefilter");
	string s;
	while(getline(ifs,s))
	{
		strfilter.push_back(s);
	}

}
