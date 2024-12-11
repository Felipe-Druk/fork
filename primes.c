#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXPIPE 2

const int ERROR = -1;
const int MINPRIMO = 2;
const int MINARG = 2;

enum estados { CONTINUAR, TERMINAR };

enum pipe { LECTURA = 0, ESCRITURA };

void procesoHijo(int pipedf[MAXPIPE]);

int mostrarPrimos(int pipedf[MAXPIPE]);

int
main(int argc, char *argv[])
{
	if (argc < MINARG) {
		return ERROR;
	}
	int n = atoi(argv[1]);

	int pipedf[MAXPIPE];
	if (pipe(pipedf) < 0) {
		return ERROR;
	}

	for (int i = MINPRIMO; i <= n; i++) {
		write(pipedf[ESCRITURA], &i, sizeof(i));
	}
	int i = -1;
	write(pipedf[ESCRITURA], &i, sizeof(i));
	return mostrarPrimos(pipedf);
}

void
procesoHijo(int pipedf[MAXPIPE])
{
	int prime;
	read(pipedf[LECTURA], &prime, sizeof(prime));
	if (prime < 0) {
		exit(TERMINAR);
	}
	printf("Primo %i\n", prime);
	int i = 1;
	read(pipedf[0], &i, sizeof(i));
	while (i > 0) {
		if (i % prime != 0) {
			write(pipedf[ESCRITURA], &i, sizeof(i));
		}
		read(pipedf[LECTURA], &i, sizeof(i));
	}
	i = -1;
	write(pipedf[ESCRITURA], &i, sizeof(i));
	exit(CONTINUAR);
}

int
mostrarPrimos(int pipedf[MAXPIPE])
{
	int estatus, pid, estadoHijo = 0;
	while (estadoHijo != TERMINAR) {
		pid = fork();
		if (pid < 0) {
			return ERROR;
		}
		if (!pid) {
			// hijo
			procesoHijo(pipedf);
		} else {
			// padre
			wait(&estatus);
			estadoHijo = WEXITSTATUS(estatus);
		}
	}
	return 0;
}