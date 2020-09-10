This Linux Shell in C can be run by compiling with 'make' and then running with ./ainux. 'history' has been implemented on top of the basic requirements.

Files:

Corresponding error messages will be displayed as well in case invalid arguments or a wrong number of arguments are provided upon the execution of a certain command (depending upon their working in terminal)

makefile - used so that we can compile all the files present

main.c - main file where we are calling all our functions to execute commands. Tokenizes inputs and seperates commands by semicolons

prompt.c - prints prompt of the shell and changes prompt accordingly if we change the present directory we are in

cd.c - allows us to change the directory that we are present in. Takes both absolute and relative paths

pwd.c - displays the directory we are present in. Displays relative paths in case the directory we are in is present inside the shell directory and absolute path in all other cases

echo.c - prints the argument given

ls command - allows us to display the files present in the current directory. Accepts relative and absolute paths. Accepts flags as well and prints hidden files and file permissions accordingly. Works for multiple directories as well and works in any order that the arguments are given in

fore.c - allows us to implement foreground processes

back.c - allows us to implement background processes and prints whenever the background process finishes executing

pinfo.c - prints process related info. Either prints info of the currently running process if not given a pid number or gives the info of any pid number. Accepts at max 1 pid number and gives error otherwise

history.c - keeps commands entered into shell into hist.txt file

historyprint.c - prints history of commands run in the shell. User can specify the number of commands to show uptil 20. Just running history without specifying the number of commands prints the last 10 commands entered. Specifying a number of commands higher than 20 just prints 20 commands

hist.txt - stores history of commands upto 20 commands