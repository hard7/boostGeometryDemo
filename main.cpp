#include <iostream>
#include "point.h"
#include "box.h"
#include <vector>
#include "Spatial/Container.h"
#include "stream/point.h"
#include "stream/box.h"
#include <map>

//#include "impl/algo_box.hh"

using std::cout;
using std::endl;


//template < template <typename T, typename T> class std::pair<T, T> >






#include <set>
#include <list>
#include <algo_box.h>

std::vector<Spatial::Container::Box> generateBoxes();

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

#include <boost/iterator/counting_iterator.hpp>
#include <algorithm>
#include <functional>


int main() {
    using Box = CommonCase::Box<int>;
    using Point = CommonCase::Point<int>;


    struct A {
        int power = 10;
        std::vector<int> b;
        A() {
            using namespace std::placeholders;
            std::transform(boost::counting_iterator<int>(0), boost::counting_iterator<int>(10),
                           std::back_inserter(b), std::bind(&A::func, *this, _1));
        }

        A(A const& other) {
            power = other.power;
            b = other.b;
            cout << "COPY" << endl;
        }

        int func(int a) { return a * power; }
    };

    A a;
    a.b.insert(--std::end(a.b), 100);
        cout << a.b << endl;

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

    std::vector<Box> boxes = generateBoxes();
//            { Box(Point(0, 0 ,0), Point(10,20,30)),
//              Box(Point(0,0,30), Point(10,20,50)),
//              Box(Point(0,0,50), Point(10,20,80)) };


    Spatial::Container sc(boxes);

    auto res = sc.getNeighbors(0);
//    for(auto& val: sc.findOutputExchange(0)) {
//        cout << val.donor << " -> " << val.destinations << endl;
//    }

    for(auto& val: sc.getOutputExchange(2)) {
        cout << val.donor << " -> " << val.destinations << endl;
//        cout << val.ghost << " -> " << val.source << endl;
    }
}



//---------

std::vector<Spatial::Container::Box> generateBoxes() {
    typedef Spatial::Container::Point Point;
    typedef Spatial::Container::Box Box;
    const int step = 10;
    const int iCount = 1, jCount = 2, kCount = 1;

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

    result.push_back( { Point(iCount*step, 0, 0), Point(iCount*step+step, jCount*step, jCount*step) } );

    return result;
}