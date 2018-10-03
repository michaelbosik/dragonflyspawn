//
// LvlBoxListIterator - An iterator for LvlBoxLists.
//


#ifndef __LVL_BOX_LIST_ITERATOR_H__
#define __LVL_BOX_LIST_ITERATOR_H__

#include "Box.h"
#include "LvlBoxList.h"

namespace df {

class LvlBoxList;

class LvlBoxListIterator {

private:
	LvlBoxListIterator();	        // Iterator must be given list when created.
	int m_index;			// Index into list.
	const LvlBoxList *m_p_list;	// List iterating over.

public:
	// Create iterator, over indicated list.
	LvlBoxListIterator(const LvlBoxList *p_list);

	// Set iterator to first item in list.
	void first();

	// Set iterator to next item in list.
	void next();

	// Return true if at end of list.
	bool isDone() const;

	// Return pointer to current item in list, NULL if done/empty.
	Box *currentBox() const;
};

} // end of namespace df
#endif // __LVL_BOX_LIST_ITERATOR_H__
