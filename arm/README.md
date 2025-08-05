# signal

## Compiling the C files and the assembly files

I have a MacBook with an Apple M1 chip.

The Apple M1 chip has an arm64 architecture.

I'm actually running macOS Sequoia 15.6. I updated my operating system last night.

The instructions for compiling the C and assembly files on an arm64 MacBook are included below.

    # First navigate to the directory containing the source files
    % cd ~/Github/signal/arm

    # Let's print a listing of all the files in the directory
    % ls
    sigcont.c	sigcont.s	sigstop.c	sigstop.s	sigterm.c	sigterm.s

    # Now we  will use the as assembler to compile the assembly files into object files
    % as sigterm.s -o sigterm.o
    % as sigstop.s -o sigstop.o
    % as sigcont.s -o sigcont.o

    # Let's print a listing of all the files in the directory
    % ls
    sigcont.c	sigcont.s	sigstop.o	sigterm.c	sigterm.s
    sigcont.o	sigstop.c	sigstop.s	sigterm.o

    # Now we will use the gcc compiler to compile the C files and link the object files into an executable
    % gcc sigterm.c sigterm.o -o sigterm
    % gcc sigstop.c sigstop.o -o sigstop
    % gcc sigcont.c sigcont.o -o sigcont

    # Let's print a listing of all the files in the directory
    % ls
    sigcont		sigcont.o	sigstop		sigstop.o	sigterm		sigterm.o
    sigcont.c	sigcont.s	sigstop.c	sigstop.s	sigterm.c	sigterm.s

    # We have finished compiling the source files and linking the object files into executables
    # In the next section we will add the executables to our shell path, so that we can run the programs from any directory
