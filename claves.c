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
#include <errno.h>

#define NUM_MENSAJES 10

int init() {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());
	printf(id);

	mq_unlink(id);

	if ((q_client = mq_open(id, O_CREAT|O_RDWR, 0777, &attrib)) == -1) {
		printf("Error al abrir la cola de cliente.\n");
		exit(-1);
	}

	if ((q_server = mq_open(id_server, O_WRONLY)) == -1) {
		printf("Error al abrir la cola del servidor.\n");
	}

	//Setting up request
	req.op = 0;
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

//Insert new element into the server queue
int set_value(char *key, char *value1, float value2) {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";
	struct triplet t;

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());

	mq_unlink(id);

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

int get_value(char *key, char *value1, float *value2) {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";
	struct triplet t;

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());

	mq_unlink(id);

	if ((q_client = mq_open(id, O_CREAT | O_RDWR, 0777, &attrib)) == -1) {
		printf("Error al abrir la cola de cliente.\n");
		exit(-1);
	}

	if ((q_server = mq_open(id_server, O_WRONLY)) == -1) {
		printf("Error al abrir la cola del servidor.\n");
	}

	//Setting up client created triplet
	strcpy(t.key, key);
	t.link = NULL;

	//Setting up request
	req.op = 2;
	req.t = t;
	strcpy(req.q_name, id);

	if ((mq_send(q_server, (const char *) &req, sizeof(req), 0)) == -1) {
		printf("La petición no ha llegado al servidor.\n");
	}

	if ((mq_receive(q_client, (char *) &ans, sizeof(ans), 0)) == -1) {
		printf("No se ha podido recibir la respuesta del servidor.\n");
	}

	strcpy(value1, ans.t.first_value);
	*value2 = ans.t.second_value;

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

int modify_value(char *key, char *value1, float value2) {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";
	struct triplet t;

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());

	mq_unlink(id);

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
	req.op = 3;
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

int delete_key(char *key) {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";
	struct triplet t;

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());

	mq_unlink(id);

	if ((q_client = mq_open(id, O_CREAT | O_RDWR, 0777, &attrib)) == -1) {
		printf("Error al abrir la cola de cliente.\n");
		exit(-1);
	}

	if ((q_server = mq_open(id_server, O_WRONLY)) == -1) {
		printf("Error al abrir la cola del servidor.\n");
	}

	//Setting up client created triplet
	strcpy(t.key, key);
	t.link = NULL;

	//Setting up request
	req.op = 4;
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

int exist(char *key) {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";
	struct triplet t;

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());

	mq_unlink(id);

	if ((q_client = mq_open(id, O_CREAT | O_RDWR, 0777, &attrib)) == -1) {
		printf("Error al abrir la cola de cliente.\n");
		exit(-1);
	}

	if ((q_server = mq_open(id_server, O_WRONLY)) == -1) {
		printf("Error al abrir la cola del servidor.\n");
	}

	//Setting up client created triplet
	strcpy(t.key, key);
	t.link = NULL;

	//Setting up request
	req.op = 5;
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

int num_items() {
	mqd_t q_server;
	mqd_t q_client;
	struct mq_attr attrib;
	struct request req;
	struct answer ans;
	char id[256];
	char *id_server = "/SERVIDOR";

	attrib.mq_maxmsg = NUM_MENSAJES;
	attrib.mq_msgsize = sizeof(struct answer);

	sprintf(id, "/client_%d", getpid());

	mq_unlink(id);

	if ((q_client = mq_open(id, O_CREAT | O_RDWR, 0777, &attrib)) == -1) {
		printf("Error al abrir la cola de cliente.\n");
		exit(-1);
	}

	if ((q_server = mq_open(id_server, O_WRONLY)) == -1) {
		printf("Error al abrir la cola del servidor.\n");
	}

	//Setting up request
	req.op = 6;
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
