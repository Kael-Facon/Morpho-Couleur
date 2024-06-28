#pragma once

#include "../utils/color.hh"
#include "../utils/vector3.hh"
#include <climits>
static Point3 null_point = Point3(INT_MAX, INT_MAX, INT_MAX);

class Intersection
{
    public :
        Intersection()= default;
        Intersection(const Point3& origin_, const Vector3& dir_);

        void update(const Point3& origin_, const Vector3& dir_);

        Point3 origin;
        Vector3 dir;
        Point3 inter_loc;
};