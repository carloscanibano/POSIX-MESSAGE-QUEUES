#ifndef _linked_list_h
#define _linked_list_h

struct triplet{
	char key[255];
	char first_value[255];
	float second_value;
	struct triplet *link;
};

typedef struct triplet *Triplet_list;

//Insert triplet verified
int insert(Triplet_list *l, struct triplet *t);
//Show every element inside the linked list verified
void show(Triplet_list l);
//Erase the entire linked list verified
int erase(Triplet_list *l);
//Count linked list elements
int elements(Triplet_list l);
//Look for a specific triplet
struct triplet* search(Triplet_list l, char *key);
//Modify a existing value
int modify(Triplet_list l, char *key, char *value1, float value2);
//Delete single tuple
int delete(Triplet_list l, char *key);
//Verify if an element exist
int verify(Triplet_list l, char *key);

#endif
