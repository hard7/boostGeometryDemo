#include <iostream>
#include "point.h"
#include "box.h"
#include <vector>
#include "Spatial/Container.h"
#include "stream/point.h"
#include "stream/box.h"

using std::cout;
using std::endl;

int main() {
    using Box = CommonCase::Box<int>;
    using Point = CommonCase::Point<int>;

    Point z(0, 0, 0);

    std::vector<Box> boxes = {Box(Point(0, 0 ,0), Point(10,20,30)),
                              Box(Point(0,0,30), Point(10,20,50)),
                              Box(Point(0,0,50), Point(10,20,80)) };

    Spatial::Container sc(boxes);
//    cout << sc.getBox(0) << endl;
    auto res = sc.getNeighbors(1);
    for(auto& val: res) {
        cout << val << endl;
    }
}

