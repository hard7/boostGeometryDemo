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

#include <boost/numeric/conversion/cast.hpp>
#include <memory>
#include <boost/iterator/counting_iterator.hpp>

#include <list>
#include <tuple>
#include <set>
#include <unordered_set>

#include "stream/box.h"                                 //FIXME DELETE
#include "stream/point.h"                                 //FIXME DELETE
#include "algo_box.h"
#include "stream/box.h"

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

namespace {

    struct Donor {
        typedef std::set<Spatial::Component::BoxId> Links;
        Box box;
        Links links;
        Donor(Box const box_, Links const& links_) : box(box_), links(links_) {}
    };

    struct DonorMaker {
        Donor::Links& links;
        DonorMaker(Donor::Links& links_) : links(links_) {}
        Donor operator()(Box const& box) { return Donor(box, links); }
    };
} // namespace {anonymous}


namespace Spatial {

struct Container::Impl {
    typedef unsigned int BorderWidth;
    typedef std::pair<Box, int> Value;
    typedef bgi::rtree< Value, bgi::dynamic_quadratic> Rtree;
    typedef std::map<BoxId, BoxId> ProjectionIm;

    _implContainer container;
    const std::vector<Box> boxes;
    std::vector<Box> boxesIm;
    std::unique_ptr< Rtree > rtree;
    BorderWidth borderWidth;
    ProjectionIm projectionIm;

    std::size_t realBoxCount;

    mutable std::map<std::pair<BoxId, BorderWidth>, Component::OutputExchange::Collection> cachedOutput;
    mutable std::map<std::pair<BoxId, BorderWidth>, Component::InputExchange::Collection> cachedInput;
    std::map<BoxId, Component::BoxIdCollection> spatialNeighbor, trueNeighbor;

    Impl(Config const& config) : boxes(std::move(config.boxes)) {
        realBoxCount = boxes.size();
        borderWidth = config.borderWidth;
        std::tie(boxesIm, projectionIm) = findImaginaryBoxes(boxes, config.periodic);
        initNeighbors();
    }

    bool isRealBoxId(BoxId boxId) const { return boxId < realBoxCount; }
    bool isImaginaryBoxId(BoxId boxId) const { return not isRealBoxId(boxId); }

    Box const& getBox(BoxId boxId) const {
        if(isRealBoxId(boxId)) return boxes.at(boost::numeric_cast<std::size_t>(boxId));
        else boxesIm.at(boost::numeric_cast<std::size_t>(boxId - realBoxCount));
    }

private:


    void initNeighbors() {
        int count = 0;
        Rtree rtree_( bgi::dynamic_quadratic( boxes.size() ));
        for (Box const& box : boxes) rtree_.insert(std::make_pair(box, count++));
        for (Box const& box : boxesIm) rtree_.insert(std::make_pair(box, count++));

        count = 0;
        for (Box const& box : boxes) spatialNeighbor.insert(findSpatialNeighborPair(rtree_, count++));
        for (Box const& box : boxesIm) spatialNeighbor.insert(findSpatialNeighborPair(rtree_, count++));

        BoxId boxId;
        Component::BoxIdCollection links;
        for(auto const& neighbor : spatialNeighbor) {
            std::tie(boxId, links) = neighbor;
            if(isImaginaryBoxId(boxId)) continue;
            std::unordered_set<BoxId> unique_;
            std::transform(std::begin(links), std::end(links), std::inserter(unique_, std::end(unique_)), [this](BoxId id) {
                return isRealBoxId(id) ? id : projectionIm.at(id);
            });
            trueNeighbor.insert(std::make_pair(boxId, Component::BoxIdCollection(std::begin(unique_), std::end(unique_))));
        }
    }

public:
    static
    std::pair< Boxes, ProjectionIm > findImaginaryBoxes(Boxes const& boxesRe, Config::Periodic per) {
        Rtree rtree_( bgi::dynamic_quadratic( boxesRe.size() ));
        for(std::size_t i=0; i<boxesRe.size(); ++i) rtree_.insert(std::make_pair(boxesRe.at(i), i));

        auto range_ = [](bool periodic) -> std::vector<int> {
            if(periodic) return { -1, 0, 1 }; else return {0};
        };
        Box bounds;
        boost::geometry::convert(rtree_.bounds(), bounds);
        Point boundsNorm = bounds.hi() - bounds.lo();

        Boxes boxesIm;
        ProjectionIm projectionIm;
        std::size_t index = boxesRe.size();
        for(int k : range_(per.byZ)) {
            for(int j : range_(per.byY)) {
                for(int i : range_(per.byX)) {
                    if(i or j or k) {
                        Point offset = boundsNorm * Point(i, j, k);//fix
                        Box stick = sticking(bounds, offset);
                        for(Value const& value : rtree_ | bgi::adaptors::queried(bgi::intersects(stick))) {
                            boxesIm.push_back(value.first - offset);
                            projectionIm.insert(std::make_pair(index++, value.second));
                        }
                    }
                }
            }
        }
        return std::make_pair(boxesIm, projectionIm);
    }


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

//    Box const& getBox(BoxId boxId) const {
//        return boxes.at(boxId);
//    }

    Component::BoxIdCollection const& getNeighbors(BoxId boxId) const {
        return trueNeighbor.at(boxId);
    }

    Component::BoxIdCollection const& getSpatialNeighbors(BoxId boxId) const {
        return spatialNeighbor.at(boxId);
    }


    Component::InputExchange::Collection const& getInputExchange(BoxId boxId, unsigned int width) const {
        auto key = std::make_pair(boxId, width);
        auto found = cachedInput.find(key);
        if(found != std::end(cachedInput)) return found->second;
        else {
            cachedInput.insert(std::make_pair(key, findInputExchange(boxId, width)));
            return cachedInput.at(key);
        }
    }


    Component::OutputExchange::Collection const& getOutputExchange(BoxId boxId, unsigned int width) const {
        auto key = std::make_pair(boxId, width);
        auto found = cachedOutput.find(key);
        if(found != std::end(cachedOutput)) return found->second;
        else {
            cachedOutput.insert(std::make_pair(key, findOutputExchange(boxId, width)));
            return cachedOutput.at(key);
        }
    }

private:

    static Component::BoxIdCollection findSpatialNeighbor(Rtree const &rtree, Box const &target) {
        Component::BoxIdCollection result;
        for(Value const& v : rtree | bgi::adaptors::queried(bgi::intersects(target) and not bgi::covered_by(target))) {
            result.push_back(v.second);
        }
        return result;
    }

//    Component::BoxIdCollection findTrueNeighbor(BoxId boxId) {
//        Component::BoxIdCollection result;
//        Box target = getBox(boxId);
//        for(Value const& v : rtree | bgi::adaptors::queried(bgi::intersects(target) and not bgi::covered_by(target))) {
//            result.push_back(v.second);
//        }
//        return result;
//    }

    std::pair<BoxId, Component::BoxIdCollection> findSpatialNeighborPair(Rtree const& rtree, BoxId boxId) const {
        return std::make_pair(boxId, findSpatialNeighbor(rtree, getBox(boxId)));
    }

    Component::InputExchange::Collection findInputExchange(BoxId boxId, unsigned int width) const {
        Component::InputExchange::Collection result;
        for(BoxId neighborBoxId : getNeighbors(boxId)) {
            for(Component::OutputExchange const& output : getOutputExchange(neighborBoxId, width)) {
//                Component::BoxIdCollection::const_iterator found = std::find(std::begin(output.destinations), std::end(output.destinations), boxId);
                Component::DestinationCollection const& dst = output.destinations;
                Component::DestinationCollection::const_iterator found;
                found = std::find_if(std::begin(dst), std::end(dst), [boxId](Component::Destination const& d) { return boxId == d.destinationId; });

                if(found != std::end(output.destinations)) result.push_back((Component::InputExchange) {found->ghost, output.donor, neighborBoxId});
            }
        }
        return result;
    }

    Component::OutputExchange::Collection findOutputExchange(BoxId boxId, unsigned int width) const {
        using std::begin;
        using std::end;

        Box current = getBox(boxId);
        Component::OutputExchange::Collection result;

        std::list<Donor> donors;
        for(BoxId neighborBoxId : getSpatialNeighbors(boxId)) {
            Box neighbor = getBox(neighborBoxId);
            Box expandedNeighbor = Impl::expand(neighbor, width);
            Box donorBox = Impl::trueIntersection(current, expandedNeighbor);
            donors.push_back({donorBox, {neighborBoxId}});
        }


        typedef std::list<Donor>::iterator iter;
        for(iter i=begin(donors); i!=end(donors); ++i) {
            for(iter j= ++iter(i); j!=end(donors); /* ++j */) {
                Box& iBox = i->box, & jBox = j->box;
                if(iBox == jBox) {
                    i->links.insert(begin(j->links), end(j->links));
                    j = donors.erase(j);
                    continue;
                }

                Box common;
                bg::intersection(iBox, jBox, common);
                if(common.volume() > 0) {
                    std::vector<Box> iSp = CommonCase::split(iBox, common);
                    std::transform(begin(iSp), end(iSp), std::inserter(donors, ++iter(i)), DonorMaker(i->links));
                    i = donors.erase(i);

                    std::vector<Box> jSp = CommonCase::split(jBox, common);
                    std::transform(begin(jSp), end(jSp), std::inserter(donors, ++iter(j)), DonorMaker(j->links));
                    j = donors.erase(j);
                    continue;
                }

                ++j;
            }
        }

        assert(isRealBoxId(boxId));
        result.reserve(donors.size());
        std::transform(begin(donors), end(donors), std::back_inserter(result), [this](Donor const& donor) {
            Component::DestinationCollection dst;
            dst.reserve(donor.links.size());
            for(BoxId linkId : donor.links) {
                if(isRealBoxId(linkId)) dst.push_back({donor.box, linkId});
                else dst.push_back({projectImaginaryBox(donor.box, linkId), projectionIm.at(linkId)});
            }
            return (Component::OutputExchange) { donor.box, std::move(dst) };
        });

        return result;
    }

    private:
        Box projectImaginaryBox(Box const& target, BoxId imId) const {
            BoxId reId = projectionIm.at(imId);
            Box imBox = getBox(imId), reBox = getBox(reId);
            Point offset  = reBox.lo() - imBox.lo();
            return target + offset;
        }
};

//----------------------------------------------------------------------------------------------------------------------


Container::Container(Boxes const& boxes) : Container(Config(boxes)) {}
Container::Container(Boxes && boxes) : Container(Config(std::move(boxes))) {}       // may be move running implicitly

Container::Container(Config const& config) : impl(new Impl(config)) {
    std::size_t size = impl->boxes.size();
    impl->container.reserve(size);
    for(std::size_t i=0; i<size; ++i) {
        impl->container.push_back(Component(*this, boost::numeric_cast<int>(i)));
    }
}

Box const& Container::getBox(BoxId boxId) const {
    return impl->getBox(boxId);
}

Component::BoxIdCollection const& Container::getNeighbors(BoxId boxId) const { return impl->getNeighbors(boxId); }

Component::InputExchange::Collection const& Container::getInputExchange(BoxId boxId) const {
    return impl->getInputExchange(boxId, impl->borderWidth);
}

Component::InputExchange::Collection const& Container::getInputExchange(BoxId boxId, unsigned int width) const {
    impl->getInputExchange(boxId, width);
}

Component::OutputExchange::Collection const& Container::getOutputExchange(BoxId boxId) const {
    return impl->getOutputExchange(boxId, impl->borderWidth);
}

Component::OutputExchange::Collection const& Container::getOutputExchange(BoxId boxId, unsigned int width) const {
    return impl->getOutputExchange(boxId, width);
}


Container::iterator Container::begin() { return impl->container.begin(); }
Container::iterator Container::end() { return impl->container.end(); }

Container::const_iterator Container::begin() const { return impl->container.cbegin(); }
Container::const_iterator Container::end() const { return impl->container.cend(); }

Container::const_iterator Container::cbegin() const { return impl->container.cbegin(); }
Container::const_iterator Container::cend() const { return impl->container.cend(); }

} // namespace Spatial