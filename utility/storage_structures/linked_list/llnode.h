#ifndef LLNODE_H
#define LLNODE_H

template <class payload_data>
class llnode {
public:
	llnode()
	{
		next_ptr = NULL;
		prev_ptr = NULL;
	}
	virtual ~llnode()
	{
		next_ptr = NULL;
		prev_ptr = NULL;
	}
	llnode<payload_data> *next_ptr;
	llnode<payload_data> *prev_ptr;
	payload_data payload;
};

#endif