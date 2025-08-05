.global _sigterm

_sigterm:
    mov x1, #15
    mov x16, #37
    svc #0
    ret
