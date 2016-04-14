#include "../Component.h"
#include "../Container.h"
#include "box.h"

namespace Spatial {

struct Component::Impl {
    Container& container;
    BoxId boxId;
    Impl(Container& container_, BoxId boxId_) : container(container_), boxId(boxId_) { }
};



Component::Component(Container& container, BoxId boxId) : impl(new Impl(container, boxId)) { }
Component::Box const& Component::getBox() const {

}

Component::BoxId Component::getBoxId() const {
    return impl->boxId;
}


} // namespace Spatial