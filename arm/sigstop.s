.global _sigstop

_sigstop:
    mov x1, #17
    mov x16, #37
    svc #0
    ret
