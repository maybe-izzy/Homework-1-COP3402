#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>
#include <stdio.h>
#include "machine_types.h"

#define MAX_STACK_HEIGHT 2048

// Initialize the stack data structure
extern void stack_initialize();
extern address stack_SP(); 
extern address stack_BP(); 
extern bool stack_empty(); 
extern void set_BP(int idx);
extern bool stack_full(); 
extern void stack_push(word val); 
extern void stack_allocate(int n); 
extern word stack_pop(); 
extern word stack_top(); 
extern bool legal_stack_index(address addr); 
extern word stack_fetch(address addr); 
extern void stack_assign(address addr, word val); 
extern void print_stack(); 

#endif