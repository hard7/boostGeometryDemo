#ifndef __ALGO_BOOST_H__
#define __ALGO_BOOST_H__

#include "point.h"
#include "box.h"

namespace BoostWrapper {

    template<class Box>
    bool covered_by(Box const& box1, Box const& box2);

} // namespace BoostWrapper

#endif //__ALGO_BOOST_H__
