

#include <FUi.h>
#include <FLocations.h>
#include "LocationManagerThread.h"
#include "Location/gps_location.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Locations;

LocationManagerThread::LocationManagerThread(void)
	: Tizen::Base::Runtime::Thread()
	//, __pUiControl(null)
{
}

LocationManagerThread::~LocationManagerThread(void)
{
}

result
LocationManagerThread::Construct(/*const Tizen::Ui::Control& uiControl*/)
{
	//__pUiControl = &uiControl;
	return Thread::Construct();
}

Object* LocationManagerThread::Run(void)
{
	result lastResult = E_SUCCESS;
	LocationCriteria locCriteria;

	locCriteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);

	Location location = LocationProvider::GetLocation(locCriteria);

	AppLog("Requested for current location in new thread.");

	lastResult = GetLastResult(); //TODO: should check for user conset first time only

	if (lastResult == E_USER_NOT_CONSENTED)
	{
		//__pUiControl->SendUserEvent(LocationManagerMainForm::LOC_MGR_NOTIFY_ERROR, null);
		AppLogDebug("no fucking permissions...lastResult == E_USER_NOT_CONSENTED");
		//TODO: Get last known location

		return 0;
	}

	Coordinates coords = location.GetCoordinates();
	double latitude = coords.GetLatitude();
	double longitude = coords.GetLongitude();

	AppLogDebug("latitude = %f longitude = %f", latitude, longitude);

	CCCoreLocation::getInstance()->getLocationDone((float)latitude, (float)longitude);
	//[locationManager stopUpdatingLocation];
	//TODO: Stop gps now

#if 0
	ArrayList* pList = new (std::nothrow) ArrayList();
	Location* pLocation = new (std::nothrow) Location(location);

	pList->Construct();
	pList->Add(*pLocation);
	//__pUiControl->SendUserEvent(LocationManagerMainForm::LOC_MGR_DRAW_SYNC_LOC_UPDATE, pList);
	//TODO: notify main app
#endif
	return 0;
}
