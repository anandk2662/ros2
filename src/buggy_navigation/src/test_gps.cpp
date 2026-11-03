#include <iostream>

#include "buggy_navigation/gps_utils.hpp"

int main()
{
    buggy_navigation::GpsPoint origin{
        12.934500,
        77.534100
    };

    buggy_navigation::GpsPoint point{
        12.934600,
        77.534200
    };

    auto local =
        buggy_navigation::gps_to_local(
            point,
            origin
        );

    std::cout << "x = "
              << local.x
              << " m\n";

    std::cout << "y = "
              << local.y
              << " m\n";

    return 0;
}