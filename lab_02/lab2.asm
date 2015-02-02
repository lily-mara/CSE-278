        ;FILE "lab2.c"
        SECTION .text
        GLOBAL  main
        ALIGN 16, db 090h
        GLOBAL main:function
main:                                    ; @main
MISMATCH: "        .cfi_startproc"
; BB#0:
MISMATCH: "        pushq   %rbp"
.Ltmp2:
MISMATCH: "        .cfi_def_cfa_offset 16"
.Ltmp3:
MISMATCH: "        .cfi_offset %rbp, -16"
        movq    rbp,rsp
.Ltmp4:
MISMATCH: "        .cfi_def_cfa_register %rbp"
MISMATCH: "        subq    $32, %rsp"
MISMATCH: "        leaq    .L.str, %rdi"
        mov     al,0
MISMATCH: "        callq   printf"
MISMATCH: "        leaq    .L.str1, %rdi"
MISMATCH: "        leaq    -4(%rbp), %rsi"
        mov     [rbp-8],eax             ; 4-byte Spill
        mov     al,0
MISMATCH: "        callq   __isoc99_scanf"
        mov     esi, [year]
        mov     edi, [rbp-4]
        mov     [rbp-12],eax            ; 4-byte Spill
        mov     [rbp-16],esi            ; 4-byte Spill
MISMATCH: "        callq   calc_age"
MISMATCH: "        leaq    .L.str2, %rdi"
        mov     esi, [rbp-16]           ; 4-byte Reload
        mov     edx,eax
        mov     al,0
MISMATCH: "        callq   printf"
        mov     edx,0
        mov     [rbp-20],eax            ; 4-byte Spill
        mov     eax,edx
MISMATCH: "        addq    $32, %rsp"
MISMATCH: "        popq    %rbp"
        ret
.Ltmp5:
        GLOBAL  main:function (.Ltmp5-main)
MISMATCH: "        .cfi_endproc"

        GLOBAL  calc_age
        ALIGN 16, db 090h
        GLOBAL calc_age:function
calc_age:                                ; @calc_age
MISMATCH: "        .cfi_startproc"
; BB#0:
MISMATCH: "        pushq   %rbp"
.Ltmp8:
MISMATCH: "        .cfi_def_cfa_offset 16"
.Ltmp9:
MISMATCH: "        .cfi_offset %rbp, -16"
        movq    rbp,rsp
.Ltmp10:
MISMATCH: "        .cfi_def_cfa_register %rbp"
        mov     [rbp-4],edi
        mov     edi, [year]
        sub     edi, [rbp-4]
        mov     eax,edi
MISMATCH: "        popq    %rbp"
        ret
.Ltmp11:
        GLOBAL  calc_age:function (.Ltmp11-calc_age)
MISMATCH: "        .cfi_endproc"

        GLOBAL year:object              ; @year
        SECTION .data
        GLOBAL  year
        ALIGN 4
year:
        dd      2020                    ; 0x7e4
        ;.size  year, 4

        GLOBAL .L.str:object            ; @.str
MISMATCH: "        .section        .rodata.str1.1,"aMS",@progbits,1"
.L.str:
        db      'Enter the year you were born: ', 0
        ;.size  .L.str, 31

        GLOBAL .L.str1:object           ; @.str1
.L.str1:
        db      '%d', 0
        ;.size  .L.str1, 3

        GLOBAL .L.str2:object           ; @.str2
.L.str2:
        db      'In %d, you will be %d years old\n', 0
        ;.size  .L.str2, 33


        ;IDENT "Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"
MISMATCH: "        .section        ".note.GNU-stack","",@progbits"

