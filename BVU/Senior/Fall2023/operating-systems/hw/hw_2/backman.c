#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#define BUFF_SIZE 256
char cwd[BUFF_SIZE];
char userInput[BUFF_SIZE];

char* cmd;
int argc;
char* argv[BUFF_SIZE];

void print(char* str) {
    int len = strlen(str);
    write(1, str, len);
}

void printPrompt() {
    print(cwd);
    print(" $ ");
}

void getInput() {
    char *ch = userInput;
    while( read(0, ch, 1) && *ch != '\n' )
        ch++;
    *ch = '\0';
}

void parseInput() {

    cmd = userInput;
    while(*cmd == ' ') cmd++;
    argv[0] = cmd;
    argc = 1;

    char* ch = cmd;
    while(*ch != ' ' && *ch != '\0') ch++;

    // Found end of input immediately; bail out
    if (*ch == '\0') {
        argv[argc] = NULL;
        return;
    } 

    // Null-terminate cmd then skip whitespace
    *ch = '\0';
    ch++;
    while(*ch == ' ') ch++;

    while(*ch != '\0') {
        // Add arg to arglist
        argv[argc] = ch;
        argc++;

        // Skip over arg characters
        while(*ch != ' ' && *ch != '\0') ch++;

        // Terminate if necessary
        if (*ch == ' ') {
            *ch = '\0';
            ch++;
        }

        // Skip any spaces present
        while(*ch == ' ') ch++;
    }

    argv[argc] = NULL;
}

void debugPrint(char* prefix, char* str) {
    print(prefix);
    print(": [");
    print(str);
    print("]\n");
}

void debugargs() {
    debugPrint("cmd", cmd);
    for(int i=0; i <= argc; i++) {
        if (argv[i] != NULL)
            debugPrint("arg", argv[i]);
        else
            debugPrint("arg", "(null)");
    }
}

int main() {

    print("[Backman Shell v2023]\n");
    getcwd(cwd, BUFF_SIZE);

    while(1) {
        printPrompt();
        getInput();
        parseInput();

        if (strcmp(cmd, "exit") == 0) {
            return 0;
        } else if (strcmp(cmd, "pwd") == 0) {
            print(cwd);
            print("\n");
        } else if (strcmp(cmd, "cd") == 0) {
            if (chdir(argv[1]) == 0)
                getcwd(cwd, BUFF_SIZE);
            else
                debugPrint("Error - Could not change to directory", strerror(errno));
        } else if (strcmp(cmd, "debugargs") == 0) {
            debugargs();
        } else {
            debugPrint("Error - Unknown command", cmd);
        }
    }

    return 0;
}

