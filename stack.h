#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_STACK_HEIGHT 2048

extern void stack_init();
extern int stack_SP(); 
extern int stack_BP(); 
extern int stack_empty(); 
extern void set_BP(int val);
extern int stack_full(); 
extern void stack_push(int val); 
extern void stack_allocate(int n); 
extern int stack_pop(); 
extern int stack_top(); 
extern int legal_stack_index(int addr); 
extern int stack_fetch(int addr); 
extern void stack_assign(int addr, int val); 
extern void print_stack(); 

#endif