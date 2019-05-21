#ifndef _claves_h
#define _claves_h

//Erase existent server-side linked list
int init();
//Insert new triplet into the server queue
int set_value(char *key, char *value1, float value2);
//Get values related to user specified key
int get_value(char *key, char *value1, float *value2);
//Modify triplets related to user specified key
int modify_value(char *key, char *value1, float value2);
//Delete triplet related to user specified key
int delete_key(char *key);
//Checks if any triplet has user specified key
int exist(char *key);
//Retrieves server-side linked list number of elements
int num_items();

#endif
