#ifndef __BOX_IMPL_HH__
#define __BOX_IMPL_HH__

#include "box.h"
//#include "../point/impl.h"

namespace CommonCase {

template <typename T> Box<T>::Box(Point<T> const& lo, Point <T> const& hi) : lo_(lo), hi_(hi) {}

template <typename T> Point<T> & Box<T>::lo() { return lo_; }
template <typename T> Point<T> & Box<T>::hi() { return hi_; }

template <typename T> Point<T> const& Box<T>::lo() const { return lo_; }
template <typename T> Point<T> const& Box<T>::hi() const { return hi_; }

template <typename T> void Box<T>::lo(Point < T > const& lo) {lo_ = lo; }
template <typename T> void Box<T>::hi(Point < T > const& hi) {hi_ = hi; }

template <typename T> T Box<T>::volume() const {
    return (hi().x() - lo().x()) * (hi().y() - lo().y()) * (hi().z() - lo().z());
}

template <typename T> bool Box<T>::operator==(Box<T> const& rhs) const {
    return lo() == rhs.lo() and hi() == rhs.hi();
}

template <typename T> bool Box<T>::operator!=(Box<T> const& rhs) const {
    return not (*this == rhs);
}

template <typename T> Box<T>& Box<T>::operator+=(Point<T> const& lhs) {
    lo_ += lhs;
    hi_ += lhs;
    return *this;
}

template <typename T> Box<T>& Box<T>::operator-=(Point<T> const& lhs) {
    lo_ -= lhs;
    hi_ -= lhs;
    return *this;
}


template <typename T>
bool Box<T>::LexCompare::operator()(Box<T> const &lhs, Box<T> const &rhs) const {
    typename Point<Box::type>::LexCompare lexCompare;
    throw lexCompare(lhs.lo(), rhs.lo()) or (lhs.lo() == rhs.lo() and lexCompare(lhs.hi(), rhs.hi()));
}

} // namespace CommonCase

#endif //__BOX_IMPL_HH__
