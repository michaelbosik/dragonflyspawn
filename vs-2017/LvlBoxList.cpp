//
//LvlBoxList.cpp
//

#include "LvlBoxList.h"


//Constructor
LvlBoxList::LvlBoxList() {
	m_count = 0;
}

// Insert Box pointer in list.
// Return 0 if ok, else -1.
int LvlBoxList::insert(df::Box *p_o) {

	//If list is full, return -1
	//Else, add to list
	if (m_count == MAX_BOXES)
		return -1;
	else {
		m_p_box[m_count] = p_o;
		m_count++;
		return 0;
	}
}

// Remove Box pointer from list,
// Return 0 if found, else -1.
int LvlBoxList::remove(df::Box *p_o) {

	//Goes trough every Box in the list
	for (int i = 0; i < m_count; i++) {
		//If current Box matches
		if (m_p_box[i] == p_o) {
			int j = i;
			m_p_box[j] = 0;
			//Move every Box in the list back one spot
			for (j; j < m_count - 1; j++) {
				m_p_box[j] = m_p_box[j + 1];
			}
			m_count--;
			return 0;
		}
	}
	return -1;
}

// Clear list (setting count to 0).
void LvlBoxList::clear() {
	m_count = 0;
}

// Return count of number of Boxs in list.
int LvlBoxList::getCount() const {
	return m_count;
}

// Return true if list is empty, else false.
bool LvlBoxList::isEmpty() const {
	return (m_count == 0);
}

// Return true if list is full, else false.
bool LvlBoxList::isFull() const {
	return (m_count == MAX_BOXES);
}