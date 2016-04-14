#ifndef __SPATIAL_CONTAINER_H__
#define __SPATIAL_CONTAINER_H__

#include "box/fwd.h"
#include <memory>
#include <vector>

namespace Spatial {

class SpatialContainer {
public:
    typedef CommonCase::Box<int> Box;

private:
    typedef std::vector<Box> Container;
    typedef Container::iterator iterator;
    typedef Container::const_iterator const_iterator;

public:
    SpatialContainer();

//    class iterator;
    iterator begin();
    iterator end();

//    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;


private:
    class Impl;
    std::shared_ptr<Impl> impl;
};

    inline void demo();

} // namespace Spatial

//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "box.h"

void Spatial::demo() {
    using std::cout;
    using std::endl;
    cout << "demo begin" << endl;

    const SpatialContainer sc;
    for(auto& box: sc) {
        cout << box.lo().x() << endl;
    }
}

#endif //__SPATIAL_CONTAINER_H__
