    .arch msp430g2553
    .p2align 1, 0
    .text

    ;;Routines to access and modify the Status Register (SR)

    .global set_sr
set_sr:
    nop                  ;No operation (for timing or debugging)
    mov     r12, r2      ;Set SR (r2) to the value in r12
    nop
    ret                  ;Return from subroutine

    .global get_sr
get_sr:
    mov     r2, r12      ;Move SR (r2) into r12
    ret

    .global or_sr
or_sr:
    nop
    bis     r12, r2      ;Bitwise OR r12 with SR (r2)
    nop
    ret

    .global and_sr
and_sr:
    nop
    and     r12, r2      ;Bitwise AND r12 with SR (r2)
    nop
    ret
