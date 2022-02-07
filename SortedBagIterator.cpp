#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator( SortedBag& b) : bag(b) {
	//TODO - Implementation
	list = b.getSortedArray();
	index = 0;
	maximum = b.size();
}

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (this->valid())
		return list[0]->value;
	else
		throw exception();
	//return NULL_TCOMP;
}

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (index >= maximum) {
		return false;
	}
	return true;
}

void SortedBagIterator::next() {
	//TODO - Implementation
	if (this->valid())
		index++;
	else
		throw exception();
}

void SortedBagIterator::first() {
	//TODO - Implementation
	index = 0;
}

