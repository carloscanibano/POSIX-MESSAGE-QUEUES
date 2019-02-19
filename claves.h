#ifndef _claves_h
#define _claves_h
#include <linked_list.h>

struct request {
	int op;
	int index;
	struct triplet t;
	//Client
	char q_name[255];
};

struct answer {
	int answer_code;
	struct triplet t;
};

int init();
int set_value(char *key, char *value1, float value2);
int get_value(char *key, char *value1, float value2);
int modify_value(char *key, char *value1, float value2);
int delete_key(char *key);
int exist(char *key);
int num_items();

#endif