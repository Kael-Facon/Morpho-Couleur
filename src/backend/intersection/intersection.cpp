#include "intersection.hh"

void Intersection::update(const Point3& origin_, const Vector3& dir_) {
    origin = origin_;
    dir = dir_;
    inter_loc = null_point;
};

Intersection::Intersection(const Point3& origin_, const Vector3& dir_) {
    origin = origin_;
    dir = dir_;
    inter_loc = null_point;
}