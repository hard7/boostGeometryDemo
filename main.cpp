#include <iostream>
#include "point.h"
#include "box.h"
#include <vector>
#include "Spatial/Container.h"
#include "stream/point.h"
#include "stream/box.h"
#include <map>
#include <tuple>

using std::cout;
using std::endl;


//template < template <typename T, typename T> class std::pair<T, T> >


template <class range_iterator>
struct Range_ {
    typedef typename range_iterator::first_type iterator;
    Range_(range_iterator range_) : range(range_) {}
    iterator begin() {return range.first; }
    iterator end() {return range.second; }
    range_iterator const range;
};

template <class range_iterator>
Range_<range_iterator> range(range_iterator range) { return Range_<range_iterator>(range); } // need for deduce template argument




void testMultimap () {
    typedef std::multimap<int , int > multimapII;
    multimapII mmap;
    mmap.insert({0, 10});
    mmap.insert({0, 12});
    mmap.insert({0, 14});
    mmap.insert({1, 40});

    multimapII::iterator begin_, end_;

    for(auto& res : range(mmap.equal_range(0)) ) {
        cout << res.first << " " << res.second << endl;
    }

}

std::vector<Spatial::Container::Box> generateBoxes();

int main() {
    using Box = CommonCase::Box<int>;
    using Point = CommonCase::Point<int>;

    Point z(0, 0, 0);



    std::vector<Box> boxes = generateBoxes();
//            { Box(Point(0, 0 ,0), Point(10,20,30)),
//              Box(Point(0,0,30), Point(10,20,50)),
//              Box(Point(0,0,50), Point(10,20,80)) };


    Spatial::Container sc(boxes);
//    cout << sc.getBox(0) << endl;
    auto res = sc.getNeighbors(0);
    for(auto& val: sc.getOutputExchange(0)) {
        cout << val.donor << " " << val.destinations [0] << endl;
    }

    testMultimap();
}



//---------

std::vector<Spatial::Container::Box> generateBoxes() {
    const int step = 10;
    const int iCount = 3, jCount = 2, kCount = 1;

    std::vector<Spatial::Container::Box> result;
    for(int k=0; k<kCount; ++k) {
        for(int j=0; j<jCount; ++j) {
            for(int i=0; i<iCount; ++i) {
                Spatial::Container::Point lo(i*step, j*step, k*step);
                Spatial::Container::Point hi(i*step+step, j*step+step, k*step+step);
                result.push_back(Spatial::Container::Box(lo, hi));
            }
        }
    }
    return result;
}