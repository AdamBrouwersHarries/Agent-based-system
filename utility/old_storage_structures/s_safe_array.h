/* 
 * File:   s_safe_array.h
 * Author: adam
 *
 * Created on 14 February 2012, 13:22
 */

#ifndef S_SAFE_ARRAY_H
#define	S_SAFE_ARRAY_H

template <class object>
class s_safe_array {
public:

		s_safe_array() {
				mem = NULL;
		}
		s_safe_array(int s){
				mem = NULL;
				initialise(s);
		}

		virtual ~s_safe_array() {
				if(mem!=NULL)
				{
						delete[] mem;
				}
		}
		void initialise(int s){
				if(mem!=NULL)
				{
						delete[] mem;
				}
				mem = new object[s];
				size = s;
		}
		unsigned int get_size()
		{
				return size;
		}
		object get(int a){
				return mem[a];
		}
		object* get_p(int a)
		{
				return &mem[a];
		}
		void set(int a, object p){
				mem[a] = p;
		}
private:
		object* mem;
		unsigned int size;
};

#endif	/* S_SAFE_ARRAY_H */

