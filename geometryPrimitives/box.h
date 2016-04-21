#ifndef BOOSTGEOMETRYDEMO_BOX_H
#define BOOSTGEOMETRYDEMO_BOX_H

#include "point.h"

namespace CommonCase {

template <typename T>
class Box {
public:
    typedef T type;
    Box() = default;
    Box(Point<T> const& lo, Point<T> const& hi);

    Point<T> & lo();
    Point<T> & hi();

    Point<T> const& lo() const;
    Point<T> const& hi() const;

    T volume() const;

    void lo(Point<T> const&);
    void hi(Point<T> const&);

    bool operator==(Box<T> const& rhs) const;
    bool operator!=(Box<T> const& rhs) const;

    Box<T>& operator+=(Point<T> const& lhs);
    Box<T>& operator-=(Point<T> const& lhs);

    struct LexCompare {
        bool operator()(Box<T> const& lhs, Box<T> const& rhs) const;
    };

private:
    Point<T> lo_, hi_;
};

template <typename T> Box<T> operator+(Box<T> const& box, Point<T> const& point) { Box<T> _t(box); _t += point; return _t; }
template <typename T> Box<T> operator+(Point<T> const& point, Box<T> const& box) { Box<T> _t(box); _t += point; return _t; }

template <typename T> Box<T> operator-(Box<T> const& box, Point<T> const& point) { Box<T> _t(box); _t -= point; return _t; }
//template <typename T> Box<T> operator-(Point<T> const& point, Box<T> const& box) { Box<T> _t(box);  { ??= }    unsupported


} // namespace CommonCase

#endif //BOOSTGEOMETRYDEMO_BOX_H
