#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void insert(Triplet_list *l, struct triplet *t){
	Triplet_list p1, p2;
	p1 = *l;
	if (p1 == NULL) {
		p1 = (struct triplet *) malloc(sizeof(struct triplet));
		strcpy(p1->key, t->key);
		strcpy(p1->first_value,t->first_value);
		p1->second_value = t->second_value;
		p1->link = NULL;
	} else {
		while (p1->link != NULL) {
			p1 = p1->link;
		}
		p2 = (struct triplet *) malloc(sizeof(struct triplet));
		strcpy(p2->key, t->key);
		strcpy(p2->first_value, t->first_value);
		p2->second_value = t->second_value;
		p1->link = p2;
	}
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