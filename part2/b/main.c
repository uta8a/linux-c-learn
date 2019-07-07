#include <stdio.h>
int main(int argc, char **argv) {
    char *p = 0;
    int top = 100;
    int last = 10000000;
    int llast = 100000;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int b[10] = {1,2,3,4,5,6,7,8,9,10};
    printf("&p    = %p\n", &p);
    printf("&top  = %p\n", &top);
    printf("&argc = %p\n", &argc);
    printf("&argv = %p\n", &argv);
    printf("&last = %p\n", &last);
    printf("&llast= %p\n", &llast);
    printf("&a    = %p\n", &a);
    printf("&b    = %p\n", &b);
}
