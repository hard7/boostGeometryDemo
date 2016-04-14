#ifndef __SPATIAL_CONTAINER_H__
#define __SPATIAL_CONTAINER_H__

#include "Spatial/Component.h"
#include <memory>
#include <vector>

namespace Spatial {

class Container {
public:
    typedef Spatial::Component::Box Box;

private:
    typedef std::vector<Spatial::Component> _implContainer;
    typedef _implContainer::iterator iterator;
    typedef _implContainer::const_iterator const_iterator;

public:
    Container();

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

    inline void demo();

} // namespace Spatial

//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "box.h"

void Spatial::demo() {
    using std::cout;
    using std::endl;
    cout << "demo begin" << endl;

    const Spatial::Container sc;
    for(auto& box: sc) {
//        cout << box.lo().x() << endl;
    }
}

#endif //__SPATIAL_CONTAINER_H__
