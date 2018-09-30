//
//ObjectListIterator.cpp
//

#include "ObjectListIterator.h"

 // Create iterator, over indicated list.
df::ObjectListIterator::ObjectListIterator(const ObjectList *p_list) {
	m_p_list = p_list;
	first();
}

// Set iterator to first item in list.
void df::ObjectListIterator::first() {
	m_index = 0;
}

// Set iterator to next item in list.
void df::ObjectListIterator::next() {
	if(m_index < m_p_list->m_count)
		m_index++;
}

// Return true if at end of list.
bool df::ObjectListIterator::isDone() const {
	return(m_index == m_p_list->m_count);
}

// Return pointer to current item in list, NULL if done/empty.
df::Object *df::ObjectListIterator::currentObject() const {
	return m_p_list->m_p_obj[m_index];
}