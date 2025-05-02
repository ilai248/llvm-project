#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

void test_variadic(const char *fmt, ...);
int main() {
    test_variadic("test", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    return 0;
}

// Your custom variadic function
void test_variadic(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    for (int i = 0; i < 20; i++) {
        int arg = va_arg(ap, int);
        //printf("Argument %d: %d\n", i, arg);
    }
    va_end(ap);
}
