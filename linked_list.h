#ifndef _linked_list_h
#define _linked_list_h

struct triplet{
	char key[255];
	char first_value[255];
	float second_value;
	struct triplet *link;
};

typedef struct triplet *Triplet_list;

void insert(Triplet_list *l, struct triplet *t);
void show(Triplet_list l);
void erase(Triplet_list *l);

#endif