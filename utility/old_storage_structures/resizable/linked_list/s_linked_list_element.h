/* 
 * File:   s_linked_list_element.h
 * Author: Adam Harries
 * 
 * Linked list element, for simple linked list class
 *
 * Created on 14 February 2012, 19:41
 */

#ifndef S_LINKED_LIST_ELEMENT_H
#define	S_LINKED_LIST_ELEMENT_H

template <class object>
class s_linked_list_element {
public:
		//constructor
		s_linked_list_element() {
				next = NULL;
				previous = NULL;
		}
		//destructor
		virtual ~s_linked_list_element() {

		}
		/*
		 * -------------------------------------
		 *  GETTERS/SETTERS FOR PRIVATE ELEMENTS
		 * -------------------------------------
		 */
		void set_payload(object p) {
				payload = p;
		}
		object get_payload() {
				return payload;
		}
		void set_next(s_linked_list_element<object>* n) {
				next = n;
		}
		void set_previous(s_linked_list_element<object>* p) {
				previous = p;
		}
		s_linked_list_element<object>* get_next() {
				return next;
		}
		s_linked_list_element<object>* get_previous() {
				return previous;
		}

private:
		object payload;
		s_linked_list_element<object>* next;
		s_linked_list_element<object>* previous;

};

#endif	/* S_LINKED_LIST_ELEMENT_H */

