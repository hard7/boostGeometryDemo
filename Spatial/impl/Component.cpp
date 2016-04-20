#include "../Component.h"
#include "../Container.h"
#include "box.h"

namespace Spatial {


Component::Component(Container& container_, BoxId boxId_) : container(container_), boxId(boxId_) { }
Component::Box const& Component::getBox() const {
    return container.getBox(boxId);
}

Component::BoxId Component::getBoxId() const {
    return boxId;
}


Component::InputExchange::Collection const& Component::getInputExchange() const { return container.getInputExchange(boxId); }
Component::OutputExchange::Collection const& Component::getOutputExchange() const { return container.getOutputExchange(boxId); }

Component::InputExchange::Collection const& Component::getInputExchange(unsigned int width) const { return container.getInputExchange(boxId, width); }
Component::OutputExchange::Collection const& Component::getOutputExchange(unsigned int width) const { return container.getOutputExchange(boxId, width); }

Component::BoxIdCollection const& Component::getNeighbors() const { container.getNeighbors(boxId); }


} // namespace Spatial