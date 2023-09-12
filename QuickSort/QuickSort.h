#ifndef AiAS_QuickSort
#define AiAS_QuickSort
#include "Utils.h"

template<class Iter, class Comp = Less<>>
Iter Partition(Iter first, Iter last, Comp comp = Comp{}) {
	--last;
	auto x = *last;
	Iter q = first;
	for (Iter j = first; j != last; ++j) {
		if (comp(*j, x)) {
			Swap(*q, *j);
			++q;
		}
	}
	Swap(*q, *last);
	return q;
}

template<class Iter, class Comp = Less<>>
void QuickSort(Iter first, Iter last, Comp comp = Comp{}) {
	while (first != last) {
		Iter q = Partition(first, last, comp);
		QuickSort(first, q, comp);
		first = ++q;
	}
}

#endif // !AiAS_QuickSort
