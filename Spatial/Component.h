#ifndef __SPATIAL_COMPONENT_H__
#define __SPATIAL_COMPONENT_H__

#include "box.h"
#include <memory>
#include <vector>

namespace Spatial {

class Container;

class Component {
public:
    typedef CommonCase::Point<int> Point;
    typedef CommonCase::Box<int> Box;
    typedef int BoxId;
    typedef std::vector<BoxId> BoxIdGroup;

    struct InputExchange {
        typedef std::vector<InputExchange> vector;
        Box ghost, donor_;
        BoxId source;
    };

    struct OutputExchange {
        typedef std::vector<OutputExchange> vector;
        Box donor, ghost_;
        BoxIdGroup destinations;
    };

    Component(Container& container, BoxId boxId);
    Box const& getBox() const;
    BoxId getBoxId() const;

    InputExchange::vector const& getInputExchange() const;
    OutputExchange::vector const& getOutputExchange() const;

    InputExchange::vector const& getInputExchange(unsigned int width) const;
    OutputExchange::vector const& getOutputExchange(unsigned int width) const;

    std::vector<BoxId> const& getNeighbors() const;

private:
    Container& container;
    BoxId boxId;
};



} // namespace Spatial

#endif //__SPATIAL_COMPONENT_H__
