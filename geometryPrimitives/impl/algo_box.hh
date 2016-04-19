#ifndef __ALGO_BOX_IMPL__
#define __ALGO_BOX_IMPL__


#include "algo_box.h"
#include "algo_boost.h"
#include <algorithm>

namespace CommonCase_ {

    template <typename T>
    static T packOnRange(std::pair<T, T> const& range, T const& value) {
        T const& min_ = range.first;
        T const& max_ = range.second;
        return std::min(max_, std::max(min_, value));
    }

    template <typename T>
    std::vector<T> uniqueOrderedValuesInRange(std::pair<T, T> const& range, std::vector<T> const& values) {
        std::vector<T> result;
        result.reserve(values.size());
        std::transform(std::begin(values), std::end(values), std::back_inserter(result), [&range](T const& v) { return packOnRange(range, v); });
        std::sort(std::begin(result), std::end(result));
        typename std::vector<T> ::iterator end_ = std::unique(std::begin(result), std::end(result));
        result.resize(std::distance(std::begin(result), end_));
        return result;
    }

} // namespace CommonCase_


template <class Box>
std::vector<Box> CommonCase::difference(Box const& b1, Box const& b2) {
    std::vector<Box> splitted = split(b1, b2);
    typename std::vector<Box>::iterator found = std::find_if(
            std::begin(splitted), std::end(splitted), [&b2](Box const& box) {return BoostWrapper::covered_by(box, b2); });
    if(found != std::end(splitted)) splitted.erase(found);
    return splitted;
}

template <class Box> // implicit
std::vector<Box> CommonCase::split(Box const& b1, Box const& b2) {
    using namespace CommonCase_;
    typedef typename Box::type T;
    typedef std::vector<T> Resection;
    using std::begin;
    using std::end;

    Resection resX = uniqueOrderedValuesInRange(getRangeX(b1), {b1.lo().x(), b1.hi().x(), b2.lo().x(), b2.hi().x()});
    Resection resY = uniqueOrderedValuesInRange(getRangeY(b1), {b1.lo().y(), b1.hi().y(), b2.lo().y(), b2.hi().y()});
    Resection resZ = uniqueOrderedValuesInRange(getRangeZ(b1), {b1.lo().z(), b1.hi().z(), b2.lo().z(), b2.hi().z()});

    std::vector<Box> result;
    result.reserve( (resX.size()-1) * (resY.size()-1) * (resZ.size()-1) );
    typename Resection::iterator lx, ly, lz, rx, ry, rz;
    for(lz=begin(resZ), rz=++begin(resZ); rz!=end(resZ); ++lz, ++rz) {
        for(ly=begin(resY), ry=++begin(resY); ry!=end(resY); ++ly, ++ry) {
            for(lx=begin(resX), rx=++begin(resX); rx!=end(resX); ++lx, ++rx) {
                Box box({*lx, *ly, *lz}, {*rx, *ry, *rz});
                result.push_back(box);
            }
        }
    }

    return result;
}


template <class Box, typename T = typename Box::type>
std::pair<T, T> CommonCase::getRangeX(Box const& box) {
    return std::make_pair(box.lo().x(), box.hi().x());
};

template <class Box, typename T = typename Box::type>
std::pair<T, T> CommonCase::getRangeY(Box const& box) {
    return std::make_pair(box.lo().y(), box.hi().y());
};

template <class Box, typename T = typename Box::type>
std::pair<T, T> CommonCase::getRangeZ(Box const& box) {
    return std::make_pair(box.lo().z(), box.hi().z());
};

#endif //__ALGO_BOX_IMPL__
