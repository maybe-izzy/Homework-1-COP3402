/*=============================================================================
| Assignment: HW 1 - Stack Machine
| Authors: Isabelle Montgomery and Christopher Colon Marquez
| Language: C
| Class: COP3402 (0001) - Systems Software - Spring 2023
| Instructor: Gary T. Leavens
| Due Date: 01/31/2023
|
| This program implements a word-addressable stack-based virtual machine.
| The virtual machine is passed an executable file as input and 
| its tracing is printed to standard output. Error messages are 
| sent to standard error output (stderr).
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "machine.h"

extern void usage(const char *cmdname);
extern void p_machine(char *filename); 

int main(int argc, char *argv[]){
    const char *cmdname = argv[0];
    --argc;

    if (argc == 1) {
	    if (argv[1][0] == '-') {
            //usage();
	    }
	    p_machine(argv[1]);
    } 
    else {
	    usage(cmdname);
    }
    return EXIT_SUCCESS;
}

// Prints a message to stderr
void usage(const char *cmdname){
    fprintf(stderr, "Usage: %s arg [arg] ...\n", cmdname);
}

// Gets instructions for VM, initializes
// a stack, and processes the instructions
// obtained from the file.
void p_machine(char *filename){
    get_instructions(filename); 
    stack_init(); 
    process_instructions(); 
}