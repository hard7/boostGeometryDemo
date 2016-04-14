#ifndef BOOSTGEOMETRYDEMO_POINT_H
#define BOOSTGEOMETRYDEMO_POINT_H


namespace CommonCase {

template <typename T>
class Point {
public:
    typedef T type;

    Point(T const& x, T const& y, T const& z);

    T const& x() const;
    T const& y() const;
    T const& z() const;

    void x(T const&);
    void y(T const&);
    void z(T const&);

private:
    T x_, y_, z_;
};

} // namespace CommonCase


#endif //BOOSTGEOMETRYDEMO_POINT_H
