#ifndef BOOSTGEOMETRYDEMO_BOX_H
#define BOOSTGEOMETRYDEMO_BOX_H

#include "point.h"

namespace CommonCase {

    template <typename T>
    class Box {
    public:
        Box(Point<T> const& lo, Point<T> const& hi);

        Point<T> const& lo() const;
        Point<T> const& hi() const;

        void lo(Point<T> const&);
        void hi(Point<T> const&);

    private:
        Point<T> _lo, _hi;
    };

} // namespace CommonCase

#endif //BOOSTGEOMETRYDEMO_BOX_H
