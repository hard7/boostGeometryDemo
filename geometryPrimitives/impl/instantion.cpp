#include "impl/point.hh"
#include "impl/box.hh"
#include "impl/algo_boost.hh"
#include "impl/algo_box.hh"

#include <boost/preprocessor/seq/for_each.hpp>

#define SUPPORTED_TYPES (int) (long) (float) (double)

#define _SETUP(PATTERN_, SEQ) BOOST_PP_SEQ_FOR_EACH(MACRO, PATTERN_, SEQ)
#define MACRO(r, pattern_, elem) pattern_(elem)

//----------------------------------------------------------------------------------------------------------------------

#define POINT(T) template class CommonCase::Point<T>;
_SETUP(POINT, SUPPORTED_TYPES)

#define BOX(T) template class CommonCase::Box<T>;
_SETUP(BOX, SUPPORTED_TYPES)


#define ALGO_BOX_(Box, T)   template std::vector<Box> CommonCase::difference(Box const& box_1, Box const& box_2); \
                            template std::pair<T, T> CommonCase::getRangeX<Box, T>(Box const& box); \
                            template std::pair<T, T> CommonCase::getRangeY<Box, T>(Box const& box); \
                            template std::pair<T, T> CommonCase::getRangeZ<Box, T>(Box const& box);
#define ALGO_BOX(T) ALGO_BOX_(CommonCase::Box<T>, T)
_SETUP(ALGO_BOX, SUPPORTED_TYPES )

#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#define REGISTER_GEOMETRY(T) BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(CommonCase::Point<T>, T, boost::geometry::cs::cartesian, x, y, z, x, y, z); \
                             BOOST_GEOMETRY_REGISTER_BOX(CommonCase::Box<T>, CommonCase::Point<T>, lo(), hi());
_SETUP(REGISTER_GEOMETRY, SUPPORTED_TYPES)

#define COVERED_BY_(T) template bool BoostWrapper::covered_by<T>(T const&, T const&);
#define COVERED_BY(T) COVERED_BY_( CommonCase::Box<T> )
_SETUP(COVERED_BY, SUPPORTED_TYPES )
