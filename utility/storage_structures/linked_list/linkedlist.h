#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "llnode.h"

template <class payload_data>
class linkedlist {
public:
	linkedlist()
	{
		dummy_start.next_ptr = &dummy_end;
		dummy_end.prev_ptr = &dummy_start;
	}
	virtual ~linkedlist()
	{
		//need to add code to delete new nodes
		std::cout<<"deleting the nodes...\n";
		llnode<payload_data>* itr = dummy_end.prev_ptr;
		while(itr!= &(dummy_start))
		{
			llnode<payload_data>* next = itr->prev_ptr;
			delete itr;
			itr = next;
		}
	}
	//function adds a node to the "end" of the list, 
	//given the payload as an argument
	llnode<payload_data> * add_node(payload_data new_payload)
	{
		llnode<payload_data> *new_node = new llnode<payload_data>;
		new_node->payload = new_payload;
		//set pointers for the new node
		new_node->prev_ptr = dummy_end.prev_ptr;
		new_node->next_ptr = &dummy_end;
		//set pointers for its new next and prev nodes
		dummy_end.prev_ptr->next_ptr = new_node;
		dummy_end.prev_ptr = new_node;
		return new_node;
	}
	//removes a node from the function
	//not very safe, simply checks to make sure that it's not
	//the start or end "dummy" nodes
	void remove_node(llnode<payload_data> *rem_node)
	{
		if(rem_node != NULL && rem_node!=&dummy_start && rem_node!=&dummy_end)
		{
			llnode<payload_data> *prev_node = rem_node->prev_ptr;
			llnode<payload_data> *next_node = rem_node->next_ptr;
			prev_node->next_ptr = next_node;
			next_node->prev_ptr = prev_node;
			delete rem_node;
		}
	}
	llnode<payload_data>* get_first()
	{
		if(is_empty() == false)
		{
			return dummy_start.next_ptr;
		}else{
			return NULL;
		}
	}
	llnode<payload_data>* get_last()
	{
		if(is_empty() == false)
		{
			return dummy_end.prev_ptr;
		}else{
			return NULL;
		}
	}
	bool is_empty()
	{
		return !(dummy_start.next_ptr = &dummy_end);
	}
	llnode<payload_data> dummy_start;
	llnode<payload_data> dummy_end;
};

#endif