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


Component::InputExchange::vector const& Component::getInputExchange() const { return container.getInputExchange(boxId); }
Component::OutputExchange::vector const& Component::getOutputExchange() const { return container.getOutputExchange(boxId); }

Component::InputExchange::vector const& Component::getInputExchange(unsigned int width) const { return container.getInputExchange(boxId, width); }
Component::OutputExchange::vector const& Component::getOutputExchange(unsigned int width) const { return container.getOutputExchange(boxId, width); }

std::vector<Component::BoxId> const& Component::getNeighbors() const { container.getNeighbors(boxId); }


} // namespace Spatial