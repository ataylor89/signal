global sigterm

sigterm:
    mov rsi, 15
    mov rax, 62
    syscall
    ret
