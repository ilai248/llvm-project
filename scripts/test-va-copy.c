#include <stdio.h>
#include <stdarg.h>

void test_fn(const char* s, ...) {
    va_list vl, vl2;
    va_start(vl, s);
    va_copy(vl2, vl);
    vfprintf(stdout, s, vl);
    vfprintf(stdout, s, vl2);
    va_end(vl);
}

int main() {
    test_fn("Foo %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8);
    printf("hi! %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
    test_fn("Foo %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8);
    printf("hi! %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
    test_fn("Foo %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8);
    printf("hi! %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
    test_fn("Foo %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8);
    printf("hi! %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
    test_fn("Foo %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8);
    printf("hi! %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
    test_fn("Foo %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8);
    printf("hi! %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
    return 0;
}
