#include "../Container.h"
#include "box.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/geometry/algorithms/intersection.hpp>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include "stream/box.h"                                 //FIXME DELETE
#include "MultimapRange.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef Spatial::Component::Point Point;
typedef Spatial::Component::Box Box;

BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(Point, Point::type, boost::geometry::cs::cartesian, x, y, z, x, y, z);
BOOST_GEOMETRY_REGISTER_BOX(Box, Point, lo(), hi());

namespace {
// Define a function object converting a value_type of indexed Range into std::pair<>.
// This is a generic implementation but of course it'd be possible to use some
// specific types. One could also take Value as template parameter and access
// first_type and second_type members, etc.
    template <typename First, typename Second>
    struct pair_maker {
        typedef std::pair<First, Second> result_type;
        template<typename T>
        inline result_type operator()(T const& v) const  {
            return result_type(v.value(), v.index());
        }
    };
}

namespace Spatial {

struct Container::Impl {
    typedef std::pair<Box, int> Value;

    _implContainer container;
    const std::vector<Box> boxes;
    bgi::rtree< Value, bgi::dynamic_quadratic> rtree;

    Impl(Boxes const& boxes_) : boxes(boxes_),
            rtree(boxes_ | boost::adaptors::indexed() | boost::adaptors::transformed(pair_maker<Box, int>())
                , bgi::dynamic_quadratic(boxes_.size())) { }


    static Box expand(Box const& box, int expandValue) {
        Point lo(box.lo().x() - expandValue, box.lo().y() - expandValue, box.lo().z() - expandValue);
        Point hi(box.hi().x() + expandValue, box.hi().y() + expandValue, box.hi().z() + expandValue);
        return Box(lo, hi);
    }

    static Box makeBox() {
        return Box(Point(0,0,0), Point(0,0,0));
    }

    static Box trueIntersection(Box const& box1, Box const& box2) throw (std::logic_error) {
        Box result = makeBox();
        bool isIntersected = boost::geometry::intersection(box1, box2, result);
        if(not isIntersected or result.volume() <= 0) {
            throw std::logic_error("Bad intersection");
        }
        return result;
    }
};


Container::Container(Boxes const& boxes) : impl(new Impl(boxes)) {
    int size = impl->boxes.size();
    impl->container.reserve(size);
    for(int i=0; i<size; ++i) {
        impl->container.push_back(Component(*this, i));
    }
}

Box const& Container::getBox(BoxId boxId) const {
    return impl->boxes.at(boxId);
}

std::vector<Container::BoxId> Container::getNeighbors(BoxId boxId) const {
    std::vector<BoxId> result;
    std::vector<Impl::Value> queryResult;
    Box const& target = getBox(boxId);
    impl->rtree.query(bgi::intersects(target) and not bgi::covered_by(target) , std::back_inserter(queryResult));
    for(Impl::Value const& v : queryResult) {
        result.push_back(v.second);
    }
    return result;
}

std::vector<Component::InputExchange> Container::getInputExchange(BoxId boxId) const {
    Box base = getBox(boxId);
    Box expanded = Impl::expand(base, 1);
    std::vector<Impl::Value> queryResult;
    std::vector<Component::InputExchange> result;
    impl->rtree.query(bgi::intersects(expanded) and not bgi::covered_by(expanded), std::back_inserter(queryResult));
    for(Impl::Value const& value : queryResult) {
        Box const& intersected = value.first;
        BoxId intersectedId = value.second;
        Box common(base);
        boost::geometry::intersection(expanded, intersected, common);
        result.push_back(Component::InputExchange {common, common, intersectedId});
    }
    return result;
}

template <typename T>
static std::set<T> collectInRange(T min_, T max_, T value_1, T value_2) {
    return { min_, max_, std::min(max_, std::max(min_, value_1)), std::min(max_, std::max(min_, value_2)) };
}

static std::vector<Container::Box> difference(Container::Box const& box_1, Container::Box const& box_2) {
    typedef typename Container::Box::type Base;
    typedef std::set<Base> Resection;
    std::vector<Container::Box> result;
    Resection resX = collectInRange<Base>(box_1.lo().x(), box_1.hi().x(), box_2.lo().x(), box_2.hi().x());
    Resection resY = collectInRange<Base>(box_1.lo().y(), box_1.hi().y(), box_2.lo().y(), box_2.hi().y());
    Resection resZ = collectInRange<Base>(box_1.lo().z(), box_1.hi().z(), box_2.lo().z(), box_2.hi().z());
    typedef Resection::iterator It;
    for(It xLeft=std::begin(resX), xRight= ++It(xLeft); xRight!=std::end(resX); ++xLeft, ++xRight) {
        for(It yLeft=std::begin(resY), yRight= ++It(yLeft); yRight!=std::end(resY); ++yLeft, ++yRight) {
            for(It zLeft=std::begin(resZ), zRight= ++It(zLeft); zRight!=std::end(resZ); ++zLeft, ++zRight) {
                Container::Point lo(*xLeft, *yLeft, *zLeft);
                Container::Point hi(*xRight, *yRight, *zRight);
                Container::Box box(lo, hi);
                if(not boost::geometry::covered_by(box, box_2)) result.push_back(box);
            }
        }
    }
    return result;
}

std::vector<Component::OutputExchange> Container::getOutputExchange(BoxId boxId) const {
    using std::cout;
    using std::endl;

    Box current = getBox(boxId);
    std::vector<Component::OutputExchange> result;

    struct Donor {
        Box box;
        std::vector<BoxId> links;
    };

    std::vector<Donor> donors;
    for(BoxId neighborBoxId : getNeighbors(boxId)) {
        Box neighbor = getBox(neighborBoxId);
        Box expandedNeighbor = Impl::expand(neighbor, 1);
        Box donorBox = Impl::trueIntersection(current, expandedNeighbor);
        donors.push_back({donorBox, {neighborBoxId}});
        std::cout << donorBox << " " << neighborBoxId << std::endl;
    }

    std::vector<Donor>::iterator itBase, itSub;
    for(itBase=std::begin(donors); itBase!=std::end(donors); ++itBase) {
        for(itSub=itBase+1; itSub!=std::end(donors); ++itSub) {
            std::vector<Box> diff = difference(itBase->box, itSub->box);
            for(auto& d : diff) {
                cout << d << " ";
            }
            cout << endl;
        }
    }

//    for(std::pair<Box, int> donorP : donors) {
//        typedef boost::geometry::model::polygon<Point> poligon;
//        std::vector<Box> res;
////        boost::geometry::difference(current, donorP.first, res);
//    }

    Box b1(Point(0,0,0), Point(10, 10, 10));
    Box b2(Point(0,0,0), Point(10, 10, 10));
    Box b3;
    bool ret = boost::geometry::covered_by(b1, b2);
    std::cout << "Result:  " << b3 << " " << ret << std::endl;

    return result;
}


Container::iterator Container::begin() { return impl->container.begin(); }
Container::iterator Container::end() { return impl->container.end(); }

Container::const_iterator Container::begin() const { return impl->container.cbegin(); }
Container::const_iterator Container::end() const { return impl->container.cend(); }

Container::const_iterator Container::cbegin() const { return impl->container.cbegin(); }
Container::const_iterator Container::cend() const { return impl->container.cend(); }

} // namespace Spatial