#ifndef __ALGO_BOOST_IMPL_H__
#define __ALGO_BOOST_IMPL_H__

#include "algo_boost.h"

//#include <boost/geometry.hpp>
#include <boost/mpl/identity.hpp>                       //need for covered_by
#include <boost/geometry/algorithms/covered_by.hpp>


template<class Box>
bool BoostWrapper::covered_by(Box const& box1, Box const& box2) {
    return boost::geometry::covered_by(box1, box2);
}

#endif //__ALGO_BOOST_IMPL_H__
