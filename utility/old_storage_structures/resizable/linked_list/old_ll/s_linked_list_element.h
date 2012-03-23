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

		}
		//destructor
		virtual ~s_linked_list_element() {

		}
		//removes the element from a list, manages previous/next;
		//if it's the previous/first in a list, returns the new previous/next
		//don't forget! if it's in the middle of the list, itt'l return itself.
		s_linked_list_element* remove() {
				if (next != NULL) {
						//next is not null (next item in list)
						if (previous != NULL) {
								//previous is not null (no previous in list)
								next->previous = previous;
								previous->next = next;
								return this;
						} else {
								//previous is null (start of a list)
								next->previous = NULL;
								return next;
						}
				} else {
						//next is null (end of a list)
						previous->next = NULL;
						return previous;
				}
		}
		//adds an element after this element, manages pointers in adjacent elements
		void add_after(s_linked_list_element* dummy) {
				if (next == NULL) {
						//end of a list...
						next = dummy;
						dummy->previous = this;
				} else {
						next->previous = dummy;
						dummy->next = next;
						dummy->previous = this;
						next = dummy;
				}
		}
		//adds an element before the element, manages pointers in adjacent elements
		void add_before(s_linked_list_element* dummy) {
				if (next == NULL) {
						//start of the list...
						previous = dummy;
						dummy->next = this;
				} else {
						previous->next = dummy;
						dummy->previous = previous;
						dummy->next = this;
						previous = dummy;

				}
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
		object* get_payload_p() {
				return &payload;
		}
		void set_next(s_linked_list_element* n) {
				next = n;
		}
		void set_previous(s_linked_list_element* p) {
				previous = p;
		}
		s_linked_list_element* get_next() {
				return next;
		}
		s_linked_list_element* get_previous() {
				return previous;
		}

private:
		object payload;
		s_linked_list_element* next;
		s_linked_list_element* previous;

};

#endif	/* S_LINKED_LIST_ELEMENT_H */

