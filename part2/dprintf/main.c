#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;

    if (argc != 2){
        fprintf(stderr, "filename required\n");
        exit(1);
    }
    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        fprintf(stderr, "file descripter can't open\n");
        exit(1);
    }
    dprintf(fd, "HELLO %s!\n", argv[1]);
    close(fd);
    return 0;
}
