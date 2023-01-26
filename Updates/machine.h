#ifndef MACHINE_H
#define MACHINE_H

#include "stack.h"
#include "machine_types.h"

typedef struct Instruction Instruction_T;

extern void print_instructions(); 
extern void get_instructions(char *filename); 
extern void process_instructions(); 

#endif