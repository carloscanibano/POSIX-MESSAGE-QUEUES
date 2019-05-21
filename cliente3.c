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

	//Solo imprimir informacion si es necesario
	for (int i = 1; i < 101; i += 2) {
		sprintf(keys, "Key_%d", i);
		if (exist(keys) == -1) {
			printf("Tripleta %d no existe en el servidor.\n", i);
		} else {
			printf("Tripleta %d existe en el servidor.\n", i);
		}
	}

	return 0;
}
