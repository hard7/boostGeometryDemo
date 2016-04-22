#include "point.h"
#include "box.h"
#include "Spatial/Container.h"
#include "stream/point.h"
#include "stream/box.h"
#include "algo_box.h"

#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using std::cout;
using std::endl;


std::vector<Spatial::Container::Box> generateBoxes();

std::ostream& operator<<(std::ostream& os, Spatial::Component::Destination const& dest) {
    os << "(" << dest.destinationId << " & " <<  dest.ghost << ")";
    return os;
}

template <typename T> std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec) {
    for(T const& item : vec) os << item << " ";
    return os;
}

template <typename T> std::ostream& operator<<(std::ostream& os, std::list<T> const& vec) {
    for(T const& item : vec) os << item << " ";
    return os;
}

#include <boost/timer.hpp>

int main() {
    using Box = CommonCase::Box<int>;
    using Point = CommonCase::Point<int>;
    cout << "** Begin **" << endl;

    boost::timer t;

    std::vector<Box> boxes = generateBoxes();
    cout << "generateBoxes: " << t.elapsed() << endl;
    t.restart();

    Spatial::Container spatialContainer(Spatial::Container::Config(boxes).get() .setPeriodicByX() .setPeriodicByY().setPeriodicByZ());

    cout << "spatialContainer: " << t.elapsed() << endl;
    t.restart();

    using Spatial::Component;
    for(Component& item : spatialContainer) {
        item.getOutputExchange(2);
    }
    std::cout << "getOutputExchange: " << t.elapsed() << " s.\n";
    t.restart();
}



//---------

std::vector<Spatial::Container::Box> generateBoxes() {
    typedef Spatial::Container::Point Point;
    typedef Spatial::Container::Box Box;
    const int step = 10;
    const int iCount = 10, jCount = 10, kCount = 10;

    std::vector<Spatial::Container::Box> result;
    for(int k=0; k<kCount; ++k) {
        for(int j=0; j<jCount; ++j) {
            for(int i=0; i<iCount; ++i) {
                Point lo(i*step, j*step, k*step);
                Point hi(i*step+step, j*step+step, k*step+step);
                result.push_back(Box(lo, hi));
            }
        }
    }

//    result.push_back( { Point(iCount*step, 0, 0), Point(iCount*step+step, jCount*step, kCount*step) } );

    return result;
}