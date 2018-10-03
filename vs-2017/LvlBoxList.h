//
// LvlBoxList - A list of boxes in a level.
//

#ifndef __LVL_BOX_LIST_H__
#define __LVL_BOX_LIST_H__

#include "Box.h"
#include "LvlBoxListIterator.h"

	const int MAX_BOXES = 5000;

	class LvlBoxListIterator;

	class LvlBoxList {

	private:
		int m_count;                    // Count of objects in list.
		df::Box *m_p_box[MAX_BOXES];   // Array of pointers to objects.

	public:
		friend class LvlBoxListIterator;           // Iterators can access.

		// Default constructor.
		LvlBoxList();

		// Insert box pointer in list.
		// Return 0 if ok, else -1.
		int insert(df::Box *p_o);

		// Remove box pointer from list,
		// Return 0 if found, else -1.
		int remove(df::Box *p_o);

		// Clear list (setting count to 0).
		void clear();

		// Return count of number of objects in list.
		int getCount() const;

		// Return true if list is empty, else false.
		bool isEmpty() const;

		// Return true if list is full, else false.
		bool isFull() const;
	};

#endif // __LVL_BOX_LIST_H__
