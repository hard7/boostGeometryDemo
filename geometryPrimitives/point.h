#ifndef BOOSTGEOMETRYDEMO_POINT_H
#define BOOSTGEOMETRYDEMO_POINT_H


namespace CommonCase {

template <typename T>
class Point {
public:
    typedef T type;

    Point();
    Point(T const& x, T const& y, T const& z);

    T const& x() const;
    T const& y() const;
    T const& z() const;

    void x(T const&);
    void y(T const&);
    void z(T const&);

    struct LexCompare {
        bool operator()(Point<T> const& lhs, Point<T> const& rhs) const;
    };

    bool operator==(Point<T> const& rhs) const;

private:
    T x_, y_, z_;
};



//template <typename T>
//bool lexicographical_less(Point<T> const& lhs, Point<T> const& rhs);

} // namespace CommonCase


#endif //BOOSTGEOMETRYDEMO_POINT_H
