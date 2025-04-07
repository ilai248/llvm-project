.intel_syntax noprefix

.section .text
.globl main
.type main, @function
main:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 48

    // *******                             Get Numbers                      **********
    mov     dword ptr [rbp - 4], 0      // align stack to 16-bit
    lea     rdi, [rip + .get10]         // access get10 with absolute (rather than relative) access.
    lea     rsi, [rbp - 0x8]            // rsi = &a
    lea     rdx, [rbp - 0xC]            // rdx = &b
    lea     rcx, [rbp - 0x10]           // rcx = &c
    lea     r8,  [rbp - 0x14]           // r8  = &d
    lea     r9,  [rbp - 0x18]           // r9  = &e

    push rax                            // extra push for alignment.

    lea     rax, [rbp - 0x2C]           // push &j
    push    rax                         // push &j

    lea     rax, [rbp - 0x28]           // push &i
    push    rax                         // push &i

    lea     rax, [rbp - 0x24]           // push &h
	push    rax                         // push &h

    lea     rax, [rbp - 0x20]           // push &g
    push    rax                         // push &g

    lea     rax, [rbp - 0x1C]           // push &f
    push    rax                         // push &f

    mov     rax, 0                      // no floating point/SIMD arguments. (TODO: Maybe need to set entire rax to 0?)
    call    scanf@PLT
    add rsp, 6*8                        // clean up stack

    // *******                             Sort Numbers                     **********
    lea rdi, [rbp - 0x2C]               // arr start
    mov rsi, 10                         // element count - 10
    mov rdx, 4                          // element size - 4
    lea rcx, comp[rip]                  // comp function
    call qsort@PLT

    // *******                             Print Numbers                    **********

    // zero out registers
    xor rsi, rsi
    xor rdx, rdx
    xor rcx, rcx
    xor r8, r8
    xor r9, r9
    xor rax, rax

    // Load register args.
    lea     rdi, .print10[rip]          // rdi = address of format string
    mov     esi, dword ptr [rbp - 8]    // rsi = a
    mov     edx, dword ptr [rbp - 12]   // rdx = b
    mov     ecx, dword ptr [rbp - 16]   // rcx = c
    mov     r8d, dword ptr [rbp - 20]   // r8 = d
    mov     r9d, dword ptr [rbp - 24]   // r9 = e

    push rax                            // extra push for alignment.

    mov     eax, [rbp - 0x2C]           // push j
    push    rax                         // push j

    mov     eax, [rbp - 0x28]           // push i
    push    rax                         // push i

    mov     eax, [rbp - 0x24]           // push h
	push    rax                         // push h

    mov     eax, [rbp - 0x20]           // push g
    push    rax                         // push g

    mov     eax, [rbp - 0x1C]           // push f
    push    rax                         // push f

    mov     rax, 0                      // no floating point/SIMD arguments.
    call    printf@PLT
    add rsp, 6*8                        // clean up stack

    mov rdi, 0
    call exit@PLT

// lambda a, b -> return *b - *a (returns positive value if right is higher).
comp:
    mov rcx, [rdi]   // First argument
    mov rax, [rsi]
    sub rax, rcx     // Second argument
    ret

.section .data
.get10:
	.asciz  "%d %d %d %d %d %d %d %d %d %d"

.print10:
	.asciz  "After Sort: %d %d %d %d %d %d %d %d %d %d\n"
