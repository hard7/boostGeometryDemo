#ifndef __SPATIAL_COMPONENT_H__
#define __SPATIAL_COMPONENT_H__

#include "box/fwd.h"
#include <memory>

namespace Spatial {

class Component {
public:
    typedef CommonCase::Box<int> Box;

    Component();

private:
    class Impl;
    std::shared_ptr<Impl> impl;
};

} // namespace Spatial

#endif //__SPATIAL_COMPONENT_H__
