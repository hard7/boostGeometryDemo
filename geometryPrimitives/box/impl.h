#ifndef BOOSTGEOMETRYDEMO_BOX_IMPL_H
#define BOOSTGEOMETRYDEMO_BOX_IMPL_H

#include "../box.h"
//#include "../point/impl.h"

namespace CommonCase {

template <typename T> Box<T>::Box(Point<T> const& lo, Point <T> const& hi) : _lo(lo), _hi(hi) {}

template <typename T> Point<T> & Box<T>::lo() { return _lo; }
template <typename T> Point<T> & Box<T>::hi() { return _hi; }

template <typename T> Point<T> const& Box<T>::lo() const { return _lo; }
template <typename T> Point<T> const& Box<T>::hi() const { return _hi; }

template <typename T> void Box<T>::lo(Point < T > const& lo) {_lo = lo; }
template <typename T> void Box<T>::hi(Point < T > const& hi) {_hi = hi; }

template <typename T> T Box<T>::volume() const {
    return (hi().x() - lo().x()) * (hi().y() - lo().y()) * (hi().z() - lo().z());
}

} // namespace CommonCase

#endif //BOOSTGEOMETRYDEMO_BOX_IMPL_H
