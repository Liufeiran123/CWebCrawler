/*
 * CharsetConverter.cpp
 *
 *  Created on: 2015年2月4日
 *      Author: lfr
 */

#include "CharsetConverter.h"

CharsetConverter::CharsetConverter() {
	// TODO Auto-generated constructor stub

}

CharsetConverter::~CharsetConverter() {
	// TODO Auto-generated destructor stub
}


iconv_t CharsetConverter::Open(string &tocode,string &fromcode)
{
	return iconv_open(tocode.c_str(), fromcode.c_str());
}
string CharsetConverter::Convert(iconv_t cd,const string &input)
{
	    const char *inbuf = input.c_str();
		size_t inbytesleft = input.length();

		size_t outbuf_len = 2 * input.length();
		char *outbuf_start = new char[outbuf_len];
		char *outbuf = outbuf_start;
		size_t outbytesleft = outbuf_len;
		size_t ret;
		ret = iconv(cd, const_cast<char**>(&inbuf), &inbytesleft, &outbuf, &outbytesleft);

		int e = errno;
		if((size_t)-1 == ret )
		{
			return string();
		}
		string out(outbuf_start, outbuf_len - outbytesleft);
		delete [] outbuf_start;
		return out;
}
int CharsetConverter::Close(iconv_t cd)
{
	return iconv_close(cd);
}
