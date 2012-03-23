/* 
 * File:   s_linked_list.h
 * Author: adam
 *
 * Created on 21 February 2012, 14:25
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
		s_linked_list_element<object>* first;
		s_linked_list_element<object>* last;
		void add_element(object b)
		{
				s_linked_list_element<object>* new_object = new s_linked_list_element<object>;
				new_object->set_payload(b);
				if(first == NULL || last == NULL)
				{
						first = new_object;
						last = new_object;
				}else{
						new_object->set_previous(last);
						if(last!=NULL)
						{
							last->set_next(new_object);
						}
						last = new_object;
				}
				size++;
		}
		void remove_element(s_linked_list_element<object>* b)
		{
				if(b==first)
				{
						if(b==last)
						{
								first = NULL;
								last = NULL;
								delete b;
						}else{
								first = b->get_next();
								first->set_previous(NULL);
								delete b;
						}
				}else if(b==last)
				{
						last = b->get_previous();
						last->set_next(NULL);
						delete b;
				}else{
						b->get_next()->set_previous(b->get_previous());
						b->get_previous()->set_next(b->get_next());
						delete b;
				}
				size--;
		}
		int size;				
};

#endif	/* S_LINKED_LIST_H */

