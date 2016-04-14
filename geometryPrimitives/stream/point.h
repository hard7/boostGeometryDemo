#ifndef __GEOMETRY_POINT_STREAM_H__
#define __GEOMETRY_POINT_STREAM_H__

#include "point.h"
#include <iostream>

namespace CommonCase {

    template <typename T>
    std::ostream& operator<< (std::ostream& os, Point<T> const& point) {
        os << "{" << point.x() << ", " << point.y() << ", " << point.z() << "}";
        return os;
    }

} // namespace CommonCase

#endif //__GEOMETRY_POINT_STREAM_H__
