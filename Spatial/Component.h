#ifndef __SPATIAL_COMPONENT_H__
#define __SPATIAL_COMPONENT_H__

#include "box.h"
#include <vector>

namespace Spatial {

class Container;

class Component {
public:
    typedef CommonCase::Point<int> Point;
    typedef CommonCase::Box<int> Box;
    typedef int BoxId;
    typedef std::vector<BoxId> BoxIdCollection;

    struct Destination { Box ghost; BoxId destinationId; };
    typedef std::vector<Destination> DestinationCollection;

    struct InputExchange {
        typedef std::vector<InputExchange> Collection;
        Box ghost, donor_;
        BoxId sourceBoxId;
    };

    struct OutputExchange {
        typedef std::vector<OutputExchange> Collection;
        Box donor /*, ghost_*/ ;
        DestinationCollection /*BoxIdCollection*/ destinations;
    };

    Component(Container& container, BoxId boxId);
    Box const& getBox() const;
    BoxId getBoxId() const;

    InputExchange::Collection const& getInputExchange() const;
    OutputExchange::Collection const& getOutputExchange() const;

    InputExchange::Collection const& getInputExchange(unsigned int width) const;
    OutputExchange::Collection const& getOutputExchange(unsigned int width) const;

    BoxIdCollection const& getNeighbors() const;

private:
    Container& container;
    BoxId boxId;
};



} // namespace Spatial

#endif //__SPATIAL_COMPONENT_H__
