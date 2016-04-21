#ifndef __ALGO_BOX_H__
#define __ALGO_BOX_H__

#include <vector>

namespace CommonCase {

    template <class Box> // implicit
    std::vector<Box> difference(Box const& box_1, Box const& box_2);

    template <class Box> // implicit
    std::vector<Box> split(Box const& box_1, Box const& box_2);


    template <class Box, class T=typename Box::type>
    Box sticking(Box const& box, Point<T> const& direct);

    template <class Box, typename T = typename Box::type>
    std::pair<T, T> getRangeX(Box const& box);

    template <class Box, typename T = typename Box::type>
    std::pair<T, T> getRangeY(Box const& box);

    template <class Box, typename T = typename Box::type>
    std::pair<T, T> getRangeZ(Box const& box);

} // namespace CommonCase


#endif //__ALGO_BOX_H__
