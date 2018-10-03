//
//VectorListIterator.cpp
//

#include "VectorListIterator.h"

 // Create iterator, over indicated list.
df::VectorListIterator::VectorListIterator(const VectorList *p_list) {
	m_p_list = p_list;
	first();
}

// Set iterator to first item in list.
void df::VectorListIterator::first() {
	m_index = 0;
}

// Set iterator to next item in list.
void df::VectorListIterator::next() {
	if (m_index < m_p_list->m_count)
		m_index++;
}

// Return true if at end of list.
bool df::VectorListIterator::isDone() const {
	return(m_index == m_p_list->m_count);
}

// Return pointer to current item in list, NULL if done/empty.
df::Vector *df::VectorListIterator::currentVector() const {
	return m_p_list->m_p_vect[m_index];
}