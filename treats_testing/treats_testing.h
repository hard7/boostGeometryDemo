#ifndef BOOSTGEOMETRYDEMO_TREATS_TESTING_H
#define BOOSTGEOMETRYDEMO_TREATS_TESTING_H


namespace _treats {
    template<typename Point>
    struct CoordinateType {
        /* typedef CoordinateType type; */
    };


    template <typename Point>
    struct PointAccessor {
        static coordinate_type<Point>::type const& getX(Point const& point) { return 0; }
        static coordinate_type<Point>::type const& getY(Point const& point) { return 0; }
        static coordinate_type<Point>::type const& getZ(Point const& point) { return 0; }
    };
}


#endif //BOOSTGEOMETRYDEMO_TREATS_TESTING_H
