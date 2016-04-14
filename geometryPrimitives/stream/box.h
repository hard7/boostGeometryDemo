#ifndef __GEOMETRY_BOX_STREAM_H__
#define __GEOMETRY_BOX_STREAM_H__

#include "box.h"
#include <iostream>

namespace CommonCase {

    template <typename T>
    std::ostream& operator<< (std::ostream& os, Box<T> const& box) {
        os << "[";
        os << "(" << box.lo().x() << ", " << box.hi().x() << "); ";
        os << "(" << box.lo().y() << ", " << box.hi().y() << "); ";
        os << "(" << box.lo().z() << ", " << box.hi().z() << ")";
        os << "]";
        return os;
    }

} // namespace CommonCase


#endif //__GEOMETRY_BOX_STREAM_H__
