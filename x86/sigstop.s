global sigstop

sigstop:
    mov rsi, 19
    mov rax, 62
    syscall
    ret
