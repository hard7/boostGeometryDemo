#ifndef BOOSTGEOMETRYDEMO_POINT_IMPL_H
#define BOOSTGEOMETRYDEMO_POINT_IMPL_H

#include "point.h"

namespace CommonCase {

template <typename T> Point<T>::Point() : x_(0), y_(0), z_(0) {}
template <typename T> Point<T>::Point(T const& x, T const& y, T const& z) : x_(x), y_(y), z_(z) {}

template <typename T> T const& Point<T>::x() const { return x_; }
template <typename T> T const& Point<T>::y() const { return y_; }
template <typename T> T const& Point<T>::z() const { return z_; }

template <typename T> void Point<T>::x(T const& x) { x_ = x; }
template <typename T> void Point<T>::y(T const& y) { y_ = y; }
template <typename T> void Point<T>::z(T const& z) { z_ = z; }

template <typename T>
bool Point<T>::operator==(Point<T> const& rhs) const {
    return x() == rhs.x() and y() == rhs.y() and z() == rhs.z();
}

template <typename T>
bool Point<T>::LexCompare::operator()(Point<T> const &lhs, Point<T> const &rhs) const {
     return lhs.x() < rhs.x() or (lhs.x() == rhs.x() and lhs.y() < rhs.y() or (lhs.y() == rhs.y() and lhs.z() < rhs.z()));
}

} // namespace CommonCase

#endif //BOOSTGEOMETRYDEMO_POINT_IMPL_H
