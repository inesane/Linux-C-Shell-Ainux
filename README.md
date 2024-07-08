# Linux Shell in C

This Linux Shell in C can be run by compiling with `make` and then running with `./ainux`. 'history' has been implemented on top of the basic requirements.

## How to Run the Shell

1. Compile the project using the Makefile:
    ```bash
    make
    ```
2. Run the shell executable:
    ```bash
    ./ainux
    ```

## Files

### makefile
- Used to compile all the files present.

### main.c
- Main file where we call all our functions to execute commands.
- Tokenizes inputs and separates commands by semicolons.

### prompt.c
- Prints the prompt of the shell and changes the prompt accordingly if we change the present directory.

### cd.c
- Allows us to change the directory that we are present in.
- Takes both absolute and relative paths.

### pwd.c
- Displays the directory we are present in.
- Displays relative paths if the directory is inside the shell directory and absolute paths otherwise.

### echo.c
- Prints the argument given.

### ls.c
- Allows us to display the files present in the current directory.
- Accepts relative and absolute paths.
- Accepts flags to print hidden files and file permissions.
- Works for multiple directories in any order of arguments.

### fore.c
- Allows us to implement foreground processes.

### back.c
- Allows us to implement background processes and prints whenever the background process finishes executing.

### pinfo.c
- Prints process-related info.
- Prints info of the currently running process if no PID is given or gives the info of any specified PID.
- Accepts at most 1 PID and gives an error otherwise.

### history.c
- Keeps commands entered into the shell in `hist.txt`.

### historyprint.c
- Prints the history of commands run in the shell.
- The user can specify the number of commands to show up to 20.
- Just running `history` without specifying the number of commands prints the last 10 commands entered.
- Specifying a number higher than 20 just prints 20 commands.

### hist.txt
- Stores history of commands up to 20 commands.

### bg.c
- Changes the state of a stopped background job with a given job number to running.

### fg.c
- Brings a job with a given job number to the foreground and changes its state to running if it isn't already.

### env.c
- Implements `setenv` and `unsetenv` commands.

### jobs.c
- Prints all running background processes with associated information pertaining to each.

### kjob.c
- Sends a given signal to the job of a given job number.

### overkill.c
- Kills all the background processes.

### redirection.c
- Implements input/output redirection.

### sig.c
- Implements signal handling.

## Error Handling
Corresponding error messages will be displayed in case invalid arguments or an incorrect number of arguments are provided upon the execution of a certain command, depending on their functionality in the terminal.

---

Enjoy using the shell!
