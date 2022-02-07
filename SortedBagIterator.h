#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	SortedBag& bag;
	SortedBagIterator( SortedBag& b);
	ListNode** list;
	int index;
	int maximum;
	//TODO - Representation

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

