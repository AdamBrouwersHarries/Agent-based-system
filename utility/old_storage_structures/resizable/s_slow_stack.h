/* 
 * File:   s_slow_stack.h
 * Author: adam harries
 *
 * A sloooow data structure for storing items. sloow push/pop.
 * 
 * Created on 14 February 2012, 13:08
 */

#ifndef S_SLOW_STACK_H
#define	S_SLOW_STACK_H

template <class object>
class s_slow_stack {
public:

		s_slow_stack() {
		}

		virtual ~s_slow_stack() {
		}

		void push_top(object t) {
				object* temp = new object[size + 1];
				for (int i = 0; i < size; i++) {
						temp[i] = mem[i];
				}
				temp[size] = t;
				if (size > 0) {
						delete[] mem;
				}
				mem = temp;
				size++;
		}

		void push_bottom(object t) {
				object* temp = new object[size + 1];
				for (int i = 0; i < size; i++) {
						temp[i + 1] = mem[i];
				}
				temp[0] = t;
				if (size > 0) {
						delete[] mem;
				}
				mem = temp;
				size++;
		}

		void push_index(object t, unsigned int index) {
				if (index <= size) {
						object* temp = new object[size + 1];
						for (int i = 0; i < index; i++) {
								temp[i] = mem[i];
						}
						for(int i = index;i<size;i++)
						{
								temp[i+1] = mem[i];
						}
						temp[index] = t;
						if (size > 0) {
								delete[] mem;
						}
						mem = temp;
						size++;
				}
		}

		object pop_top() {
				object r = mem[size-1];
				if(size>1)
				{
						object* temp = new object[size-1];
						for(int i = 0;i<size-1;i++)
						{
								temp[i] = mem[i];
						}
						delete[] mem;
						mem = temp;
				}else{
						delete[] mem;
				}
				size--;
		}

		object pop_bottom() {
				object r = mem[0];
				if(size>1)
				{
						object* temp = new object[size-1];
						for(int i = 1;i<size;i++)
						{
								temp[i-1] = mem[i];
						}
						delete[] mem;
						mem = temp;
				}else{
						delete[] mem;
				}
				size--;
		}
private:
		object* mem;
		unsigned int size;
};

#endif	/* S_SLOW_STACK_H */
