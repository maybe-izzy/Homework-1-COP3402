#include <stdlib.h>
#include "stack.h"
#include "error_handling.h"

static int stack[MAX_STACK_HEIGHT];
static int SP;
static int BP;

/* CITATION: code examples from class for stack utilities */

// Initializes stack values
void stack_init(){
    SP = 0;
    BP = 0;
    for (int i = 0; i < MAX_STACK_HEIGHT; i++) {
	    stack[i] = 0;
    }
}

// Returns the stack pointer
int stack_SP(){
    return SP; 
}

// Returns the base pointer
int stack_BP(){
    return BP; 
}

// Returns if the stack is empty or not
int stack_empty(){ 
    return SP == 0;                  
}

// Returns if the stack is full or not 
int stack_full() {
    return SP == MAX_STACK_HEIGHT-1;
}

// Push a given value to the stack 
void stack_push(int val) {
    if (stack_full()){
        error("Trying to push to a full stack!"); 
    }
    stack[SP++] = val;
}

// Increase the size of the stack by n elements 
void stack_allocate(int n){
    int new_sp = SP + n;
    if (!legal_stack_index(new_sp)) {
        error("Trying to expand stack memory outside of legal index!"); 
    }
    SP = new_sp;
}

// Pop the stack 
int stack_pop() {
    if (stack_empty()) {
        error("Trying to pop an empty stack!"); 
        return ERROR_CONSTANT; 
    } 
    else {
        return stack[--SP]; 
    }
}

// Return the top element without popping
int stack_top() {
    if (stack_empty()) {
        error("Trying to access element in empty stack!"); 
        return ERROR_CONSTANT; 
    }
    else{
        return stack[SP-1];  
    }
}

// Moves the BP (base pointer) to a given value
void set_BP(int val){
    if ((BP < 0) || (BP > SP)){ // Ensures compliance with invariant: 0 ≤ BP ∧ BP ≤ SP
        error("Trying to set BP to invalid value!"); 
    }
    else {
        BP = val; 
    }
}

// Determines whether the given stack address is legal
int legal_stack_index(int addr){
    return ((addr < MAX_STACK_HEIGHT) && (addr >= 0)); // Ensures compliance with invariant: SP ∧ 0 ≤ SP ∧ SP < MAX_STACK_HEIGHT
}

// Fetch the value from the given address
int stack_fetch(int addr){
    if (!legal_stack_index(addr)) {
        error("Trying to fetch from illegal stack address!"); 
    }
    return stack[addr];
}

// Place a value at a given address in the stack 
void stack_assign(int addr, int val){
    if (!legal_stack_index(addr)) {
        error("Trying to place value at illegal stack address!"); 
    }
    stack[addr] = val;
}

void print_stack(){
    printf("\nstack: "); 
    for (int i = BP; i < stack_SP(); i++){
        printf("S[%d]: %d ", i,  stack[i]); 
    }
}