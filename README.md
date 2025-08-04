# signal

## Introduction

This repository gives us a peaceful way of terminating a program on Amazon Linux 2023, the default machine image on AWS cloud.

I log into my EC2 instance with the command:

    % ssh -i ~/myserver.pem ec2-user@<public-ipv4-address>
    [ec2-user@ip-ww-xx-yy-zz ~]$

Now I run my homepage application, which is a website written in Python.

    [ec2-user@ip-ww-xx-yy-zz ~]$ sudo su
    [root@ip-ww-xx-yy-zz ec2-user]# cd homepage
    [root@ip-ww-xx-yy-zz homepage]# python app.py &
    [1] 31505
    [root@ip-ww-xx-yy-zz homepage]#  * Serving Flask app 'app'
     * Debug mode: off
    WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
     * Running on all addresses (0.0.0.0)
     * Running on http://127.0.0.1:80
     * Running on http://ww.xx.yy.zz:80
    Press CTRL+C to quit

The command "python app.py &" runs my web server in the background.

I press the return key to get back to the command prompt.

Then I cd into my signal folder.

    [root@ip-ww-xx-yy-zz homepage]# cd ../signal
    [root@ip-ww-xx-yy-zz signal]# ls
    sigint.c  sigint.s

Now it's time to compile the source files.

But first, we have to install gcc and nasm.

    [root@ip-ww-xx-yy-zz signal]# yum install gcc -y
    <gcc installation finished>
    [root@ip-ww-xx-yy-zz signal]# yum install nasm -y
    <nasm installation finished>

gcc is a C compiler, and nasm is an assembly compiler (also called an assembler).

Now we can compile our C file and our assembly file.

We compile the assembly file first, since the C file depends on the assembly file.

    [root@ip-ww-xx-yy-zz signal]# nasm -f elf64 sigint.s -o sigint.o
    [root@ip-ww-xx-yy-zz signal]# ls
    sigint.c  sigint.o  sigint.s
    [root@ip-172-31-93-134 signal]# gcc sigint.c sigint.o -o sigint
    [root@ip-172-31-93-134 signal]# ls
    sigint  sigint.c  sigint.o  sigint.s

We have finished compiling our C and assembly files.

We created an executable called "sigint".

Let's quickly check the status of our process.

    [root@ip-172-31-93-134 sigint]# ps aux | grep python
    root       31505  --  -- -- -- pts/5    S    03:18   0:00 /usr/bin/python3 app.py
    root       31590  --  -- -- -- pts/5    S+   03:21   0:00 grep --color=auto python
    [root@ip-172-31-93-134 sigint]# jobs
    [1]+  Running                 /usr/bin/python3 app.py &

You can see that our Python application is currently running.

It has a process ID (pid) of 31505.

Now we are going to use our sigint program to sent an interrupt signal to our Python application.

    [root@ip-172-31-93-134 signal]# ./sigint 31505
    Sent a SIGINT signal to pid 31505
    [1]+  Terminated              /usr/bin/python3 app.py  (wd: /home/ec2-user/homepage)
    (wd now: /home/ec2-user/signal)

It worked.

Our sigint signal worked.

Let's use the ps and jobs commands to confirm that it worked.

    [root@ip-172-31-93-134 signal]# ps aux | grep python
    root       31770  --  -- --  -- pts/5    S+   03:27   0:00 grep --color=auto python

You can see that it's missing from the ps aux output.

    [root@ip-172-31-93-134 signal]# jobs
    [root@ip-172-31-93-134 signal]#

We also see that there are currently no jobs running.

So we were able to confirm that our sigint program worked.

The sigint program accepts an integer argument. The integer argument is the pid of the process we want to interrupt.

In order to write the sigint program, we used a combination of C and assembly.

We used C to parse a process ID from our command line arguments.

We used x86-64 assembly to make a system call that terminates a process with a given process ID.

Register rax contains the system call number, which corresponds to a specific kernel function.

In this case, the system call number is 62.

Register rdi contains the first argument to the system call.

The argument to our sigint function actually gets stored in register rdi, by the caller, so we don't have to update register rdi.

In other words, the process ID that we pass to sigint gets stored in register rdi, so we don't have to update register rdi.

Register rsi contains the second argument to the system call, the value 15, which stands for SIGTERM.

After registers rax, rdi, and rsi have the correct values, we can make our syscall.

To be clear, rax has the value 62, rdi has the process ID, and rsi has the value 15.

Then we return from our sigint function.

The ret instruction pops the return address from the stack and loads it into the instruction pointer register.

The return address corresponds to the instruction immediately following the sigint call.

In other words, the return address corresponds to `printf("Sent a SIGINT signal to pid %d\n", pid);` in sigint.c.

Well, that's it for an introduction.

Just remember...

We used C to parse a process ID from our command line arguments (it would take a long time to do this in assembly).

We used x86 assembly to terminate a process with a given process ID.

So this project contains a combination of C and assembly.

It serves as a nice example of how we can combine these two languages.

The C language saves us time parsing command line arguments... and the assembly language lets us make a system call by its call number.
