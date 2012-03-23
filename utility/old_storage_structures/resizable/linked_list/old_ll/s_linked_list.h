/*
 * File:   s_linked_list.h
 * Author: Adam Harries
 *
 * a simple linked list.
 *
 * Created on 14 February 2012, 19:39
 */

#include "s_linked_list_element.h"

#ifndef S_LINKED_LIST_H
#define	S_LINKED_LIST_H

template <class object>
class s_linked_list {
public:
		s_linked_list() {
				size = 0;
		}
		virtual ~s_linked_list() {

		}
		//"pushes" the object d to the end of the list
		void add_end(object d) {
				s_linked_list_element<object>* temp = new s_linked_list_element<object>;
				temp->set_payload(d);
				if (first == NULL || last == NULL) {
						//there are no elements in the array AT ALL
						first = temp;
						last = temp;
				} else {
						last->add_after(temp);
						last = temp;
				}
				size++;				
		}
		//adds the object to the front of the list
		void add_start(object d){
				s_linked_list_element<object>* temp = new s_linked_list_element<object>;
				temp->set_payload(d);
				if(first == NULL && last == NULL){
						//no elements in array AT ALL
						first = temp;
						last = temp;
				}else{
						first->add_before(temp);
						first = temp;
				}
				
		}
		//gets a reference to the LINKED_LIST_ELEMENT at position i
		s_linked_list_element<object>* get_ll_at(unsigned int i){
				s_linked_list_element<object>* temp = new s_linked_list_element<object>;
				if (i < size) {
						if (i == 0) {
								return first;
						} else if (i == size - 1) {
								return last;
						}else{
								s_linked_list_element<object>* g = first;
								for(unsigned int j = 0;j<i;j++){
										g = g->get_next();
								}
								return g;
						}
				}else{
						return temp;
				}
		}
		object get_at(unsigned int i){
				object temp;
				if(i<size){
						return get_ll_at(i)->get_payload();
				}
				return temp;
		}
		//"pops" the last element from the end of the list. will need to be deleted after.
		s_linked_list_element<object>* remove_end() {
				size--;
				if (first == NULL && last == NULL) {
						s_linked_list_element<object>* false_returner = new s_linked_list_element<object>;
						return false_returner;
				} else {
						s_linked_list_element<object>* temp = last;
						last = last->remove();
						first = last;
						return temp;
				}
		}
		//"dequeues" the first element from the start of the list. will need to be deleted after.
		s_linked_list_element<object>* remove_start() {
				size--;
				if (first == NULL && last == NULL) {
						s_linked_list_element<object>* false_returner = new s_linked_list_element<object>;
						return false_returner;
				} else {
						s_linked_list_element<object>* temp = first;
						first = first->remove();
						last = first;
						return temp;
				}
		}
		//removes the element from a point in the middle of the list, returns it if poss
		s_linked_list_element<object>* remove_at(int i) {
				s_linked_list_element<object>* temp = new s_linked_list_element<object>;
				if (i < size) {
						if (i == 0) {
								return remove_start();
						} else if (i == size - 1) {
								return remove_end();
						}else{
								s_linked_list_element<object>* g = first;
								for(int j = 0;j<i;j++){
										g = g->get_next();
								}
								s_linked_list_element<object>* o_next = g->get_next();
								s_linked_list_element<object>* o_prev = g->get_previous();
								g->remove();
								o_next->set_previous(o_prev);
								o_prev->set_next(o_next); 
								return g;
						}
				}else{
						return temp;
				}
		}
		unsigned int get_size(){return size;}
private:
		s_linked_list_element<object>* first;
		s_linked_list_element<object>* last;
		unsigned int size;

};

#endif	/* S_LINKED_LIST_H */

