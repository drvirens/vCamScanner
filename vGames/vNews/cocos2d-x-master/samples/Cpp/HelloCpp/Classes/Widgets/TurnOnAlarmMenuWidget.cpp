#include "TurnOnAlarmMenuWidget.h"
using namespace cocos2d;
TurnOnAlarmMenuWidget::TurnOnAlarmMenuWidget(
        TurnOnAlarmMenuDelegatePtr delegate)
    : _delegate(delegate)
{

}


void TurnOnAlarmMenuWidget::onInit()
{
#if 0 //original code
    _rs = getApi()->reserveSpace(Anchor::Right, Anchor::Bottom,
                                 MTileSize(6,2*3));
#endif
//viren+ increase the reserve space

  _rs = getApi()->reserveSpace(Anchor::Right, Anchor::Bottom,
                               MTileSize(6,2*4));


//viren-
    displayButtons();
}

void TurnOnAlarmMenuWidget::displayButtons()
{
    if(_rs.isDefined())
    {
        MTilePosition base_pos = _rs.getPosition();
        MTileSize base_size = MTileSize(6, 2);
      
        {
            MTile* tile = MTile::create(
                        "violet.png",
                        base_pos,
                        base_size);

            CCSize tile_size = tile->getInnerContentSize();
            CCLabelTTF* question = LF::label(R::tr(R::TurnOnAlarmMenuWidget_AlarmPurpose),
                                             LF::MEDIUM_FONT,
                                             CCSize(tile_size.width,0),
                                             kCCTextAlignmentCenter);
            tile->addChild(question,
                           Aligment::HCenter,
                           Aligment::VCenter,
                           0, LF::vfix(LF::MEDIUM_FONT));

            getApi()->addTile(tile);
        }
        {
            MTile* tile = MTile::create(
                        "blue.png",
                        MTilePosition(base_pos.x(),
                                      base_pos.y() + base_size.height()),
                        base_size,
                        this,
                        tile_selector(TurnOnAlarmMenuWidget::onWakeUpClick)
                        );
            addImageAndLabelToTile(tile, R::tr(R::TurnOnAlarmMenuWidget_WakeUp), "bed_icon.png");
            getApi()->addTile(tile);
        }
        {
        //viren: this is crashing on tizen so dont show
       #if (CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)
            MTile* tile = MTile::create(
                        "blue.png",
                        MTilePosition(base_pos.x(),
                                      base_pos.y() + base_size.height()*2),
                        base_size,
                        this,
                        tile_selector(TurnOnAlarmMenuWidget::onGoOutInTimeClick)
                        );
            addImageAndLabelToTile(tile, R::tr(R::TurnOnAlarmMenuWidget_WakeUpAndGoOut), "go_out.png");
            getApi()->addTile(tile);
        #endif
        }
      
        //viren+ add facebook button
      {
        const unsigned int theX = base_pos.x();// - base_size.width();
        
        MTile* tile = MTile::create(
                                    "blue.png",
                                    MTilePosition(theX,
                                                  base_pos.y() + base_size.height()*3),
                                    base_size,
                                    this,
                                    tile_selector(TurnOnAlarmMenuWidget::onPostOnFacebookClick)
                                    );
        addImageAndLabelToTile(tile, R::tr(R::TurnOnAlarmMenuWidget_PostOnFacebook), "go_out.png");
        getApi()->addTile(tile);
      }
        //viren-
    }
}


void TurnOnAlarmMenuWidget::onWakeUpClick(MTile *)
{
    if(_delegate.get())
    {
        _delegate->onWakeUpClick();
    }
}

void TurnOnAlarmMenuWidget::onGoOutInTimeClick(MTile *)
{
    if(_delegate.get())
    {
        _delegate->onGoOutInTimeClick();
    }
}

//viren+

//#include "webview_plugin/ZYWebView.h"
//#include "MAUtil/VirenString.h"
//#include "FacebookDemoMoblet.h"
//#include "Facebook/config.h"
//#include "cocos2d.h"

void testFaceBook() {
//  FacebookDemoMoblet *appMoblet = new FacebookDemoMoblet(CONFIG_APPLICATION_ID);
}

void TurnOnAlarmMenuWidget::onPostOnFacebookClick(MTile *)
{
//  testFaceBook();
}
//viren-



