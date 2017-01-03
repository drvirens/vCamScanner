

#ifndef FACEBOOKDEMOSCREEN_H_
#define FACEBOOKDEMOSCREEN_H_

//#include <MAUtil/Environment.h>
//
//#include "ListItem.h"
//
//
//#include <NativeUI/Button.h>
//#include <NativeUI/ListView.h>
//#include <NativeUI/ListViewListener.h>
//#include <NativeUI/Screen.h>
//#include <NativeUI/VerticalLayout.h>

namespace FacebookDemoGUI
{

class FacebookDemoScreen //: public NativeUI::Screen, public MAUtil::KeyListener
{
public:
	FacebookDemoScreen(FacebookDemoScreen *prevScreen);
	virtual void show();
	void receiveKeyEvents(bool receive);

	//void add(ListItem *btn);

	void setListItemsColor(int color);
	void setScreenColor(int color);

	bool isEmpty() const;

	void clearScreenAfterLosingFocus(bool clearScreen);

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode);

	FacebookDemoScreen *getPreviousScreen();

	virtual ~FacebookDemoScreen();

protected:
	virtual void back();

private:
//	virtual int addChild(NativeUI::Widget* widget);

protected:
	FacebookDemoScreen 			*mPreviousScreen;
//
//	NativeUI::VerticalLayout 	*mLayout;
//	NativeUI::ListView 			*mList;
//	NativeUI::Button			*mBackButton;

	//we can't set the font color for a ListViewItem yet, so we set
	//the background of the item. The default font color on Android is white
	//and the default font color on iPhone is black.
	//So we set the background color of the items to black for Android and
	//light gray for iPhone.
	int							mItemsColor_Android;
	int 						mItemsColor_iPhone;

	int							mScreenColor;

	bool 						mClearScreenAfterLosingFocus;
};


}//namespace FacebookDemoGUI


#endif /* FACEBOOKDEMOSCREEN_H_ */
