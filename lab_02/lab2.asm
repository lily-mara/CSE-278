        ;FILE "lab2.c"
        GLOBAL  year
        GLOBAL  year2
        SECTION .data
        ALIGN 4
        GLOBAL year:object
        ;.size  year, 4
        GLOBAL year2:object
        ;.size  year2, 4
year: 
        dd      2020
        SECTION         .rodata
        ALIGN 8
year2: 
        dd      2050
        SECTION         .rodata
        ALIGN 8
.LC0: 
        db      'Enter the year you were born: '
.LC1: 
        db      '%d'
        ALIGN 8
.LC2: 
        db      'In %d, you will be %d years old',10,''
        SECTION .text
        GLOBAL  main
        GLOBAL main:function
main: 
MISMATCH: "        pushq   %rbp"
        movq    rbp,rsp
MISMATCH: "        subq    $16, %rsp"
        mov     edi, .LC0
        mov     eax,0
        call    printf
MISMATCH: "        leaq    -4(%rbp), %rax"
        movq    rsi,rax
        mov     edi, .LC1
        mov     eax,0
        call    __isoc99_scanf
        mov     eax, [rbp-4]
        mov     edi,eax
        call    calc_age
        mov     edx,eax
        mov     eax, [year(%rip)]
        mov     esi,eax
        mov     edi, .LC2
        mov     eax,0
        call    printf
        mov     eax, [rbp-4]
        mov     edi,eax
        call    calc_age2
        mov     edx,eax
        mov     eax, [year2(%rip)]
        mov     esi,eax
        mov     edi, .LC2
        mov     eax,0
        call    printf
        leave
        ret
        GLOBAL  main:function (.-main)
        GLOBAL  calc_age
        GLOBAL calc_age:function
        GLOBAL  calc_age2
        GLOBAL calc_age2:function
calc_age: 
MISMATCH: "        pushq   %rbp"
        movq    rbp,rsp
        mov     [rbp-4],edi
        mov     eax, [year(%rip)]
        sub     eax, [rbp-4]
MISMATCH: "        popq    %rbp"
        ret
        GLOBAL  calc_age:function (.-calc_age)
        ;IDENT "GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
calc_age2: 
MISMATCH: "        pushq   %rbp"
        movq    rbp,rsp
        mov     [rbp-4],edi
        mov     eax, [year2(%rip)]
        sub     eax, [rbp-4]
MISMATCH: "        popq    %rbp"
        ret
        GLOBAL  calc_age2:function (.-calc_age2)
        ;IDENT "GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
MISMATCH: "        .section        .note.GNU-stack,"",@progbits"

