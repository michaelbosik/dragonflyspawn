//
//ObjectList.cpp
//

#include "ObjectList.h"


//Constructor
df::ObjectList::ObjectList() {
	m_count = 0;
}

// Insert object pointer in list.
// Return 0 if ok, else -1.
int df::ObjectList::insert(Object *p_o) {

	//If list is full, return -1
	//Else, add to list
	if (m_count == MAX_OBJECTS)
		return -1;
	else {
		m_p_obj[m_count] = p_o;
		m_count++;
		return 0;
	}
}

// Remove object pointer from list,
// Return 0 if found, else -1.
int df::ObjectList::remove(Object *p_o) {

	//Goes trough every object in the list
	for (int i = 0; i < m_count; i++) {
		//If current object matches
		if (m_p_obj[i] == p_o) {
			int j = i;
			//Move every object in the list back one spot
			for (j; j < m_count - 1; j++) {
				m_p_obj[j] = m_p_obj[j+1];
			}
			m_p_obj[j] = NULL;
			m_count--;
			return 0;
		}
	}
	return -1;
}

// Clear list (setting count to 0).
void df::ObjectList::clear() {
	m_count = 0;
}

// Return count of number of objects in list.
int df::ObjectList::getCount() const {
	return m_count;
}

// Return true if list is empty, else false.
bool df::ObjectList::isEmpty() const {
	return (m_count == 0);
}

// Return true if list is full, else false.
bool df::ObjectList::isFull() const {
	return (m_count == MAX_OBJECTS);
}