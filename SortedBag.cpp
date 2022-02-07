#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include <exception>

using namespace std;

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->r = r;
	this->m = 11;
	this->nrElems = 0;
	this->alpha = 0.7;
	this->ht = new ListNode*[m];

	for (int i = 0; i < m; i++)
		this->ht[i] = new ListNode;
}

int SortedBag::hash(TComp position) const {
    if (position < 0)
        position = position * -1;
    return position % this->m;
}

void SortedBag::add(TComp e) {
    this->nrElems++;
    int pos = this->hash(e);
    if (!this->ht[pos]->valid)
    {
        // If the position is not valid make it valid
        //std::cout << "b";
        this->ht[pos]->next = nullptr;
        this->ht[pos]->prev = nullptr;
        this->ht[pos]->value = e;
        this->ht[pos]->valid = true;
    }
    else
    {
        //std::cout << "c";
        auto* node = new ListNode;
        node->valid = true;
        node->value = e;
        node->next = this->ht[pos];
        node->prev = nullptr;
        this->ht[pos]->prev = node; // add the node behind the currrent position
        this->ht[pos] = node; // make the new current position that of the node
    }

    if (this->nrElems * 1.00 / this->m >= this->alpha) {
        // Ckeck if the table needs to be rehashed
        auto* newHT = new ListNode*[m * 2];
        m *= 2;

        for (int i = 0; i < m; i++)
            newHT[i] = new ListNode;

        for (int i = 0; i < m / 2; i++)
        {
            if (this->ht[i]->valid)
            {
                // copy the contents
                ListNode* current = this->ht[i];
                bool first = true;
                do {
                    if (!first)
                    {
                        current = current->next;
                    }
                    pos = this->hash(current->value);
                    if (!newHT[pos]->valid)
                    {
                        newHT[pos]->next = nullptr;
                        newHT[pos]->prev = nullptr;
                        newHT[pos]->value = current->value;
                        newHT[pos]->valid = true;
                    }
                    else {
                        auto* node = new ListNode;
                        node->valid =true;
                        node->value = current->value;
                        node->next = newHT[pos];
                        node->prev = nullptr;
                        newHT[pos]->prev = node;
                        newHT[pos] = node;
                    }
                    first = false;
                } while (current->next != nullptr);
            }
        }
        //free the memory
        delete this->ht;
        this->ht = newHT;
    }
}


bool SortedBag::remove(TComp e) {
	//TODO - Implementation
    int pos = this->hash(e);
    ListNode* current = this->ht[pos];
    if (current->valid) {
        bool first = true;
        do {
            if (!first)
            {
                current = current->next;
            }
            if (current->value == e) {
                if (current->prev == nullptr) {
                    // if its the first element in its list
                    if (current->next == nullptr)
                        current->valid =false;
                    else {
                        this->ht[pos] = current->next;
                        this->ht[pos]->prev = nullptr;
                    }
                }
                else {
                    //if not just jump over it
                    current->prev->next = current->next;
                    if (current->next != nullptr)
                        current->next->prev =current->prev;
                }
                this->nrElems--;
                return true;
            }
            first = false;
        } while (current->next != nullptr);
    }
    return false;
}


bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
    int pos = this->hash(elem);
    ListNode* current = this->ht[pos];
    if (current->valid) {
        bool first = true;
        do {
            if (!first)
            {
                current = current->next;
            }
            if (current->value == elem) {
                return true;
            }
            first = false;
        } while (current->next != nullptr);
    }
    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
    int nr = 0;
    int pos = this->hash(elem);
    ListNode* current = this->ht[pos];
    if (current->valid) {
        bool first = true;
        do {
            if (!first)
            {
                current = current->next;
            }
            if (current->value == elem) {
                nr++;
            }
            first = false;
        } while (current->next != nullptr);
    }
    return nr;
}



int SortedBag::size() const {
	//TODO - Implementation
    return this->nrElems;
}


bool SortedBag::isEmpty() const {
	//TODO - Implementation
    if (this->nrElems == 0) {
        return true;
    }
    return false;
}


SortedBagIterator SortedBag::iterator()  {
	return SortedBagIterator(*this);
}

int SortedBag::removeOccurrences(int nr, TComp elem) {
    // Best case = Theta(1) when nr<0
    // Worst case = Theta(nr)
    // Average case = O(nr)
    // Total Complexity = O(nr)
    if (nr < 0) {
        throw exception();
    }
    int removed = 0;
    int pos = this->hash(elem);
    ListNode* current = this->ht[pos];
    if (current->valid) {
        bool first = true;
        do {
            if (!first)
            {
                current = current->next;
            }
            if (current->value == elem) {
                if (current->prev == nullptr) {
                    // if its the first element in its list
                    if (current->next == nullptr)
                        current->valid = false;
                    else {
                        this->ht[pos] = current->next;
                        this->ht[pos]->prev = nullptr;
                    }
                }
                else {
                    //if not just jump over it
                    current->prev->next = current->next;
                    if (current->next != nullptr)
                        current->next->prev = current->prev;
                }
                this->nrElems--;
                removed++;
                if (removed == nr) {
                    return removed;
                }
            }
            first = false;
        } while (current->next != nullptr);
    }
    return removed;
}


SortedBag::~SortedBag() {
	//TODO - Implementation
    // mAyBe?
    delete this->ht;
}

ListNode** SortedBag::getSortedArray() const {
    // for the iterator
    int position = 0;
    auto* array = new ListNode*[m];
    for (int i = 0; i < m; i++)
    {
        if (this->ht[i]->valid)
        {
            ListNode* current = this->ht[i];
            bool first = true;
            do {
                if (!first)
                {
                    current = current->next;
                }
                array[position] = current;
                position++;
                first = false;
            } while (current->next != nullptr);
        }
    }
    int i, j;
    for (i = 0; i < position - 1; i++) {
        for (j = i; j < position; j++) {
            if (this->r(array[j]->value, array[i]->value)) {
                ListNode* aux = array[j];
                array[j] = array[i];
                array[i] = aux;
            }
        }
    }
    return array;
}
