#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

// Custom va_list implementation for testing (this assumes your system is patched to have the new field)
typedef struct {
    uintptr_t overflow_arg_area_size;
    void *gp_offset;
    void *fp_offset;
    void *overflow_arg_area;
    void *reg_save_area;
} my_va_list;

// Your custom variadic function
void test_variadic(const char *fmt, ...) {
    int result = 0;
    int val = 42;

    asm volatile (
        "movl $1, %%eax\n\t"
        "addl %1, %%eax\n\t"
        "subl $10, %%eax\n\t"
        "xorl %%eax, %%eax\n\t"
        "movl %1, %%eax\n\t"
        "imull $3, %%eax\n\t"
        "addl $7, %%eax\n\t"
        "subl $5, %%eax\n\t"
        "xorl $0x55AA55AA, %%eax\n\t"
        "notl %%eax\n\t"
        "roll $3, %%eax\n\t"
        "rorl $2, %%eax\n\t"
        "addl %%eax, %%eax\n\t"
        "movl %%eax, %0\n\t"
        : "=r" (result)          // output
        : "r" (val)              // input
        : "%eax"                 // clobbered
    );
    
    va_list ap;
    va_start(ap, fmt);
    my_va_list* my_ap = (my_va_list*)&ap;
    printf("Got      overflow_arg_area_size: 0x%lx\n", my_ap->overflow_arg_area_size);
    va_end(ap);
}

int main() {
    test_variadic("test", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    return 0;
}
