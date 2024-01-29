.globl memzero
memzero:
    str xzr, [X0], #8
    subs x1, x1, #8
    b.gt memzero
    ret 