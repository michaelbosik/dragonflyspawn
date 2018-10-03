//
//VectorList.cpp
//

#include "VectorList.h"


//Constructor
df::VectorList::VectorList() {
	m_count = 0;
}

// Insert Vector pointer in list.
// Return 0 if ok, else -1.
int df::VectorList::insert(Vector *p_o) {

	//If list is full, return -1
	//Else, add to list
	if (m_count == MAX_VECTORS)
		return -1;
	else {
		m_p_vect[m_count] = p_o;
		m_count++;
		return 0;
	}
}

// Remove Vector pointer from list,
// Return 0 if found, else -1.
int df::VectorList::remove(Vector *p_o) {

	//Goes trough every Vector in the list
	for (int i = 0; i < m_count; i++) {
		//If current Vector matches
		if (m_p_vect[i] == p_o) {
			int j = i;
			//Move every Vector in the list back one spot
			for (j; j < m_count - 1; j++) {
				m_p_vect[j] = m_p_vect[j + 1];
			}
			m_p_vect[j] = 0;
			m_count--;
			return 0;
		}
	}
	return -1;
}

// Clear list (setting count to 0).
void df::VectorList::clear() {
	m_count = 0;
}

// Return count of number of VECTORS in list.
int df::VectorList::getCount() const {
	return m_count;
}

// Return true if list is empty, else false.
bool df::VectorList::isEmpty() const {
	return (m_count == 0);
}

// Return true if list is full, else false.
bool df::VectorList::isFull() const {
	return (m_count == MAX_VECTORS);
}