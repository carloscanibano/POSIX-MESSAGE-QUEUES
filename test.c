#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "linked_list.h"

int main() {
	Triplet_list list;
	struct triplet t1 = {"key1", "value1", 1};
	struct triplet t2 = {"key2", "value2", 2};
	struct triplet t3 = {"key3", "value3", 3};
	struct triplet t4;

	/*if (insert(&list, &t1) == -1) {
		printf("Error al insertar tripleta en la lista.\n");
	}*/


	insert(&list, &t2);
	insert(&list, &t3);
	/*if (insert(&list, &t1) == -1) {
		printf("Error al insertar tripleta en la lista.\n");
	}*/

	t4 = *search(list, "key4");

	if ((strcmp(t4.key, "NOT_FOUND")) == 0) {
		printf("Error, tripleta no encontrada.\n");
	} else {
		printf("Valores encontrados para la tripleta: key(%s), first_value(%s), second_value(%f).\n",
			t4.key, t4.first_value, t4.second_value);
	}

	if (modify(&list, "key1", "valuemodificado", -1) == -1){
		printf("Error al modificar tripleta en la lista.\n");
	}

	if (delete(&list, "key2") == -1){
		printf("Error al eliminar tripleta en la lista.\n");
	}

	printf("La lista contiene: %d elementos.\n", elements(list));

	show(list);

	erase(&list);

	printf("Imprimir despues despues de vaciar el servidor\n");

	show(list);

	printf("La lista contiene: %d elementos.\n", elements(list));


}
