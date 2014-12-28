/*
 * chajian.h
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#ifndef CHAJIAN_H_
#define CHAJIAN_H_

class MessageComponent {
public:
	MessageComponent();
	virtual ~MessageComponent();
public:
	virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,void*/*函数返回值*/) =0;
};

#endif /* CHAJIAN_H_ */
