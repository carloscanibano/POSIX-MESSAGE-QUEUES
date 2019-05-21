#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "claves.h"


int main() {
	int flag = 1;
	char keys[256];
	char value1[256];
	float value2;

	//Solo imprimir informacion si es necesario
	for (int i = 1; i < 25; i++) {
		sprintf(keys, "Key_%d", i);
		if (modify_value(keys, "mod", i + 900) == -1) {
			//printf("Error al borrar tripleta en el servidor.\n");
			flag = 0; //FALSE
			break;
		} else {
			printf("Tripleta %d editada correctamente en el servidor.\n", i);
		}
	}

	if (!flag) printf("Error al modificar tripletas en el servidor.\n");

		//Solo imprimir informacion si es necesario
	for (int i = 1; i < 25; i++) {
		sprintf(keys, "Key_%d", i);
		if (get_value(keys, value1, &value2) == -1) {
			//printf("Error al borrar tripleta en el servidor.\n");
			flag = 0; //FALSE
			break;
		} else {
			printf("Key: %s, Value1: %s, Value2: %f\n", keys, value1, value2);
		}
	}

	if (!flag) printf("Error al obtener valores en el servidor.\n");

	return 0;
}
