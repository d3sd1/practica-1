#include <stdio.h>        /* Header file for printf */
#include <sys/types.h>        /* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>        /* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    /*If the number of arguments is less than two (argv[0] -> program, argv[|] -> file to be shown) we print the error and return -1*/
    if (argc < 2) {
        printf("Not enough arguments\n");
        return -1;
    }
    int descriptor;    //Descriptor del fichero
    char buf[BUFFER_SIZE];    //Declaramos el buffer con el tamaño indicado

    descriptor = open(argv[1], O_RDONLY);
    if (descriptor < 0) {
        printf("Error opening file.\n");
        return -1;
    }

    int nread, nwrite;
    while ((nread = read(descriptor, buf, BUFFER_SIZE)) > 0) {
        do {
            nwrite = write(STDOUT_FILENO, buf, nread);
            if (nwrite < 0) {
                if (close(descriptor) < 0) {
                    printf("Error closing file.\n");
                    return -1;
                }
                printf("Error writing output to terminal.\n");
                return -1;
            }
            nread -= nwrite;

        } while (nread > 0);
    }

    return 0;
}
