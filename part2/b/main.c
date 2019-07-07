#include <stdio.h>
int main(int argc, char **argv) {
    char *p = 0;
    int top = 100;
    printf("&p    = 0x%lx\n", (unsigned long)&p);
    printf("&top  = 0x%lx\n", (unsigned long)&top);
    printf("&argc = 0x%lx\n", (unsigned long)&argc);
    printf("&argv = 0x%lx\n", (unsigned long)&argv);
}
