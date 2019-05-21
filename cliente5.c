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

  for (int i = 1; i < 101; i++) {
    sprintf(keys, "Key_%d", i);
    sprintf(value1, "Value_%d", i);
    if (set_value(keys, value1, i) == -1) {
      printf("Error al insertar tripleta %d en el servidor.\n", i);
    } else {
      printf("Tripleta %d insertada correctamente en el servidor.\n", i);
    }
  }

  printf("Elementos en el servidor: %d.\n", num_items());

	return 0;
}
