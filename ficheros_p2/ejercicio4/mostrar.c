#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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
	
	int opt;
	int bytes = 0;
	while((opt = getopt(argc, argv, "n:e")) != -1) {
		switch(opt) {
		case 'n':
			bytes = optarg;
			break;
		case 'e':
			break;
		}
	}
	return 0;
}
