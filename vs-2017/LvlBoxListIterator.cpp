//
//LvlBoxListIterator.cpp
//

#include "LvlBoxListIterator.h"

 // Create iterator, over indicated list.
df::LvlBoxListIterator::LvlBoxListIterator(const LvlBoxList *p_list) {
	m_p_list = p_list;
	first();
}

// Set iterator to first item in list.
void df::LvlBoxListIterator::first() {
	m_index = 0;
}

// Set iterator to next item in list.
void df::LvlBoxListIterator::next() {
	if (m_index < m_p_list->m_count)
		m_index++;
}

// Return true if at end of list.
bool df::LvlBoxListIterator::isDone() const {
	return(m_index == m_p_list->m_count);
}

// Return pointer to current item in list, NULL if done/empty.
df::Box *df::LvlBoxListIterator::currentBox() const {
	return m_p_list->m_p_box[m_index];
}