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
    typedef std::vector<Box> Boxes;
    typedef _implContainer::iterator iterator;
    typedef _implContainer::const_iterator const_iterator;

public:
    Container(std::vector<Box> const& values);

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

    void demo();

} // namespace Spatial

//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "box.h"

inline void Spatial::demo() {
    using Box = Component::Box;
    using Point = CommonCase::Point<Box::type>;
    using std::cout;
    using std::endl;

    cout << "demo begin" << endl;
    std::vector<Component::Box> boxes = {Box(Point(1,2,3), Point(10,20,30)), Box(Point(10,20,30), Point(100,200,300)) };

    const Spatial::Container sc(boxes);
    for(auto& box: sc) {
//        cout << box.lo().x() << endl;
    }
}

#endif //__SPATIAL_CONTAINER_H__
