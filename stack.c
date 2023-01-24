#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

#define MAX_STACK_HEIGHT 2048

struct Stack{
    int array[MAX_STACK_HEIGHT]; 
    int top; 
}; 

Stack_T make_stack(void){
    Stack_T s = (Stack_T) malloc(sizeof(struct Stack)); 
    s->top = -1; 
    return s; 
}

int is_empty(Stack_T s){
    if (s->top == -1){
        return 1;  
    }
    else {
        return 0; 
    }
}

int is_full(Stack_T s){
    if (s->top >= MAX_STACK_HEIGHT){
        return 1;  
    }
    else {
        return 0; // this should return a halt condition flag
    }
}


int pop(Stack_T s){
    if (s->top != -1){
        return (s->array[s->top--]); 
    }
    else {
        // handle this halt condition 
        return -999;  
    }
}

void push(Stack_T s, int val){
    if (s->top < MAX_STACK_HEIGHT){
        s->array[++(s->top)] = val; 
    }
    else {
        // handle this halt contition 
    }
}

void print_stack(Stack_T s){
    printf("stack: "); 
    for (int i = 0; i < (s->top + 1); i++){
        printf("S[%d] : %d ", i,  s->array[i]); 
    }
    printf("\n"); 
}