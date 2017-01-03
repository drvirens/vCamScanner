

#include "../../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"

USING_NS_CC;

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void ApplicationInitialized(void) {
	AppDelegate *pAppDelegate = new AppDelegate(); //where to delete it?
	CCLOG("ApplicationInitialized: getOpenGLView is NULL so create AppDelegate and run");
	CCEGLView *eglView = CCEGLView::sharedOpenGLView();

	//viren+
	//	eglView->setFrameSize(1280, 720); //<--- original
//		eglView->setFrameSize(720, 1280); //for portrait mode
	{
		Tizen::Graphics::Rectangle rect = CCOspApplication::GetInstance()->getCCOspForm()->GetBounds();
//		eglView->setFrameSize(rect.width, rect.height);
//		eglView->setFrameSize(rect.height, rect.width );
		eglView->setFrameSize(720, 1280);
	}
	//viren-

	CCApplication::sharedApplication()->run();
}

_EXPORT_ int OspMain(int argc, char *pArgv[])
{
    AppLog("Application started.");
    ArrayList args(SingleObjectDeleter);
    args.Construct();
    for (int i = 0; i < argc; i++)
    {
    	String* arg = new (std::nothrow) String(pArgv[i]);
        args.Add(arg);
    }

    CCOspApplication::SetApplicationInitializedCallback(ApplicationInitialized);
    //CCOspApplication::SetScreenOrientation(Tizen::Ui::ORIENTATION_LANDSCAPE);
    CCOspApplication::SetScreenOrientation(Tizen::Ui::ORIENTATION_PORTRAIT);
    result r = Tizen::App::Application::Execute(CCOspApplication::CreateInstance, &args);
    TryLog(r == E_SUCCESS, "[%s] Application execution failed", GetErrorMessage(r));
    AppLog("Application finished.");

    return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
