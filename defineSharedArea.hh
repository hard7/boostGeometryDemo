#ifndef BOOSTGEOMETRYDEMO_DEFINESHAREDAREA_HH_H
#define BOOSTGEOMETRYDEMO_DEFINESHAREDAREA_HH_H

#include "defineSharedArea.h"

template <typename _InputIterator, typename T>
std::vector< CommonCase::Box<T> > defineSharedArea(_InputIterator begin, _InputIterator end) {
    __glibcxx_function_requires(_InputIteratorConcept < _InputIterator >);

}

#endif //BOOSTGEOMETRYDEMO_DEFINESHAREDAREA_HH_H
