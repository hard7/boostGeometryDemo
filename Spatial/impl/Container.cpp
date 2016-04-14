#include "../Container.h"
#include "box.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>

namespace {
    typedef Spatial::Component::Point Point;
    typedef Spatial::Component::Box Box;
}

BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(Point, Point::type, boost::geometry::cs::cartesian, x, y, z, x, y, z);
BOOST_GEOMETRY_REGISTER_BOX(Box, Point, lo, hi);

namespace Spatial {

struct Container::Impl {
    _implContainer container;
    const std::vector<Box> boxes;

    Impl(Boxes const& boxes_) : boxes(boxes_) {
//        container.resize(boxes.size());
    }
};


Container::Container(Boxes const& boxes) : impl(new Impl(boxes)) { }

Container::iterator Container::begin() { return impl->container.begin(); }
Container::iterator Container::end() { return impl->container.end(); }

Container::const_iterator Container::begin() const { return impl->container.cbegin(); }
Container::const_iterator Container::end() const { return impl->container.cend(); }

Container::const_iterator Container::cbegin() const { return impl->container.cbegin(); }
Container::const_iterator Container::cend() const { return impl->container.cend(); }

} // namespace Spatial