#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* Not used on this assignment but useful for next */
//#include <stdio.h>
//#include <fcntl.h>
//#include <sys/wait.h>

#define MAX_ARR_SIZE 256

/* Global Variables */
char cwd[MAX_ARR_SIZE];
char input[MAX_ARR_SIZE];
char* argv[MAX_ARR_SIZE];
int argc = 0;

void print(char* str) {
    write(1, str, strlen(str));
}

void init_shell() {
    print("###############################\n");
    print("##                           ##\n");
    print("##  Welcome To Jrsh v0.1.13  ##\n");
    print("##                           ##\n");
    print("###############################\n\n\n");
    getcwd(cwd, MAX_ARR_SIZE);
}

void print_prompt() {
    print(cwd);
    print(" $ ");
}

/* assumes input is not going to be more than 256 chars */
void get_input() {
    char* ch = input;
    while (1) {
        read(0, ch, 1);
        if (*ch == '\n') 
            break;
        ch++;
    }
}

void parse_input() {
    argc = 0; // reset argc
    char* idxPtr = input;
    int strFound = 0; // bool

    while (*idxPtr != '\n') {
        // At beginning of argument, so set strFound flag and point
        // argv[argc] to beginning of argument and increment argc
        if (!strFound && (*idxPtr != ' ')) {
            strFound = 1;
            argv[argc++] = idxPtr;
        }

        // First space so insert a null byte and unset strFound flag
        else if (strFound && (*idxPtr == ' ')) {
            *idxPtr = '\0';
            strFound = 0;
        }

        idxPtr++; // advance index pointer
    }

    *idxPtr = '\0'; // set \n to \0
}

void debugargs() {
    print("cmd: [");
    print(argv[0]);
    print("]\n");

    for (int i=0; i<argc; i++) {
        print("arg: [");
        print(argv[i]);
        print("]\n");
    }

    print("arg: [(null)]\n");
    return;
}

void cd(char* path) {
    int i = chdir(path);
    if (i == 0) {
        getcwd(cwd, MAX_ARR_SIZE);
    }
    else {
        print("Error: ");
        print(strerror(errno));
        print("\n");
    }
}

void handle_input() {
    if (*input == '\0')
        return;

    else if (strcmp(argv[0], "debugargs") == 0)
        debugargs();

    else if (strcmp(argv[0], "exit") == 0) {
        if (argc == 1) {
            print("Exiting Jrsh now...\n");
            exit(0);
        }
        else {
            print(argv[0]);
            print(": does not take any arguments\n");
        }
    }
    else if (strcmp(argv[0], "cd") == 0) {
        if (argc == 2)
            cd(argv[1]);
        else {
            print("Usage: ");
            print(argv[0]);
            print(" PATH_TO_DIR\n");
        }
    }
    else if (strcmp(argv[0], "pwd") == 0) {
        if (argc == 1) {
            print(cwd);
            print("\n");
        }
        else {
            print(argv[0]);
            print(": does not take any arguments\n");
        }
    }
    else {
        print(argv[0]);
        print(": command not found\n");
    }
}


int main() {

    init_shell();

    while (1) {
        print_prompt();
        get_input();
        parse_input();
        handle_input();
    }

    return 0;
}
