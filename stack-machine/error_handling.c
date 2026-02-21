#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error_handling.h"

void error(const char *error_message){
    fflush(stdout); // flush so output comes after what has happened already.
	fprintf(stderr, "%s\n", error_message); // Printing error to stdout.
    exit(EXIT_FAILURE); // Exit code to indicate program failure. 
}