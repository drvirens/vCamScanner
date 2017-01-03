#include "Sounds.h"


 // Global checker sound 
bool gSoundCheck = true;
bool gSoundMediaLoaded = false; //viren 
/*
===================================================================================
Class PreloadSounds
===================================================================================
*/

// STATIC 
std::map <std::string , std::string> PreloadSounds::AllSounds;

/*
====================
CorrectVolume
====================
*/
void PreloadSounds::CorrectVolume()
{
	// set default volume
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
}

/*
====================
Load
====================
*/
void PreloadSounds::Load()
{
	using namespace cocos2d;
 
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		AllSounds["BgMusic"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/bg_music.ogg"));
		AllSounds["RedHatJump"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/red_hat_jump.ogg"));
		AllSounds["RedHatDeath"]	= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/red_hat_death.ogg"));
		AllSounds["BulletAttack"]	= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/bullet_attack.ogg"));
		AllSounds["WolfDeath"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/wolf_death.ogg"));

	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		
		//AllSounds["BgMusic"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/bg_music.ogg"));
    AllSounds["BgMusic"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/bg_music.ogg"));
		AllSounds["RedHatJump"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/red_hat_jump.wav"));
		AllSounds["RedHatDeath"]	= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/red_hat_death.wav"));
		AllSounds["BulletAttack"]	= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/bullet_attack.wav"));
		AllSounds["WolfDeath"]		= std::string(CCFileUtils::fullPathFromRelativePath("Sounds/wolf_death.wav"));
  
  #elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  
  std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/bg_music.wav");
  AllSounds["BgMusic"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/red_hat_jump.wav");
  AllSounds["RedHatJump"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/red_hat_death.wav");
  AllSounds["RedHatDeath"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/bullet_attack.wav");
  AllSounds["BulletAttack"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/wolf_death.wav");
  AllSounds["WolfDeath"] = fullPath;
  
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
  
  std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/bg_music.ogg");
  AllSounds["BgMusic"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/red_hat_jump.wav");
  AllSounds["RedHatJump"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/red_hat_death.wav");
  AllSounds["RedHatDeath"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/bullet_attack.wav");
  AllSounds["BulletAttack"] = fullPath;
  
  fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Sounds/wolf_death.wav");
  AllSounds["WolfDeath"] = fullPath;


	#endif

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic( AllSounds["BgMusic"].c_str() );
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( AllSounds["RedHatJump"].c_str() );
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( AllSounds["RedHatDeath"].c_str() );
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( AllSounds["BulletAttack"].c_str() );
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( AllSounds["WolfDeath"].c_str() );
}

/*
====================
PlayBackGround
====================
*/
void PreloadSounds::PlayBackGround()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(PreloadSounds::AllSounds["BgMusic"].c_str(), true);
}

/*
====================
PlayBackGround
====================
*/
void PreloadSounds::StopBackGround()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
}

/*
===================================================================================
Class SoundsRedHat
===================================================================================
*/
SoundsRedHat::~SoundsRedHat()
{
	//
}
void SoundsRedHat::PlayAttack()
{
	//
}
void SoundsRedHat::PlayDeath() 
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(PreloadSounds::AllSounds["RedHatDeath"].c_str(), false);
}
void SoundsRedHat::PlayJump()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(PreloadSounds::AllSounds["RedHatJump"].c_str(), false);
}

/*
===================================================================================
Class SoundsRedHat
===================================================================================
*/
SoundsWolf::~SoundsWolf()
{
	//
}
void SoundsWolf::PlayAttack() 
{
	//
}
void SoundsWolf::PlayJump()
{
	//
}
void SoundsWolf::PlayDeath() 
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(PreloadSounds::AllSounds["WolfDeath"].c_str(), false);
}

/*
===================================================================================
Class SoundsBullet
===================================================================================
*/
SoundsBullet::~SoundsBullet()
{
	//
}
void SoundsBullet::PlayAttack() 
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(PreloadSounds::AllSounds["BulletAttack"].c_str(), false);
}
void SoundsBullet::PlayJump()
{
	//
}
void SoundsBullet::PlayDeath() 
{
	//	
}

 