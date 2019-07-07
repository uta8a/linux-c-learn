#include <stdio.h>
int main() {
    int x=100;
    printf("0x%x\n", x);
    fprintf(stdout, "%d\n", x);
    fprintf(stderr, "error\n");
    return 0;
}

