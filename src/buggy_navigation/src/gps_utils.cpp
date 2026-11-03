#include "buggy_navigation/gps_utils.hpp"

#include <cmath>

namespace buggy_navigation
{

namespace
{

constexpr double EARTH_RADIUS = 6378137.0;

constexpr double DEG_TO_RAD =
    3.14159265358979323846 / 180.0;

}

LocalPoint gps_to_local(
    const GpsPoint & point,
    const GpsPoint & origin)
{
    const double lat = point.latitude * DEG_TO_RAD;
    const double lat0 = origin.latitude * DEG_TO_RAD;

    const double d_lat =
        (point.latitude - origin.latitude) * DEG_TO_RAD;

    const double d_lon =
        (point.longitude - origin.longitude) * DEG_TO_RAD;

    LocalPoint result;

    result.x =
        d_lon * EARTH_RADIUS * std::cos(lat0);

    result.y =
        d_lat * EARTH_RADIUS;

    return result;
}

}  // namespace buggy_navigation
