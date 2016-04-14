#ifndef __SPATIAL_COMPONENT_H__
#define __SPATIAL_COMPONENT_H__

#include "box.h"
#include <memory>
#include <vector>

namespace Spatial {

class Component {
public:
    typedef CommonCase::Point<int> Point;
    typedef CommonCase::Box<int> Box;
    typedef int BoxId;

    struct InputExchange {
        typedef std::vector<InputExchange> vector;
        Box ghost, donor_;
        BoxId source;
    };

    struct OutputExchange {
        typedef std::vector<OutputExchange> vector;
        Box donor, ghost_;
        std::vector<BoxId> destinations;
    };

    Component();
    Box const& getBox() const;
    BoxId getBoxId() const;

    InputExchange::vector const& getInputExchange() const;
    OutputExchange::vector const& getOutputExchange() const;

private:
    class Impl;
    std::shared_ptr<Impl> impl;
};



} // namespace Spatial

#endif //__SPATIAL_COMPONENT_H__
