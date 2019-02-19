#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "linked_list.h"
#include "claves.h"

int init() {

}

//Insert new element into the server queue
int set_value(char *key, char *value1, float value2) {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char *id;
	char *id_server = "Q_SERVER";
	struct triplet t;

	sprintf(id, "client_%d", getpid());
	if ((q_client = mq_open(id, O_CREAT | O_RDWR, 0777, &attrib)) == -1) {
		printf("Error al abrir la cola de cliente.\n");
		exit(-1);
	}

	if ((q_server = mq_open(id_server, O_WRONLY)) == -1) {
		printf("Error al abrir la cola del servidor.\n");
	}

	//Setting up client created triplet
	strcpy(t.key, key);
	strcpy(t.first_value, value1);
	t.second_value = value2;
	t.link = NULL;

	//Setting up request
	req.op = 1;
	req.index = -1;
	req.t = t;
	strcpy(req.q_name, id);

	if ((mq_send(q_server, (const char *) &req, sizeof(req), 0)) == -1) {
		printf("La petición no ha llegado al servidor.\n");
	}

	if ((mq_receive(q_client, (char *) &ans, sizeof(ans), 0)) == -1) {
		printf("No se ha podido recibir la respuesta del servidor.\n");
	}

	if ((mq_close(q_server)) == -1) {
		printf("Error al cerrar la cola del servidor.\n");
	}

	if ((mq_close(q_client)) == -1) {
		printf("Error al cerrar la cola del cliente.\n");
	}

	if ((mq_unlink(id)) == -1) {
		printf("Error al eliminar la cola del cliente.\n");
	}

	return ans.answer_code;
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
