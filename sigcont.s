global sigcont

sigcont:
    mov rsi, 18
    mov rax, 62
    syscall
    ret
