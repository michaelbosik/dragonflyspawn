//
// VectorListIterator - An iterator for VectorLists.
//
// Copyright 2017 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __VECTOR_LIST_ITERATOR_H__
#define __VECTOR_LIST_ITERATOR_H__

#include "Vector.h"
#include "VectorList.h"

namespace df {

	class VectorList;

	class VectorListIterator {

	private:
		VectorListIterator();	        // Iterator must be given list when created.
		int m_index;			// Index into list.
		const VectorList *m_p_list;	// List iterating over.

	public:
		// Create iterator, over indicated list.
		VectorListIterator(const VectorList *p_list);

		// Set iterator to first item in list.
		void first();

		// Set iterator to next item in list.
		void next();

		// Return true if at end of list.
		bool isDone() const;

		// Return pointer to current item in list, NULL if done/empty.
		Vector *currentVector() const;
	};

} // end of namespace df
#endif // __VECTOR_LIST_ITERATOR_H__
