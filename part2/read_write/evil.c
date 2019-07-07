#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    char *buf;
    int fd, size;

    buf = (char *) calloc(100, sizeof(char));

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("file can't open");
        exit(1);
    }

    size = read(fd, buf, 99);
    printf("fd: %d sz: %d\n", fd, size);
    buf[size] = '\0';
    buf[size+1] = 'a';
    printf("%s\n", buf);

    close(fd);
    free(buf);

    return 0;
}
