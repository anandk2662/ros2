namespace buggy_navigation
{

struct GpsPoint
{
    double latitude;
    double longitude;
};

struct LocalPoint
{
    double x;
    double y;
};

LocalPoint gps_to_local(
    const GpsPoint & point,
    const GpsPoint & origin
);

} 
