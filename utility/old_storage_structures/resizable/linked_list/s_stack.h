/* 
 * File:   s_stack.h
 * Author: adam
 *
 * Created on 12 February 2012, 00:02
 */

#ifndef S_STACK_H
#define	S_STACK_H

#include "s_stack_element.h"

template <class object>
class s_stack {
private:
		unsigned int size;
		s_stack_element<object>* first;
		s_stack_element<object>* last;
public:

		s_stack() {
				size = 0;
		}

		virtual ~s_stack() {

		}

		unsigned int get_size() {
				return size;
		}

		void push(object t) {
				if (size == 0 && (first == NULL) &&(last == NULL)) {
						s_stack_element<object>* temp = new s_stack_element<object > ();
						temp->payload = t;
						first = temp;
						last = temp;
						size++;
				} else {
						s_stack_element<object>* temp = new s_stack_element<object > ();
						temp->payload = t;
						temp->prev = last;
						last->next = temp;
						last = temp;
						size++;
				}
		}
		//do not forget to delete the object after getting it back...

		object pop() {
				object t;
				//check to see if there's anything in the list at all...
				if (last != NULL) {
						//if we have more than one element...
						if (first != last) {
								//set the return object to the payload of the last element
								t = last->payload;
								if (last->prev != first) {
										//set new last element
										last = last->prev;
										//destroy new last element's next pointer by deleting (will delete old last);
										delete last->next;
								} else {
										last = first;
										delete last->next;
								}
						} else {
								t = last->payload;
								delete last;
						}
						size--;
				} else {
						std::cout << "list empty.";
				}
				return t;
		}

		object get(unsigned int i, object nada) {
				if (i < size) {
						s_stack_element<object>* it = first;
						for (unsigned int a = 0; a < i; a++) {
								if (it != NULL) {
										it = it->next;
								}
						}
						if (it != NULL) {
								return it->payload;
						}
				}
				return nada;
		}

		void get(int i, object* n) {
				
						if (i < size) {
								s_stack_element<object>* it = first;
								for (int a = 0; a < i; a++) {
										if (it != NULL) {
												it = it->next;
										}
								}
								if (it != NULL) {
										n = &(it->payload);
								}
						}
				
		}
		void set(int i, object n) {
				if(i<size)
				{
						s_stack_element<object>* it = first;
						for(int a=0;a<i;a++)
						{
								if(it!=NULL)
								{
									it = it->next;
								}
						}
						if(it!=NULL)
						{
								it->payload = n;
						}
				}
		}
};

#endif	/* S_STACK_H */

