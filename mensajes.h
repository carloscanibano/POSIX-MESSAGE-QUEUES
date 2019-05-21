#ifndef _mensajes_h
#define _mensajes_h
#include "linked_list.h"

struct request {
	int op;
	struct triplet t;
	//Client queue name
	char q_name[255];
};

struct answer {
	int answer_code;
	struct triplet t;
};


#endif