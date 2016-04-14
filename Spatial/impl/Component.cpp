#include "../Component.h"
#include "box.h"

namespace Spatial {


struct SpatialComponent::Impl {
    Box box;
};


SpatialComponent::SpatialComponent() : impl(new Impl) { }

} // namespace Spatial