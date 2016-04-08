#include "impl.h"


#define BOOST_PP_VARIADICS
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>

#define _SIZE BOOST_PP_TUPLE_SIZE
#define _GET(i, types) BOOST_PP_TUPLE_ELEM( _SIZE(types), i, types )
#define _BASE(data)     _GET(0, data)
#define _TYPES(data)    _GET(1, data)

#define _HANDLE(_, i, bundle) template class _BASE(bundle)<_GET(i, _TYPES(bundle))>;
#define INSTANTIATE(base, types) BOOST_PP_REPEAT( _SIZE(types), _HANDLE, (base, types) )

namespace CommonCase {

INSTANTIATE(Point, (int, long, float, double));

} // namespace CommonCase