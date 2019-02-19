#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <linked_list.h>
#include <claves.h>

int init() {

}

int set_value(char *key, char *value1, float value2) {
	mqd_t q_server;
	mqd_t q_client;
	struct request req;
	struct answer ans;

	q_client = mq_open();
}

int get_value(char *key, char *value1, float value2) {

}

int modify_value(char *key, char *value1, float value2) {

}

int delete_key(char *key) {

}

int exist(char *key) {

}

int num_items() {

}