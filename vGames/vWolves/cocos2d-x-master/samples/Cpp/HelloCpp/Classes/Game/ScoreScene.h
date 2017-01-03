#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"

class ScoreScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene*			scene( int score);
	virtual bool						init();  
	CREATE_FUNC(ScoreScene);
    
	// a selector callback
	virtual void						menuCloseCallback(CCObject* pSender);
	virtual void						menuAgainPlayCallback(CCObject* pSender);

	void								UpdateScore( int score );
private:
	int									m_score;
};

#endif // __SCORE_SCENE_H__
