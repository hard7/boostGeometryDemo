#ifndef __UTIL_MULTIMAP_RANGE_H__
#define __UTIL_MULTIMAP_RANGE_H__

#include <map>

template <class range_iterator>
struct MultimapRange {
    typedef typename range_iterator::first_type iterator;
    MultimapRange(range_iterator const& range_) : range(range_) {}
    iterator begin() {return range.first; }
    iterator end() {return range.second; }
    range_iterator const range;
};

// need for deduce template argument
template <class range_iterator>
MultimapRange<range_iterator> makeMultimapRange(range_iterator const& range) {
    return MultimapRange<range_iterator>(range);
}


#endif //__UTIL_MULTIMAP_RANGE_H__
