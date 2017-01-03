

#ifndef _LOCATION_MANAGER_MAIN_FORM_H_
#define _LOCATION_MANAGER_MAIN_FORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FLocations.h>
#include <FUi.h>

class LocationManagerThread;

class LocationManagerMainForm
	: public Tizen::Locations::ILocationProviderListener
 	, public Tizen::App::IAppControlResponseListener
{
public:
	LocationManagerMainForm(void);
	virtual ~LocationManagerMainForm(void);
	bool Initialize(void);

	virtual result OnTerminating(void);
	void GetCurrentLocation();
	void CancelLocationUpdates();
	double GetLastKnownLongitude();
	double GetLastKnownLatitude();

	virtual void OnLocationUpdated(const Tizen::Locations::Location& location);
	virtual void OnLocationUpdateStatusChanged(Tizen::Locations::LocationServiceStatus status);
	virtual void OnRegionEntered(Tizen::Locations::RegionId regionId);
	virtual void OnRegionLeft(Tizen::Locations::RegionId regionId);
	virtual void OnRegionMonitoringStatusChanged(Tizen::Locations::LocationServiceStatus status);
	virtual void OnAccuracyChanged(Tizen::Locations::LocationAccuracy accuracy);
	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

	virtual void OnAppControlCompleteResponseReceived(const Tizen::App::AppId &appId, const Tizen::Base::String &operationId, Tizen::App::AppCtrlResult appControlResult, const Tizen::Base::Collection::IMap *pExtraData){}

	void DrawLocationInformation(const Tizen::Locations::Location& location);
	void AddMonitoringRegion();
	void ShowMessageBox(const Tizen::Base::String& title, const Tizen::Base::String& message);
	void LogLocationInfo(const Tizen::Locations::Location location);
	bool CheckLocationSetting(void);

private:
	void LaunchLocationSettings(void);
	result OnInitializing(void);

public:
	static const RequestId LOC_MGR_DRAW_SYNC_LOC_UPDATE = 101;
	static const RequestId LOC_MGR_NOTIFY_ERROR = 102;

private:
	enum ViewType
	{
		VIEW_TYPE_NONE,
		VIEW_TYPE_LOCTION_UPDATE,
		VIEW_TYPE_REGION_MONITORING,
	}__viewType;


	static const int ID_CONTEXT_UPDATE_INTERVAL = 208;
	static const int ID_CONTEXT_UPDATE_DISTANCE = 209;

	static const int ID_CONTEXT_GET_LAST = 210;
	static const int ID_CONTEXT_GET_CURRENT = 211;

	static const int ID_POPUP_REGION_OK = 212;
	static const int ID_POPUP_REGION_CANCEL = 213;

	Tizen::Locations::LocationProvider* __pLocProvider;
	LocationManagerThread* __pLocationManagerThread;
	Tizen::Locations::RegionId __regionId;
	Tizen::Locations::Coordinates __regionCenter;
	double __regionRadius;
	bool __isUpdateInProgress;
};

#endif	//_LOCATION_MANAGER_MAIN_FORM_H_
