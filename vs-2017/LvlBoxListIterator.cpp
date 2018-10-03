//
//LvlBoxListIterator.cpp
//

#include "LvlBoxListIterator.h"

 // Create iterator, over indicated list.
LvlBoxListIterator::LvlBoxListIterator(const LvlBoxList *p_list) {
	m_p_list = p_list;
	first();
}

// Set iterator to first item in list.
void LvlBoxListIterator::first() {
	m_index = 0;
}

// Set iterator to next item in list.
void LvlBoxListIterator::next() {
	if (m_index < m_p_list->m_count)
		m_index++;
}

// Return true if at end of list.
bool LvlBoxListIterator::isDone() const {
	return(m_index == m_p_list->m_count);
}

// Return pointer to current item in list, NULL if done/empty.
df::Box *LvlBoxListIterator::currentBox() const {
	return m_p_list->m_p_box[m_index];
}