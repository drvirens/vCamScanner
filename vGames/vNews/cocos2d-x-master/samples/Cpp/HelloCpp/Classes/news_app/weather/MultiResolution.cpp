#include "MultiResolution.h"


float MultiResolution::getScale()
{	
	CCSize size = CCEGLView::sharedOpenGLView()->getFrameSize();
	if (size.width >= 320 && size.width <= 480)
		return 1.0;
	else if(size.width > 480 && size.width <= 640)
		return 1.5;
	else
		return 2.5;
}



