#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "machine.h"

void p_machine(char *filename); 
void usage(const char *info); 

int main(int argc, char *argv[]){
    --argc;

    if (argc == 1) {
	    /* argument should be a file name, not an option */
	    if (argv[1][0] == '-') {
	        usage("(argument should be a file name)"); 
	    }
	    p_machine(argv[1]);
    } 
    else {
	    usage("");
    }
    return EXIT_SUCCESS;
}

// print a usage message to stderr
void usage(const char *info){
    fprintf(stderr, "usage: ./vm input_filename...\n");
    fprintf(stderr, "%s", info); 
}

void p_machine(char *filename){
    get_instructions(filename); 
    stack_init(); 
    process_instructions(); 
}