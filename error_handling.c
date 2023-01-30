#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error_handling.h"

void error(const char *error_message){
    fflush(stdout); 
	fprintf(stderr, "%s\n", error_message);
    exit(EXIT_FAILURE);
}