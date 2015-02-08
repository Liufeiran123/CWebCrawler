/*
 * CharsetConverter.h
 *
 *  Created on: 2015年2月4日
 *      Author: lfr
 */

#ifndef CHARSETCONVERTER_H_
#define CHARSETCONVERTER_H_

#include <iconv.h>
#include <errno.h>
#include <string>

using namespace std;

class CharsetConverter {
public:
	CharsetConverter();
	virtual ~CharsetConverter();

public:
	static iconv_t Open(string &tocode,string &fromcode);
	static string Convert(iconv_t cd,const string &input);
	static int Close(iconv_t cd);
};

#endif /* CHARSETCONVERTER_H_ */
