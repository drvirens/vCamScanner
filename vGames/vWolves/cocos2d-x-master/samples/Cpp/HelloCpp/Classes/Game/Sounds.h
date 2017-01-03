/*
===================================================================================
Description
		REMARK
		
Copyright (c) TexnoDog, 2011.
Author	  Klimontov Michael (KlimontovM@gmail.com)
===================================================================================
*/

#ifndef __SOUNDS__H__
#define __SOUNDS__H__


#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include <map> 
#include <string>

#include "Definition.h"



// true - on sound 
// false - off 
extern bool gSoundCheck;

extern bool gSoundMediaLoaded; //viren: load sound delay to make startup faster

/*
===================================================================================
Interface PreISounds
===================================================================================
*/
struct ISounds
{
	virtual						~ISounds(){};
	
	virtual void				PlayDeath()		= 0;
	virtual void				PlayAttack()	= 0;
	virtual void				PlayJump()		= 0;
};

/*
===================================================================================
class PreloadSounds
===================================================================================
*/
class PreloadSounds
{
public:
	
	static void CorrectVolume();
	static void Load ();
	static void PlayBackGround();
	static void StopBackGround();
protected:

	static std::map <std::string , std::string> AllSounds;
};

/*
===================================================================================
class SoundsRedHat
===================================================================================
*/
class SoundsRedHat : public PreloadSounds,
					 public ISounds
{
public:
	virtual ~SoundsRedHat();

private:

	virtual void PlayDeath();
	virtual void PlayAttack();
 	virtual void PlayJump();
};

/*
===================================================================================
class  SoundsWolf
===================================================================================
*/
class SoundsWolf :	public PreloadSounds,
					public ISounds
{
public:
	virtual ~SoundsWolf();

private:

	virtual void PlayDeath();
	virtual void PlayAttack();
	virtual void PlayJump();
};

/*
===================================================================================
class  SoundsBullet
===================================================================================
*/
class SoundsBullet : public PreloadSounds,
					 public ISounds
{
public:
	virtual ~SoundsBullet();

private:

	virtual void PlayDeath();
	virtual void PlayAttack();
	virtual void PlayJump();
};


#endif //__SOUNDS__H__