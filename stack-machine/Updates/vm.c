#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "machine_types.h"
#include "machine.h"

extern void usage(const char *cmdname);
extern void p_machine(char *filename); 

    //Stack_T stack = make_stack();

int main(int argc, char *argv[]){
    const char *cmdname = argv[0];
    --argc;

    if (argc == 1) {
	    /* argument should be a file name, not an option */
	    if (argv[1][0] == '-') {
	        //usage(); print out how to invoke the machine
	    }
	    p_machine(argv[1]);
    } 
    else {
	    usage(cmdname);
    }
    
    return EXIT_SUCCESS;
}

// print a usage message to stderr
void usage(const char *cmdname){
    fprintf(stderr, "Usage: %s arg [arg] ...\n", cmdname);
}

void p_machine(char *filename){
    get_instructions(filename); 
    print_instructions(); 
    stack_initialize(); 
    process_instructions(); 
}