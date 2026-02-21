
#include <stdlib.h>
//#include "utilities.h"
#include "stack.h"

// the stack's storage
static word stack[MAX_STACK_HEIGHT];

// index of NEXT free space
static address sp;

// first index of current AR
static address bp;

// Initialize the stack data structure
void stack_initialize(){
    sp = 0;
    bp = 0;
    for (address i = 0; i < MAX_STACK_HEIGHT; i++) {
	    stack[i] = 0;
    }
}

// Return the stack's num. of elements
// (SP value)
address stack_SP(){
    return sp; 
}

// Return the address of the base
// of the current AR (BP value)
address stack_BP(){
    return bp; 
}

// Is the stack empty?
bool stack_empty(){ 
    return sp == 0;                  
}

// Is the stack full?
bool stack_full() {
    return sp == MAX_STACK_HEIGHT-1;
}

// Requires: !stack_full()
// push a word on the stack
void stack_push(word val) {
    stack[sp++] = val;
}

// Requires: stack_size() + n
//                  < MAX_STACK_HEIGHT
// Increase the size of the stack by n
void stack_allocate(int n){
    int new_sp = sp + n;
    if (!legal_stack_index(new_sp)) {
	// report error
    }
    sp = new_sp;
}

// Requires: !stack_empty()
// pop the stack and return the top elem
word stack_pop() {
    if (stack_empty()) {
        // report error
        exit(2);
    } 
    else {
        return stack[--sp];  // or stack[sp--]; ???
    }
}

// return the top element without popping
word stack_top() {
    if (stack_empty()) {
        // report error
        exit(2);
    }
    else {
        return stack[sp-1];  // don't use -- here!
    }
}

void set_BP(int idx){
    bp = idx; 
}

// Is the given address legal?
bool legal_stack_index(address addr){
    return addr < MAX_STACK_HEIGHT;
}

// fetch the value from the given address
word stack_fetch(address addr){
    if (!legal_stack_index(addr)) {
	// report error
    }
    return stack[addr];
}

// assign val to the given address, addr, on the stack
void stack_assign(address addr, word val){
    if (!legal_stack_index(addr)) {
	// report error
    }
    stack[addr] = val;
}

void print_stack(){
    printf("stack: "); 
    for (int i = bp; i < stack_SP(); i++){
        printf("S[%d] : %d ", i,  stack[i]); 
    }
    printf("\n"); 
}

