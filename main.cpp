#include <iostream>
#include "point.h"
#include "box.h"
#include <vector>
#include "Spatial/Container.h"
#include "stream/point.h"
#include "stream/box.h"
#include <map>

using std::cout;
using std::endl;


//template < template <typename T, typename T> class std::pair<T, T> >






#include <set>

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