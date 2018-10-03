//
// VectorList - A list of VECTORS.
//
// Copyright 2017 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __VECTOR_LIST_H__
#define __VECTOR_LIST_H__

#include "Vector.h"
#include "VectorListIterator.h"


	const int MAX_VECTORS = 5000;

	class VectorListIterator;

	class VectorList {

	private:
		int m_count;                    // Count of VECTORS in list.
		df::Vector *m_p_vect[MAX_VECTORS];   // Array of pointers to VECTORS.

	public:
		friend class VectorListIterator;           // Iterators can access.

		// Default constructor.
		VectorList();

		// Insert Vector pointer in list.
		// Return 0 if ok, else -1.
		int insert(df::Vector *p_o);

		// Remove Vector pointer from list,
		// Return 0 if found, else -1.
		int remove(df::Vector *p_o);

		// Clear list (setting count to 0).
		void clear();

		// Return count of number of VECTORS in list.
		int getCount() const;

		// Return true if list is empty, else false.
		bool isEmpty() const;

		// Return true if list is full, else false.
		bool isFull() const;
	};
#endif // __VECTOR_LIST_H__
