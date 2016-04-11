#ifndef BOOSTGEOMETRYDEMO_DEFINESHAREDAREA_H
#define BOOSTGEOMETRYDEMO_DEFINESHAREDAREA_H


#include <vector>
#include "geometryPrimitives/box/fwd.h"

template <typename _InputIterator, typename T>
std::vector< CommonCase::Box<T> > defineSharedArea(_InputIterator begin, _InputIterator end);


#endif //BOOSTGEOMETRYDEMO_DEFINESHAREDAREA_H
