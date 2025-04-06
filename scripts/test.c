#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define GPR_SIZE sizeof(uint64_t)
#define NUM_GPRS 6
#define MAX_GPR_OFFSET (GPR_SIZE * (NUM_GPRS - 1))
#define OVERFLOW_AREA_PTR 16 // Location of overflow area relative to the frame of the function (rbp).

void my_func(FILE* file, va_list v) {
    uint32_t gp_offset = v->gp_offset;
    uint32_t fp_offset = v->fp_offset;
    void* overflow_arg_area = v->overflow_arg_area;
    void* reg_save_area = v->reg_save_area;

    int next_arg = 0;
    for (int i = 0; i < 10; i++) {
        // If we still have available GPRs, print them.
        if (gp_offset <= MAX_GPR_OFFSET) {
            next_arg = *(int*)(reg_save_area + gp_offset);
            gp_offset += GPR_SIZE;
        } else {
            // No available GPRs? Print overflow region.
            next_arg = *(int*)(overflow_arg_area);
            overflow_arg_area += GPR_SIZE;
        }
        fprintf(file, "%d\n", next_arg);
    }
}

FILE* fout = NULL;
void test1(int n, ...) {
    void* frame;
    uint64_t reg_save_area[NUM_GPRS];
    va_list ap;
    __asm__ volatile("mov %%rbp, %0" : "=r"(frame));

    // init reg_save_area. (skip first val cause its used for 'n').
    __asm__ volatile("mov %%rsi, %0" : "=r"(reg_save_area[1]));
    __asm__ volatile("mov %%rdx, %0" : "=r"(reg_save_area[2]));
    __asm__ volatile("mov %%rcx, %0" : "=r"(reg_save_area[3]));
    __asm__ volatile("mov %%r8, %0" : "=r"(reg_save_area[4]));
    __asm__ volatile("mov %%r9, %0" : "=r"(reg_save_area[5]));

    // Adjust for test1's frame: rsp + 8 (return addr) + space for n
    ap->gp_offset = GPR_SIZE; // Skip the first var ('n').
    ap->fp_offset = 0; // Not used.
    ap->reg_save_area = (void*)reg_save_area;
    ap->overflow_arg_area = frame + OVERFLOW_AREA_PTR;

    if (!fout) fout = stdout;
    my_func(fout, ap);
}

int main() {
    test1(10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    return 0;
}
