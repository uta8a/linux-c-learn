#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf;
    int fd, size, pos;

    buf = (char *) calloc(100, sizeof(char));
    fd = open("abc.txt", O_RDONLY);
    if (fd < 0) {
        perror("r1");
        exit(1);
    }
    size = read(fd, buf, 5);
    printf("read(%d, buf, 5)\n", fd);
    printf("%d bytes\n", size);
    buf[size] = '\0';
    printf("%s\n\n", buf);

    pos = lseek(fd, 2, SEEK_CUR);
    printf("lseek(%d, 2, SEEK_CUR) => %d\n", fd, pos);
    size = read(fd, buf, 5);
    printf("read(%d, buf, 5) => %d\n", fd, size);
    printf("%s\n\n", buf);

    pos = lseek(fd, 0, SEEK_SET);
    printf("lseek(%d, 0, SEEK_SET) => %d\n", fd, pos);
    size = read(fd, buf, 5);
    printf("read(%d, buf, 5) => %d\n", fd, size);
    buf[size] = '\0';
    printf("%s\n\n", buf);
    
    pos = lseek(fd, -10, SEEK_END);
    printf("lseek(%d, -10, SEEK_END) => %d\n", fd, pos);
    size = read(fd, buf, 5);
    printf("read(%d, buf, 5) => %d\n", fd, size);
    buf[size] = '\0';
    printf("%s\n", buf);
    
    return 0;
}
