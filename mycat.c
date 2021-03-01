#include <stdio.h>        /* Header file for printf */
#include <sys/types.h>        /* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>        /* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    int descriptor;    //Descriptor del fichero
    char buf[BUFFER_SIZE];    //Declaramos el buffer con el tamaño indicado


    /*
     * Read file and fetch descriptor.
     */
    descriptor = open(argv[1], O_RDONLY);
    if (descriptor < 0) {
        printf("Error opening file.\n");
        return -1;
    }

    /*
     * Read file line to line and output with STDOUT_FILENO
     */
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
    /*
     * We faced an error.
     */
    if (nread < 0) {
        printf("Error reading file.\n");
        if (close(descriptor) < 0) {
            printf("Error while closing file.\n");
        }
        return -1;

    }

    /*
     * Free memory, close descriptor.
     */
    if (close(descriptor) < 0) {
        printf("Error closing file.\n");
        return -1;
    }
    return 0;
}
