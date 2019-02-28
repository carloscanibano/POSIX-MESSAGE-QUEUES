#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "linked_list.h"
#include "claves.h"

/* mutex y variables condicionales para proteger la copia del mensaje*/
pthread_mutex_t mutex_mensaje;
int mensaje_no_copiado = 1; /* TRUE con valor a 1 */
pthread_cond_t cond_mensaje;
Triplet_list server; /* server list */
struct triplet first; /* first node of list */

void tratar_mensaje(struct request *mes){
  struct request mensaje; /* mensaje local */
  mqd_t q_cliente; /* cola del cliente */
  struct answer result; /* resultado de la petición */
  /* el thread copia el mensaje a un mensaje local */
  pthread_mutex_lock(&mutex_mensaje);

  mensaje.op = mes->op;
  strcpy(mensaje.t.key, mes->t.key);
  strcpy(mensaje.t.first_value, mes->t.first_value);
  mensaje.t.second_value = mes->t.second_value;
  strcpy(mensaje.q_name, mes->q_name);

  /* ya se puede despertar al servidor*/
  mensaje_no_copiado = 0; /* FALSE con valor 0 */
  pthread_cond_signal(&cond_mensaje);
  pthread_mutex_unlock(&mutex_mensaje);

  if (mensaje.op == 0) {
    if (server != NULL){
      result.answer_code = erase(&server);
      insert(server, &first);
    }else{
      printf("Iniciado correctamente\n");
      result.answer_code = insert(server, &first);
    }

  }else if (server != NULL) {
    if (mensaje.op == 1) {
      result.answer_code = insert(server, &mensaje.t);
    }else if (mensaje.op == 2) {
      result.answer_code = verify(server, mensaje.t.key);
      if (result.answer_code == 0){
         result.t = *search(server, mensaje.t.key);
      }
    }else if (mensaje.op == 3) {
     result.answer_code = modify(server, mensaje.t.key, mensaje.t.first_value, mensaje.t.second_value);
    }else if (mensaje.op == 4) {
      result.answer_code = delete(server, mensaje.t.key);
    }else if (mensaje.op == 5) {
      result.answer_code = verify(server, mensaje.t.key);
    }else if (mensaje.op == 6) {
      result.answer_code = elements(server);
    }
  }


  /* Se devuelve el resultado al cliente */
  /* Para ello se envía el resultado a su cola */
  printf(mensaje.q_name);
  q_cliente = mq_open(mensaje.q_name, O_WRONLY);
  if (q_cliente == -1){
    printf("No se puede abrir la cola del cliente\n");
  }else {
    mq_send(q_cliente, (const char *) &result, sizeof(result), 0);
    mq_close(q_cliente);
  }

  pthread_exit(0);

}


int main(void){
  mqd_t q_servidor; /* cola del servidor */
  struct request mess; /* mensaje a recibir */
  struct mq_attr q_attr; /* atributos de la cola */
  pthread_attr_t t_attr; /* atributos de los threads */
  pthread_t thid;
  q_attr.mq_maxmsg = 10;
  q_attr.mq_msgsize = sizeof(struct request);

  q_servidor = mq_open("/SERVIDOR", O_CREAT|O_RDONLY, 0777, &q_attr);
  if (q_servidor == -1) {
    printf("No se puede crear el  servidor.\n");
  }

  pthread_mutex_init(&mutex_mensaje, NULL);
  pthread_cond_init(&cond_mensaje, NULL);
  pthread_attr_init(&t_attr);
  /* atributos de los threads, threads independientes */
  pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

  while (1) {
    mq_receive(q_servidor, (char *) &mess, sizeof(mess), 0);
    pthread_create(&thid, &t_attr, (void *)tratar_mensaje, &mess);
    /* se espera a que el thread copie el mensaje */
    pthread_mutex_lock(&mutex_mensaje);
    while (mensaje_no_copiado){
      pthread_cond_wait(&cond_mensaje, &mutex_mensaje);
    }
    mensaje_no_copiado = 1;
    pthread_mutex_unlock(&mutex_mensaje);
  } /* FIN while */
} /* Fin main */
