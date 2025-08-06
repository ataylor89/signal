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

## Adding the programs to our shell path

First I open Terminal.

Then I can figure out which shell I am using by typing the command

    % echo $SHELL
    /bin/zsh

It turns out I am using zsh.

If you are using zsh, you can edit the file ~/.zshrc.

The z in .zshrc stands for Z shell, the name of the shell.

The rc in .zshrc stands for "run commands" or "run configurations".

The commands (configurations) in ~/.zshrc get run when the Z shell is started.

If you are using bash, which is also common, you can edit the file ~/.bashrc.

The rc in ~/.bashrc once again stands for "run commands" or "run configurations".

The commands in ~/.bashrc are run every time the bash process is started.

In summary, the ~/.zshrc and ~/.bashrc files are configuration files which contain commands that get run every time zsh or bash is run.

You may have heard of files like ~/.zprofile and ~/.bash_profile.

I think that ~/.zprofile and ~/.bash_profile are executed by login shells, whereas ~/.zshrc and ~/.bashrc are executed by non-login shells.

So there's actually a subtle point to be made.

The files ~/.zshrc and ~/.bashrc are executed every time a non-login shell is started.

The files ~/.zprofile and ~/.bash_profile are executed every time a login shell is started.

I'm spending a long time on this subject, but I wanted to make this distinction clear.

Now, let's return to the topic of ~/.zshrc.

We can edit ~/.zshrc to configure our PATH environment variable so that it includes the directory for sigterm, sigstop, and sigcont.

Let's do that now.

    # First let's examine the contents of our ~/.zshrc file
    % cat ~/.zshrc
    export SYSLIBROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk

    # We already have one command in our ~/.zshrc file, where we export an environment variable
    # Let's add another command to our ~/.zshrc file, where we add to our PATH variable
    % cat << EOF >> ~/.zshrc
    heredoc> export PATH="\$PATH:/Users/username/Github/signal/arm"
    heredoc> EOF

    # We just appended a line to our ~/.zshrc file. Let's see what ~/.zshrc looks like now.
    % cat ~/.zshrc
    export SYSLIBROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
    export PATH="$PATH:/Users/username/Github/signal/arm"

    # Perfect! The ~/.zshrc file looks exactly the way we want it to look.
    # It's worth mentioning that I used a heredoc to add a line of code to ~/.zshrc.
    # The heredoc treats everything before the second EOF delimiter as a block of text.
    # We can also add a line of code to ~/.zshrc using the echo command.
    # Let's show how we can do it with the echo command.
    # We'll pretend that the ~/.zshrc file looks the way it did before we added to it
    % cat ~/.zshrc
    export SYSLIBROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk

    # Now we will add a line of code that updates the PATH variable using the echo command
    % echo 'export PATH="$PATH:/Users/username/Github/signal/arm"' >> ~/.zshrc

    # Let's view the contents of ~/.zshrc to see if it looks the way it should
    % cat ~/.zshrc
    export SYSLIBROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
    export PATH="$PATH:/Users/username/Github/signal/arm"

## Testing our sigstop, sigcont, and sigterm programs

The text below was originally part of the previous section, but I moved it to a new section.

    # Awesome. We were able to add a line of code to ~/.zshrc using the echo command.
    # So we demonstrated two ways of adding to the ~/.zshrc file.
    # We can also edit the ~/.zshrc file using vi.
    # This gives us a total of three ways of updating the ~/.zshrc file.
    # We can really use any text editor to update the ~/.zshrc file.
    # We can also use the cat and echo commands to update the ~/.zshrc file.
    # Now that our ~/.zshrc file is updated, we can restart Terminal, or open a new tab in Terminal.
    # The ~/.zshrc file will get run because we are starting a new shell.
    # The directory for our sigterm, sigstop, and sigcont programs should be included in the PATH variable.
    # So we should be able to run our sigterm, sigstop, and sigcont programs without specifying the full path.
    # Let's start our Python web server (homepage) so that we can experiment with our signaling programs.
    % jobs
    % python ~/Github/homepage/app.py &
    [1] 19582
    username@hostname ~ %  * Serving Flask app 'app'
     * Debug mode: off
    WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
     * Running on all addresses (0.0.0.0)
     * Running on http://127.0.0.1:80
     * Running on http://ww.xx.yy.zz:80
    Press CTRL+C to quit

    # Our Python website is now running on localhost
    # Let's send some signals to this process (pid 19582) using our signaling programs
    # First I will press the return key to get back to the command prompt
    # Then I will confirm that the process is running by running the jobs command
    % jobs
    [1]  + running    python3 ~/Github/homepage/app.py

    # We confirmed the process is running
    # Now let's send some signals
    % sigstop 19582
    Sent a SIGSTOP signal to pid 19582.
    [1]  + suspended (signal)  python3 ~/Github/homepage/app.py

    # Let's run the jobs command again to see the status of the process
    % jobs
    [1]  + suspended (signal)  python3 ~/Github/homepage/app.py

    # The process is suspended. Let's restart it using the sigcont program.
    % sigcont 19582
    Sent a SIGCONT signal to pid 19582.
    % jobs
    [1]  + running    python3 ~/Github/homepage/app.py

    # The Python process is running once again. We were able to restart it using the sigcont program.
    # Now let's terminate the Python process using the sigterm program.
    % sigterm 19582
    Sent a SIGTERM signal to pid 19582.
    %
    [1]  + terminated  python3 ~/Github/homepage/app.py
    % jobs
    %

    # You can see that the Python process, our web server, got terminated
    # So we were able to stop, resume, and terminate the Python application using our sigstop, sigcont, and sigterm programs
    # It worked like a charm
    # They worked like a charm
    # And we did not have to specify the full path of our programs, since the directory for these programs is already in the PATH variable
    # If zsh and bash are not given the full path for a program, then it tries out the directories included in the PATH variable until it finds one of them that works, or until it runs out of directories
    # So we can run our sigstop, sigcont, and sigterm programs from any directory, since their directory is included in the PATH variable
    # This is convenient and it saves us time
    # We don't have to type out a full path... we don't have to cd into the signal/arm directory... we can just use the program names
    # Now, it's time to wrap things up
    # We finished testing our sigstop, sigcont, and sigterm programs
    # As we said before, they worked like a charm
    # I think that's all for now
    # Today is Wednesday, August 6, 2025
    # I know this document is a little long but I think I will just keep it the way it is
    # I wanted the document to be clear and comprehensive
    # There's really a balance between concise and comprehensive
    # Is every word in this document necessary? Is every line of text necessary?
    # Maybe it is... maybe it is
    # Thanks for reading
    # Buenas tardes
    # Estoy mirando la tele y escuchando a la musica
    # Quizas voy a mirar una pelicula
    # Que pelicula debo mirar?
    # Necesito decidir...
