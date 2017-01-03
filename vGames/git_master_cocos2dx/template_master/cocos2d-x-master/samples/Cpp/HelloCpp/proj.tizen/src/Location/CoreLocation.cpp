

#include "Location/LocationManagerMainForm.h"
#include "Location/CoreLocation_interface.h"
#include "Location/gps_location_base.h"
#include "cocos2d.h"


static CoreLocationImpl * myinstanceT=NULL;

CoreLocationImpl * CoreLocationImpl::getInstance() {
    if (myinstanceT==NULL) {
        myinstanceT=new CoreLocationImpl();
    }
    return myinstanceT;
}

CoreLocationImpl::CoreLocationImpl( void )
: self( NULL )
{
}

CoreLocationImpl::~CoreLocationImpl( void )
{
    AppLogDebug("WARNING CoreLocationImpl::~CoreLocationImpl" );
    delete self; self = 0;
}

bool CoreLocationImpl::init( void )
{
	self = new LocationManagerMainForm();
	self->Initialize();
	self->GetCurrentLocation();
    return true;
}

void CoreLocationImpl::dealloc ( void ) {
	AppLogDebug("CoreLocationImpl::dealloc : cancel location updattes");
	self->OnTerminating();
	this->cancel();
}

void CoreLocationImpl::cancel () {
	CCAssert(self != 0, "self is NULL pointer");
	self->CancelLocationUpdates();
}

float CoreLocationImpl::getLastKnownLongitude() {
	CCLOG("CoreLocationImpl::getLastKnownLongitude");
	double longi = self->GetLastKnownLongitude();
	return (float)longi;
}
float CoreLocationImpl::getLastKnownLatitude() {
	CCLOG("CoreLocationImpl::getLastKnownLatitude");
	double lati = self->GetLastKnownLatitude();
	return (float)lati;
}




