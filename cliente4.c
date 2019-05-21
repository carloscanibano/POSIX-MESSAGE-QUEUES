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
	char keys[256];
	char value1[256];
	float value2;

  if (init() == -1) {
		printf("Error al inicializar la lista del servidor.\n");
	} else {
		printf("Lista del servidor inicializada correctamente.\n");
	}

  for (int i = 1; i < 100; i +=5) {
		sprintf(keys, "Key_%d", i);
		sprintf(value1, "Value_%d", i);
		if (set_value(keys, value1, i) == -1) {
			printf("Error al insertar tripleta %d en el servidor.\n", i);
		} else {
			printf("Tripleta %d insertada correctamente en el servidor.\n", i);
		}
	}

  for (int i = 30; i < 60; i++) {
    sprintf(keys, "Key_%d", i);
    if (get_value(keys, value1, &value2) == -1) {
      printf("Error al conseguir tripleta %d en el servidor.\n", i);
    } else {
      printf("Key: %s, Value1: %s, Value2: %f\n", keys, value1, value2);
    }
  }


  for (int i = 1; i < 101; i += 4) {
		sprintf(keys, "Key_%d", i);
		if (exist(keys) == -1) {
			printf("Tripleta %d no existe en el servidor.\n", i);
		} else {
			printf("Tripleta %d existe en el servidor.\n", i);
		}
	}

	return 0;
}
