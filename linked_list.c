#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

int insert(Triplet_list l, struct triplet *t){
	Triplet_list p1, p2;
	p1 = l;
	int code = -1;

	if (search(l, t->key) == NULL) {
		return code;
	}

	if (p1 == NULL) {
		p1 = (struct triplet *) malloc(sizeof(struct triplet));
		strcpy(p1->key, t->key);
		strcpy(p1->first_value,t->first_value);
		p1->second_value = t->second_value;
		p1->link = NULL;
		code = 0;
	} else {
		while (p1->link != NULL) {
			p1 = p1->link;
		}
		p2 = (struct triplet *) malloc(sizeof(struct triplet));
		strcpy(p2->key, t->key);
		strcpy(p2->first_value, t->first_value);
		p2->second_value = t->second_value;
		p1->link = p2;
		code = 0;
	}
	return code;
}

void show(Triplet_list l) {
	while (l != NULL) {
		printf("key: %s, first_value: %s, second_value: %f", l->key, l->first_value, l->second_value);
		l = l->link;
	}
}

void erase(Triplet_list *l) {
	Triplet_list aux, p;
	p = *l;
	if (p != NULL) {
		while (p != NULL) {
			aux = p->link;
			free(p);
			p = aux;
		}
		*l = NULL;
	}
}

int elements(Triplet_list l) {
	Triplet_list cursor = l;
	int c = 0;
	while (cursor != NULL) {
		c++;
		cursor = cursor->link;
	}
	return c;
}

struct triplet* search(Triplet_list l, char *key) {
	Triplet_list cursor = l;
	while (cursor != NULL) {
		if (strcmp(cursor->key, key) == 0) {
			return cursor;
		}
		cursor = cursor->link;
	}
	return NULL;
}

int modify(Triplet_list l, char *key, char *value1, float value2) {
	int code = -1;
	Triplet_list cursor = l;
	if (search(l, key) == NULL) {
		return code;
	} else {
		while (cursor != NULL) {
			if (strcmp(cursor->key, key) == 0) {
				strcmp(cursor->first_value, value1);
				cursor->second_value = value2;
				return 0;
			}
			cursor = cursor->link;
		}	
	}
	return code;
}

int delete(Triplet_list l, char *key) {
	int code = -1;
	Triplet_list cursor = l;
	if (search(l, key) == NULL) {
		return code;
	} else {
		while (cursor != NULL) {
			if (strcmp(cursor->link->key, key) == 0) {
				cursor->link = cursor->link->link;
				free(cursor->link);
				return 0;
			}
		}
	}
	return code;
}
