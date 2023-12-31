#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>


#define MAX_ARR_SIZE 256

/* Global Variables */
char cwd[MAX_ARR_SIZE];
char input[MAX_ARR_SIZE];
char* argv[MAX_ARR_SIZE];
int argc = 0;

/* FILE IO */
char infile[MAX_ARR_SIZE];
char outfile[MAX_ARR_SIZE];
int in_flag;  // 0 for none, 1 for <
int out_flag; // 0 for none, 1 for >, 2 for >>


void print(char* str) {
    write(1, str, strlen(str));
}

void init_shell() {
    print("###############################\n");
    print("##                           ##\n");
    print("##  Welcome To Jrsh v0.3.9   ##\n");
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
    while ( read(0, ch, 1) && *ch != '\n') ch++;
    *ch = '\0';
}

/* Parses through input stream looking for IO redirects. If redirects are 
 * found, sets global IO flags and stores filenames. Since IO flags are set
 * and filenames saved, a null byte is inserted at the beginning of redirect
 * stream giving the illusion it was not there.
 */
void parse_redirect() {
    // reset in and out flags
    in_flag = 0;
    out_flag = 0;

    char* idxPtr = input;
    
    // find first redirct character
    while ((*idxPtr != '\0') && (*idxPtr != '<') && (*idxPtr != '>')) idxPtr++;

    // if no redirect char is found: return 
    if (*idxPtr == '\0')
        return;

    char* redirect_start = idxPtr; // point to beginning of redirect stream
    char* infile_start;
    char* outfile_start;
    char* infile_end;
    char* outfile_end;

    while (*idxPtr != '\0') {
        // handle input redirection
        if (*idxPtr == '<') {
            in_flag = 1;
            idxPtr++;

            // Jump all white space. Then point to the beginning of filename.
            // Then find the end of the file name. Finally, point to the end
            // of the filename.
            while (*idxPtr == ' ') idxPtr++; 
            infile_start = idxPtr;
            while (*idxPtr != ' ' && *idxPtr != '>' && *idxPtr != '\0') {
                idxPtr++;
            }
            infile_end = idxPtr;
        }
        // handle output redirection
        else if (*idxPtr == '>') {
            out_flag = 1;
            idxPtr++;

            // Check if next character is another '>'
            if (*idxPtr == '>') {
                out_flag = 2;
                idxPtr++;
            }

            // Jump all white space. Then point to the beginning of filename.
            // Then find the end of the file name. Finally, point to the end
            // of the filename.
            while (*idxPtr == ' ') idxPtr++;
            outfile_start = idxPtr;
            while (*idxPtr != ' ' && *idxPtr != '<' && *idxPtr != '\0') {
                idxPtr++;
            }
            outfile_end = idxPtr;
        }
        else {
            idxPtr++;
        }
    }

    // add null byte at the beginning of redirect stream 
    *redirect_start = '\0';
    
    // add null byte if IO flags and copy null terminated filename into 
    // infile and/or outfile globals
    if (in_flag) {
        *infile_end = '\0';
        strcpy(infile, infile_start);
    }
    if (out_flag) {
        *outfile_end = '\0';
        strcpy(outfile, outfile_start);
    }
}

void parse_input() {
    argc = 0; // reset argc
    char* idxPtr = input;
    int strFound = 0;

    while (*idxPtr != '\0') {
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
    argv[argc] = NULL;
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

void handle_IO_redirect() {
    // handle input flag
    if (in_flag) {
        close(0); // close stdin
        int in_fd;
        if ((in_fd = open(infile, O_RDONLY)) == -1) {
            print("Error: ");
            print(strerror(errno));
            print("\n");
        } 
    }

    // handle output flag
    if (out_flag) {
        close(1); // close stdout
        int out_fd; 
        if (out_flag == 1) {
            out_fd = open(outfile, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
        }
        else if (out_flag == 2) {
            out_fd = open(outfile, O_WRONLY|O_CREAT|O_APPEND, S_IRWXU);
        }

        if (out_fd == -1) {
            print("Error: ");
            print(strerror(errno));
            print("\n");
        } 
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
        int childPid;
        if ((childPid = fork()) == 0) {
            handle_IO_redirect();
            execvp(argv[0], argv);

            // if ecec returns then process must have failed so print 
            // errno and exit
            print("Error: ");
            print(strerror(errno));
            print("\n");
            exit(1);
        }
        else {
            // wait for child process to finish
            while (wait(0) != childPid);            
        }
    }
}


int main() {

    init_shell();

    while (1) {
        print_prompt();
        get_input();
        parse_redirect();
        parse_input();
        handle_input();
    }

    return 0;
}
