#ifndef BOOSTGEOMETRYDEMO_POINT_H
#define BOOSTGEOMETRYDEMO_POINT_H


namespace CommonCase {

template <typename T>
class Point {
public:
    typedef T type;

    Point();
    explicit Point(T const&);
    Point(T const& x, T const& y, T const& z);

    T const& x() const;
    T const& y() const;
    T const& z() const;

    T& x();
    T& y();
    T& z();

    void x(T const&);
    void y(T const&);
    void z(T const&);

    struct LexCompare { bool operator()(Point<T> const& lhs, Point<T> const& rhs) const; };

    bool operator==(Point<T> const& rhs) const;
    bool operator!=(Point<T> const& rhs) const;

    Point<T>& operator+=(Point<T> const& lhs);
    Point<T>& operator-=(Point<T> const& lhs);
    Point<T>& operator*=(Point<T> const& lhs);
    Point<T>& operator*=(T const& lhs);
    Point<T>& operator/=(T const& lhs);

    Point<T> operator-() const;

private:
    T x_, y_, z_;
};

template <typename T> Point<T> operator+(Point<T> const& lhs, Point<T> const& rhs) { Point<T> _t(lhs); _t += rhs; return _t; }
template <typename T> Point<T> operator-(Point<T> const& lhs, Point<T> const& rhs) { Point<T> _t(lhs); _t -= rhs; return _t; }

template <typename T> Point<T> operator*(Point<T> const& lhs, Point<T> const& rhs) { Point<T> _t(lhs); _t *= rhs; return _t; }
template <typename T> Point<T> operator*(Point<T> const& lhs, T const& rhs) { Point<T> _t(lhs); _t *= rhs; return _t; }
template <typename T> Point<T> operator*(T const& lhs, Point<T> const& rhs) { Point<T> _t(rhs); _t *= lhs; return _t; }

template <typename T> Point<T> operator/(Point<T> const& lhs, T const& rhs) { Point<T> _t(lhs); _t /= rhs; return _t; }
//template <typename T> Point<T> operator/(T const& lhs, Point<T> const& rhs) { ?? }   // unsupported


} // namespace CommonCase


#endif //BOOSTGEOMETRYDEMO_POINT_H
