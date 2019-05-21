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

	for (int i = 1; i < 20; i++) {
		sprintf(keys, "Key_%d", i);
		if (modify_value(keys, "mod", i + 400) == -1) {
      printf("Error al modificar tripleta %d en el servidor.\n", i);
		} else {
			printf("Tripleta %d editada correctamente en el servidor.\n", i);
		}
	}

  for (int i = 30; i < 60; i += 2) {
		sprintf(keys, "Key_%d", i);
		if (delete_key(keys) == -1) {
			printf("Error al borrar tripleta %d en el servidor.\n", i);
		} else {
			printf("Tripleta %d borrada correctamente en el servidor.\n", i);
		}
	}

  printf("Elementos en el servidor: %d.\n", num_items());
	return 0;
}
