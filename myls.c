#include <stdio.h>        /* Header file for system call printf */
#include <unistd.h>        /* Header file for system call gtcwd */
#include <sys/types.h>        /* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]) {

    DIR *descriptor;
    if (argc < 2) {
        char buf[PATH_MAX];
        getcwd(buf, PATH_MAX);
        descriptor = opendir(buf);
    }
    if (descriptor == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    struct dirent *file;
    while ((file = readdir(descriptor)) != NULL) {
        printf("%s\n", file->d_name);
    }

    return 0;
}
