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


//template < template <typename T, typename T> class std::pair<T, T> >




std::vector<Spatial::Container::Box> generateBoxes();


std::ostream& operator<<(std::ostream& os, Spatial::Component::Destination const& dest) {
    os << "(" << dest.destinationId << " & " <<  dest.ghost << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec) {
    for(T const& item : vec) os << item << " ";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::list<T> const& vec) {
    for(T const& item : vec) os << item << " ";
    return os;
}

#include <boost/numeric/conversion/cast.hpp>
#include <chrono>
#include <boost/timer.hpp>

int main() {
    using Box = CommonCase::Box<int>;
    using Point = CommonCase::Point<int>;

    {
        typedef std::list<int> List;
        List list = {6, 5, 4, 2, 6, 8};

//        cout << *list.erase(++std::begin(list)) << endl;
//        for(List::iterator iBase=std::begin(list); iBase!=std::end(list); ++iBase) {
//            static int asdgacwadaw = 4;
//            if(--asdgacwadaw >= 0) List::iterator it = list.insert(++List::iterator(iBase), 1);
//            *it *= 10;
//        }

//        List::iterator it = begin(list);
//        cout << "list: " << list << endl;
//        it--;
//        cout << ": " << (it == std::end(list)) << endl;
    }

    cout << "** Begin **" << endl;
    Box b1(Point(0, 0, 0), Point(30,30,30));
    Box b2(Point(10, 10, 10), Point(20,20,20));

//    cout << CommonCase::split(b1, b2) . size() << endl;

    boost::timer t;

    std::vector<Box> boxes = generateBoxes();
//            { Box(Point(0, 0 ,0), Point(10,20,30)),
//              Box(Point(0,0,30), Point(10,20,50)),
//              Box(Point(0,0,50), Point(10,20,80)) };

    cout << "generate boxes: " << t.elapsed() << endl;

    t.restart();
//    Spatial::Container::Config cnf(boxes); cnf.setPeriodicByX();
    Spatial::Container spatialContainer(Spatial::Container::Config(boxes).get() .setPeriodicByX() .setPeriodicByY().setPeriodicByZ());
//    Spatial::Container spatialContainer(cnf);
    cout << "create spatialContainer: " << t.elapsed() << endl;


//    auto res = spatialContainer.getNeighbors(0);
//    for(auto& val: sc.findOutputExchange(0)) {
//        cout << val.donor << " -> " << val.destinations << endl;
//    }

//    for(auto& val: spatialContainer.getOutputExchange(2)) {
//        cout << val.donor << " -> " << val.destinations << endl;
//    }

    cout << "Start getOutputExchange." << endl;
    t.restart();

    using Spatial::Component;
    for(Component& item : spatialContainer) {
        item.getOutputExchange();
    }

    std::cout << "Printing took " << t.elapsed() << " s.\n";

//    cout << "Start Estimate" << endl;
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