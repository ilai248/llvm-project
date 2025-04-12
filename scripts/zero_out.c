#include <stdio.h>

void arg6(int a, int b, int c, int d, int e, int f) { }

void (*arg6_)(int, int, int, int, int, int) = arg6;

int main() {
    arg6_(1, 2, 3, 4, 5, 6);
    printf("%08x %08x %08x %08x %08x\n");
    arg6_(1, 2, 3, 4, 5, 6);
}

