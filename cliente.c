#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "claves.h"
#include "linked_list.h"

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

//No necesita lista abierta anteriormente, la inicia el
void cliente1() {
	char value1[255];
	float value2;

	//ESTADO INICIAL: LISTA SIN INICIALIZAR, NO HAY ELEMENTOS.

	if (init() == -1) {
		printf("Error al inicializar la lista del servidor.\n");
	} else {
		printf("Lista del servidor inicializada correctamente.\n");
	}

	//ESTADO 1: LISTA INICIALIZADA CORRECTAMENTE, 1 ELEMENTO

	if (set_value("Clave1", "Valor1", 0) == -1) {
		printf("Error al insertar tripleta en el servidor.\n");
	} else {
		printf("Tripleta insertada correctamente en el servidor.\n");
	}

	//ESTADO 2: INSERCION CORRECTA, 2 ELEMENTOS

	if (set_value("Clave1", "Valor1", 0) == -1) {
		printf("Error al insertar tripleta en el servidor.\n");
	} else {
		printf("Tripleta insertada correctamente en el servidor.\n");
	}

	//ESTADO 3: INSERCION FALLIDA, ¡CLAVE DUPLICADA!, 2 ELEMENTOS

	if (set_value("Clave2", "Valor2", 2) == -1) {
		printf("Error al insertar tripleta en el servidor.\n");
	} else {
		printf("Tripleta insertada correctamente en el servidor.\n");
	}

	//ESTADO 4: INSERCION CORRECTA, 3 ELEMENTOS

	if (set_value("Clave3", "Valor3", 3) == -1) {
		printf("Error al insertar tripleta en el servidor.\n");
	} else {
		printf("Tripleta insertada correctamente en el servidor.\n");
	}

	//ESTADO 5: INSERCION CORRECTA, 4 ELEMENTOS

	if (modify_value("Clave2", "Value2Mod", 20) == -1) {
		printf("Error al modificar tripleta en el servidor.\n");
	} else {
		printf("Tripleta modificada correctamente en el servidor.\n");
	}

	//ESTADO 6: MODIFICACION CORRECTA, 4 ELEMENTOS, 1 MODIFICADO
	//ESTADO ESPERADO: head->clave1->clave2(MOD)->clave3->NULL
	//COMPROBAR QUE ASI ES

	if (delete_key("Clave1") == -1) {
		printf("Error al eliminar tripleta en el servidor.\n");
	} else {
		printf("Tripleta eliminada correctamente del servidor.\n");
	}

	//ESTADO 7: ELIMINACION CORRECTA, 3 ELEMENTOS, 1 MODIFICADO
	//ESTADO ESPERADO: head->clave2(MOD)->clave3->NULL

	if (exist("Clave1") == -1) {
		printf("Error al buscar tripleta en el servidor.\n");
	} else {
		printf("Tripleta buscada correctamente en el servidor.\n");
	}

	//ESTADO 8: TRIPLETA NO EXISTE, 3 ELEMENTOS, 1 MODIFICADO

	if (exist("Clave2") == -1) {
		printf("Error al buscar tripleta en el servidor.\n");
	} else {
		printf("Tripleta buscada correctamente en el servidor.\n");
	}		

	//ESTADO 9: TRIPLETA EXISTE, 3 ELEMENTOS, 1 MODIFICADO

	if (set_value("Clave", "Valor", 453) == -1) {
		printf("Error al insertar tripleta en el servidor.\n");
	} else {
		printf("Tripleta insertada correctamente en el servidor.\n");
	}

	//ESTADO 10: INSERCION CORRECTA, 4 ELEMENTOS, 1 MODIFICADO
	//ESTADO ESPERADO: head->clave2(MOD)->clave3->clave->NULL

	if (get_value("Clave", value1, &value2) == -1) {
		printf("Error al obtener valores del servidor.\n");
	} else {
		printf("Valores recuperados del servidor correctamente.\n");
		printf("Primer valor: %s\n Segundo valor: %f\n", value1, value2);
	}

	//ESTADO 11: LECTURA CORRECTA, 4 ELEMENTOS, 1 MODIFICADO

	if (get_value("Clave1", value1, &value2) == -1) {
		printf("Error al obtener valores del servidor.\n");
	} else {
		printf("Valores recuperados del servidor correctamente.\n");
		printf("Primer valor: %s\n Segundo valor: %f\n", value1, value2);
	}

	//ESTADO 12: LECTURA INCORRECTA, 4 ELEMENTOS, 1 MODIFICADO	
}

//Necesita lista abierta
void cliente2() {
	char keys[256];
	char values[256];
	int flag = 1; //TRUE

	//Solo imprimir informacion si es necesario
	for (int i = 1; i < 100; i++) {
		sprintf(keys, "Key_%d", i);
		sprintf(values, "Value_%d", i);
		if (set_value(keys, values, i) == -1) {
			//printf("Error al insertar tripleta en el servidor.\n");
			flag = 0; //FALSE
		} else {
			//printf("Tripleta insertada correctamente en el servidor.\n");
		}	
	}

	if (!flag) printf("ERROR EN LA CREACION DE 100 TRIPLETAS\n");

	//ESTADO 1: CREACION CORRECTA DE 100 TRIPLETAS

	//Solo imprimir informacion si es necesario
	for (int i = 25; i < 51; i++) {
		sprintf(keys, "Key_%d", i);
		if (delete_key(keys) == -1) {
			//printf("Error al borrar tripleta en el servidor.\n");
			flag = 0; //FALSE
		} else {
			//printf("Tripleta borrada correctamente en el servidor.\n");
		}	
	}

	if (!flag) printf("ERROR EN EL BORRADO DE 25 TRIPLETAS\n");

	//ESTADO 2: BORRADO CORRECTO DE 25 TRIPLETAS
	//AÑADIRE MAS COSAS DESPUES, PERO PUEDES PROBAR LA CREACION Y EL BORRADO	

}

int main() {

	//Deberia funcionar todo sin error y obtener resultados coherentes
	test_funciones();
	//Para probar, invoca las diferentes funciones de cliente como arriba
	//CONSIDERA REINICIAR LA LISTA ENTRE CLIENTES SI ES NECESARIO (MEMORIA)
	//Algunos clientes necesitan la lista abierta o ellos solos la crean, mirar signatura

	//cliente1();
	//cliente2();
	return 0;
}
