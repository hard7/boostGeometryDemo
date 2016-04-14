#include <iostream>

#include "geometryPrimitives/point.h"
#include "geometryPrimitives/box.h"
#include "defineSharedArea.hh"
#include <vector>

using std::cout;
using std::endl;


struct A {
    typedef int Type;
};

template < typename T >
struct B {
    B(A a) {}
};



int main() {
    using Box = CommonCase::Box<int>;
    std::vector<Box> boxes = { Box({0,0,0}, {10, 10, 10}), Box({10, 0, 0}, {20, 10, 10}) };
//    SpatialContainer sc(boxes.begin(), boxes.end());

//    SpatialContainer<CommonCase::Box<int> > sc = makeSpatialContainer(boxes.begin());

    int nums[] = {1,2,3};

//    defineSharedArea(std::begin(boxes), std::end(boxes));
//    defineSharedArea(A(), A());

    Spatial::demo();
    return 0;
}

/*
 * «std::vector<CommonCase::Box<int> >::const_iterator {aka __gnu_cxx::__normal_iterator<const CommonCase::Box<int>*, std::vector<CommonCase::Box<int> > >}»
 * to «SpatialContainer<int>::const_iterator {aka __gnu_cxx::__normal_iterator<const SpatialComponent<int>*, std::vector<SpatialComponent<int>, std::allocator<SpatialComponent<int> > > >}»
 *
 */