#ifndef STACK_H
#define STACK_H

typedef struct Stack *Stack_T;

extern Stack_T make_stack(void);
extern int is_empty(Stack_T s); 
extern int is_full(Stack_T s); 
extern void push(Stack_T s, int val);
extern int pop(Stack_T s);
extern void print_stack(Stack_T s); 

#endif