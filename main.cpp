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

    std::vector<Box> boxes = generateBoxes();
//            { Box(Point(0, 0 ,0), Point(10,20,30)),
//              Box(Point(0,0,30), Point(10,20,50)),
//              Box(Point(0,0,50), Point(10,20,80)) };


    Spatial::Container sc(boxes);

    auto res = sc.getNeighbors(0);
    for(auto& val: sc.getOutputExchange(0)) {
        cout << val.donor << " -> " << val.destinations << endl;
    }
}



//---------

std::vector<Spatial::Container::Box> generateBoxes() {
    const int step = 10;
    const int iCount = 3, jCount = 2, kCount = 2;

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