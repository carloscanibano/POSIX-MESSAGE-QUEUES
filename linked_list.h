#ifndef _linked_list_h
#define _linked_list_h

struct topic{
	char name[255];
	struct user *userList;
	struct topic *nextTopic;
};

struct user{
	short ip;
	long port;
	struct user *nextUser;
};

typedef struct topic *Topic_list;
typedef struct user *User_list;

//Insert topic
int insert_topic(Triplet_list *l, struct triplet *t);
//Subscribe user to existing topic
int insert_user_topic(Triplet_list *l, struct triplet *t);
//Subscribe user to non existing topic
int insert_user_notopic(Triplet_list *l, struct triplet *t);
//Show every element inside the linked list verified
void show(Triplet_list l);
//Erase the entire linked list verified
int erase(Triplet_list *l);
//Count linked list elements
int elements(Triplet_list l);
//Look for a specific triplet
struct triplet* search(Triplet_list l, char *key);
//Modify a existing value
int modify(Triplet_list *l, char *key, char *value1, float value2);
//Delete single tuple
int delete(Triplet_list *l, char *key);
//Verify if an element exist
int verify(Triplet_list l, char *key);

#endif
