#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <elf.h>
#include <unistd.h>
#include <string.h>

union Header {
	ELF64_Ehdr x64;
	ELF32_Ehdr x32;
}

int main(int argc, char * argv[]) {
	int elf_fd = -1;
	unsigned char e_ident[EI_NIDENT];

	// Make sure we aren't derping where we should be herping...
	if (2 != argc) {
		printf("Usage: %s [ELF]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// If you didn't supply a real file what are you even doing?
	elf_fd = open(argv[1], O_RDONLY);
	if (-1 == elf_fd) {
		int err = errno;
		perror("open");
		exit(EXIT_FAILURE);		
	}	
	
	// Confirm ELF header
	// start simple, read in the first 16 bytes	
	int bytes_read = read(elf_fd, e_ident, EI_NIDENT);
	if (EI_NIDENT != bytes_read) {
		printf("Could not read %d bytes from file \"%s\" representing the elf header, quitting.\n", EI_NIDENT, argv[1]);
		exit(EXIT_FAILURE);
	}

	// compare the first four bytes to ensure we have a valid .ELF header
	if (0 != strncmp(ELFMAG, e_ident, SELFMAG)) {
		printf(".ELF header not found, quitting.\n");
		exit(EXIT_FAILURE);
	}

	printf("Found .ELF header, testing for 32-bit vs 64-bit.\n");


	exit(EXIT_SUCCESS);
}
