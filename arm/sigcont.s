.global _sigcont

_sigcont:
    mov x1, #19
    mov x16, #37
    svc #0
    ret
