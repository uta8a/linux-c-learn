#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192

int main(int argc, char **argv) {
    char buf[BUFFER_SIZE];
    int size;
    int fd;

    if (argc != 2){
        fprintf(stderr, "file name required\n");
        exit(1);
    }

    fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "%s can't open\n", argv[1]);
        exit(1);
    }
    size = read(0, buf, BUFFER_SIZE); // 0 is stdin
    while(size > 1) {
        write(fd,buf,size);
        size = read(0, buf, BUFFER_SIZE);
    }
    close(fd);
    return 0;
}
