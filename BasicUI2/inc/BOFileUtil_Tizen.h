/*
 * BOFileUtil_Tizen.h
 *
 *  Created on: Nov 27, 2016
 *      Author: virendrashakya
 */

#ifndef BOFILEUTIL_TIZEN_H_
#define BOFILEUTIL_TIZEN_H_


#include <BOFileUtil.h>

class BOFileUtil_Tizen : public BOFileUtil {
public:
	virtual void init();
	virtual string getWritablePath() const;
};


#endif /* BOFILEUTIL_TIZEN_H_ */
