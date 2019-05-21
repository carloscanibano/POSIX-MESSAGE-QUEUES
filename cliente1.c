#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "claves.h"

//Esta funcion prueba las operaciones del servidor individualmente
void test_funciones() {
	//struct triplet t = {"Clave 1", "Valor 1", 1};
	char value1[255];
	float value2;

	if (init() == -1) {
		printf("Error al inicializar la lista del servidor.\n");
	} else {
		printf("Lista del servidor inicializada correctamente.\n");
	}

	if (set_value("Clave1", "Valor1", 0) == -1) {
		printf("Error al insertar tripleta en el servidor.\n");
	} else {
		printf("Tripleta insertada correctamente en el servidor.\n");
	}

	if (get_value("Clave1", value1, &value2) == -1) {
		printf("Error al obtener valores del servidor.\n");
	} else {
		printf("Valores recuperados del servidor correctamente.\n");
		printf("Primer valor: %s\n Segundo valor: %f\n", value1, value2);
	}

	if (modify_value("Clave1", "ValueMod", 2) == -1) {
		printf("Error al modificar tripleta en el servidor.\n");
	} else {
		printf("Tripleta modificada correctamente en el servidor.\n");
	}

	if (delete_key("Clave1") == -1) {
		printf("Error al eliminar tripleta en el servidor.\n");
	} else {
		printf("Tripleta eliminada correctamente del servidor.\n");
	}

	if (exist("Clave1") == -1) {
		printf("Error al buscar tripleta en el servidor.\n");
	} else {
		printf("Tripleta buscada correctamente en el servidor.\n");
	}

	if (num_items() == -1) {
		printf("Error al contar tripletas existentes en el servidor.\n");
	} else {
		printf("El número de tripletas en el servidor asciende a: %d.\n", num_items());
	}
}

void cliente1() {
	char keys[256];
	char values[256];
	int flag = 1; //TRUE

	//Solo imprimir informacion si es necesario
	for (int i = 1; i < 101; i++) {
		sprintf(keys, "Key_%d", i);
		sprintf(values, "Value_%d", i);
		if (set_value(keys, values, i) == -1) {
			//printf("Error al insertar tripleta en el servidor.\n");
			flag = 0; //FALSE
			break;
		} else {
			printf("Tripleta %d insertada correctamente en el servidor.\n", i);
		}
	}

	if (!flag) printf("ERROR EN LA CREACION DE 100 TRIPLETAS\n");

	//ESTADO 1: CREACION CORRECTA DE 100 TRIPLETAS

	//Solo imprimir informacion si es necesario
	for (int i = 25; i < 50; i++) {
		sprintf(keys, "Key_%d", i);
		if (delete_key(keys) == -1) {
			//printf("Error al borrar tripleta en el servidor.\n");
			flag = 0; //FALSE
			break;
		} else {
			printf("Tripleta %d borrada correctamente en el servidor.\n", i);
		}
	}

	if (!flag) printf("ERROR EN EL BORRADO DE 25 TRIPLETAS\n");

	printf("Elementos en el servidor: %d.\n", num_items());

}

int main() {
	cliente1();
	return 0;
}
