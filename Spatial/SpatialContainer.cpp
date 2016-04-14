#include "SpatialContainer.h"
#include "box.h"

namespace Spatial {

struct SpatialContainer::Impl {
    Container container = {Box({1, 2, 5}, {1, 2, 6}), Box({10, 20, 50}, {10, 20, 60})};
};

SpatialContainer::SpatialContainer() : impl(new Impl) { }

SpatialContainer::iterator SpatialContainer::begin() { return impl->container.begin(); }
SpatialContainer::iterator SpatialContainer::end() { return impl->container.end(); }

SpatialContainer::const_iterator SpatialContainer::begin() const { return impl->container.cbegin(); }
SpatialContainer::const_iterator SpatialContainer::end() const { return impl->container.cend(); }

} // namespace Spatial