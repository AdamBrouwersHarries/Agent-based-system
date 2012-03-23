/* 
 * File:   s_stack_element.h
 * Author: adam
 *
 * Created on 12 February 2012, 17:14
 */

#ifndef S_STACK_ELEMENT_H
#define	S_STACK_ELEMENT_H

template <class object>
class s_stack_element
{
		public:
		s_stack_element(){}
		virtual ~s_stack_element(){}
		object payload;
		s_stack_element* next;
		s_stack_element* prev;		
};


#endif	/* S_STACK_ELEMENT_H */

