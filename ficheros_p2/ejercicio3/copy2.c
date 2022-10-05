#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/stat.h>

const int tam = 512;

void copy(int fdo, int fdd)
{
	int c,ret;
	unsigned char stream[tam];

	/* Read file byte by byte */
	while ((c = read(fdo, stream, tam)) > 0) {
		/* Print byte to stdout */

		ret = write(fdd,stream,c);

		if (ret == -1){
			close(fdd);
			close(fdo);
			err(3,"putc() failed!!");
		}
	}

	close(fdd);
	close(fdo);
}

void copyLink(char* fo, char* fd, struct stat* s){
	char* c = malloc(s->st_size + 1);
	if(readlink(fo, c, s->st_size + 1)==-1)
		err(2, "Error leyendo el link");
	
	if(symlink(fd, c) == -1)
		err(2, "Error creando el link");
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
		exit(1);
	}

	int origin, destiny;

		/* Open file */
	if ((origin = open(argv[1], O_RDONLY)) == -1)
		err(2,"The input file %s could not be opened",argv[1]);

	if ((destiny = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0660)) == -1)
		err(2,"The input file %s could not be opened",argv[2]);

	struct stat s;
	if(lstat(argv[1], &s) == -1)
		err(2, "Error checkeando el tipo del archivo origen %s", argv[1]);
	
	fprintf(stderr, "%i\n", s.st_mode);
	if(s.st_mode == 33204){
		copyLink(argv[1], argv[2], &s);
	}
	else if(s.st_mode == 33200)
		copy(origin, destiny);
	else
		err(2, "Tipo de archivo no soportado para copiar");

	return 0;
}
