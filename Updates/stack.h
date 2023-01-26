#ifndef STACK_H
#define STACK_H

typedef struct Stack *Stack_T;

extern Stack_T make_stack(void);
extern int is_empty(Stack_T s); 
extern int is_full(Stack_T s); 
extern void push(Stack_T s, int val);
extern int pop(Stack_T s);
extern int top(Stack_T s); // Added to have get the # at top. Used in PSI instruction.
extern int get_value(Stack_T s, int go_to_position); // Added to get # at position BP - o from the stack. Used in PRM and STO instructions.
extern void print_stack(Stack_T s); 

#endif