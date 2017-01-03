

#ifndef CoreLocation_interface_h
#define CoreLocation_interface_h

class LocationManagerMainForm;

class CoreLocationImpl
{
public:
    CoreLocationImpl ( void );
    ~CoreLocationImpl( void );
    static CoreLocationImpl * getInstance();
    bool init( void );
    void dealloc ( void );
    void cancel();
    float getLastKnownLongitude();
    float getLastKnownLatitude();
    
private:
    LocationManagerMainForm* self;
};


#endif


