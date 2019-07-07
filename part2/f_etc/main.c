#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFFER_SIZE 8192
int main(int argc, char **argv) {
    int size;
    FILE *stream;
    char buf[BUFFER_SIZE];

    if (argc != 2) {
        fprintf(stderr, "please write filename\n");
        exit(1);
    }
    stream = fopen(argv[1], "r");

    if (stream == NULL) {
        fprintf(stderr, "%s can't open\n", argv[1]);
        exit(1);
    }
    size = 1;
    while(size > 0) {
        size = fread(buf, 1, BUFFER_SIZE, stream);
        if (size > 0) {
            fwrite(buf, 1, size, stdout);
        }
    }
    fclose(stream);
    return 0;
}
