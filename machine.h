#include "stack.h"

#ifndef MACHINE_H
#define MACHINE_H

typedef struct Instruction Instruction_T;

extern void print_memnonic(Instruction_T instruction); 
extern Instruction_T *get_instructions(char *filename); 
extern void process_instructions(Instruction_T *instruction_array, Stack_T stack); 
extern void execute_instruction(Instruction_T instruction, Stack_T stack); 

#endif