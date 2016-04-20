#ifndef __SPATIAL_CONTAINER_H__
#define __SPATIAL_CONTAINER_H__

#include "Spatial/Component.h"
#include <memory>
#include <vector>

namespace Spatial {

class Container {
public:
    typedef Component::Box Box;
    typedef Component::Point Point;
    typedef Component::BoxId BoxId;

private:
    typedef std::vector<Spatial::Component> _implContainer;
    typedef std::vector<Box> Boxes;
    typedef _implContainer::iterator iterator;
    typedef _implContainer::const_iterator const_iterator;

public:
    Container(std::vector<Box> const& values, unsigned int borderWidth = 1);

    Box const& getBox(BoxId boxId) const;
    BoxId getBoxId(Box const& box) const;
    std::vector<BoxId> const& getNeighbors(BoxId boxId) const;

    Component::InputExchange::Collection const& getInputExchange(BoxId boxId) const;
    Component::InputExchange::Collection const& getInputExchange(BoxId boxId, unsigned int width) const;

    Component::OutputExchange::Collection const& getOutputExchange(BoxId boxId) const;
    Component::OutputExchange::Collection const& getOutputExchange(BoxId boxId, unsigned int width) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    class Impl;
    std::shared_ptr<Impl> impl;
};

} // namespace Spatial

#endif //__SPATIAL_CONTAINER_H__
