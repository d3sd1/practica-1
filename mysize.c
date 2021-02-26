#include <stdio.h>    /*Header file for system call printf*/
#include <sys/types.h>    /*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>    /*Header file for system call fcntl*/
#include <dirent.h>    /*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>


int main(int argc, char *argv[]) {

    DIR *descriptor;
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    descriptor = opendir(buffer);

    struct dirent *file;
    mainReader:
    while ((file = readdir(descriptor)) != NULL) {
            int fDescriptor = open(file->d_name, O_RDONLY);
            if (fDescriptor < 0) {
                printf("Error opening file -> %s\n", file->d_name);
                goto mainReader;
            }
            int fileSize = lseek(fDescriptor, 0, SEEK_END);
            if (fileSize < 0) {
                printf("Error closing file -> %s\n", file->d_name);
                goto mainReader;
            }
            printf("%s    %d\n", file->d_name, fileSize);

            if (close(fDescriptor) < 0) {
                printf("Error closing file -> %s\n", file->d_name);
                return -1;
            }


    }
    return 0;
}
