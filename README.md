# **HASH** -


## Features

- Using commands with semicolons between them
- Handles input/output redirections
- Piping of one command into other works
- background and foreground activities
-signal

- cd

- echo

- pwd

- ls

- history

- discover

- other system commands using execvp

- pinfo

- jobs

- fg

- bg

- sig

## Files

### **main.c**

clear display, show initial prompt and take input. it also catches signals.

### **cd.c**
duplicates the cd command. can take a relative/absolute path as its argument.

### **echo.c**
prints the argument followed by echo. handles tabs and extra spaces.

### **pwd.c**
prints the current working directory

### **ls.c**
implements the ls function of the linux terminal. handles flags and paths.

### **history.c**
prints the last 10 executed commands. previous 20 commands saved in history.txt

### **discover.c**
immitates the discover command as mentioned in the assignment
assumes argument to the discover command to be given without quotes

### **syscommands**
all other non user-defined commands are executed normally, using execvp. foreground and background processes

### **pinfo.c**
prints the process related info of the shell

### **jobs.c**
prints the background processes of the terminal

### **fg.c**
changes the respective background command to foreground command

### **bg.c**
changes the state of a stoped background process to running

### **tokenization**
assumes no space after entered semi colon

### **headers.h**
Contains all the required headers for all files

### **redirection**
if > < input and output sources are mentioned, code executes it as per the given command

### **pipe**
linux shell piping command is imitated
also handles redirections with piping

### **signal_handling**
ctrl Z
ctrl C
ctrl D