#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "machine_types.h"
#include "stack.h"

#define MAX_CODE_LENGTH 512
#define NUM_OPCODES 27 

static const char *mnemonics[NUM_OPCODES] =
    {"LIT", "RTN", "CAL", "POP", "PSI",
     "PRM", "STO", "INC", "JMP", "JPC",
     "CHO", "CHI", "HLT ", "NDB", "NEG",
     "ADD", "SUB", "MUL", "DIV", "MOD", 
     "EQL", "NEQ", "LSS", "LEQ", "GTR", 
     "GEQ", "PSP"
    };

struct Instruction{
    int op; 
    int m; 
};

Instruction_T instruction_array[MAX_CODE_LENGTH]; 
int INSTRUCTION_COUNT = 0; 
int PC = 0; 
int print_debug = 1;
int halt = 0; 

// Is the argument a legal op code for the machine?
static bool legal_op_code(int op)
{
    return 0 <= op && op < NUM_OPCODES;
}

// Requires: legal_op_code(op);
// Return the ASCII mnemonic for the op code given.
static const char *get_mnemonic(int op){
    if (!legal_op_code(op)) {
	    // Error handling 
        exit(2); 
    }
    return mnemonics[op - 1];
}

void print_instructions(){
    printf("%-5s %-5s %-5s", "Addr", "OP", "M"); 
    for (int i = 0; i < INSTRUCTION_COUNT; i++){
        printf("\n%-5d %-5s %-5d", i, get_mnemonic(instruction_array[i].op), instruction_array[i].m); 
    }
}

/* Processes program instructions from text file into an array of instructions */
void get_instructions(char *filename){
    FILE *fp = fopen(filename, "r"); 
    int i = 0; 
    int num_read; 
    int stop_reading = 0; 
    int op;
    int m;

    while(stop_reading != 1){
        num_read = fscanf(fp, "%d %d\n", &op, &m);
        if (!legal_op_code(op) || num_read < 2) {
	        stop_reading = 1;
        }
        else {
            instruction_array[i].op = op; 
            instruction_array[i].m = m; 
            i++; 
            INSTRUCTION_COUNT++; 
        }  
    }

    fclose(fp);      
}

void trace(){
    if (print_debug){
        printf("PC: %d BP: %d SP: %d\n", PC, stack_BP(), stack_SP());  
        print_stack(); 
    }
}

/* Execute a given instruction using the stack memory */
void execute_instruction(Instruction_T instruction){
    int op1; 
    int op2; 

    // Decode the instructions 
    if (instruction.op == 1){ // LIT
        stack_push(instruction.m);
    }
    else if (instruction.op == 2){ // RTN
	 
    }
    else if (instruction.op == 3){ // CAL
        int new_BP = stack_SP(); 
        int old_BP = stack_BP(); 

        set_BP(new_BP); 
        stack_push(old_BP);
        stack_push(PC); 
        PC = instruction.m; 
    }
    else if (instruction.op == 4){ // POP
        stack_pop(); 
    }
    else if (instruction.op == 5){ // PSI
        stack_pop();
        stack_push(stack_top()); 
    }
    else if (instruction.op == 6){ // PRM 

    }
    else if (instruction.op == 7){ // STO
        op1 = stack_pop(); // SP-1
        op2 = stack_pop(); // SP-2

        stack_assign((op1 + instruction.m), op2);
    }
    else if (instruction.op == 8){ // INC
        stack_allocate(instruction.m); 
    }
    else if (instruction.op == 9){ // JMP
        PC = stack_pop(); 
    }
    else if (instruction.op == 10){ // JPC
        op1 = stack_pop(); 
        if (op1 != 0){
            PC = instruction.m; 
        }
    }
    else if (instruction.op == 11){// CHO 
        putc(stack_pop(), stdout); 
    }
    else if (instruction.op == 13){ // HLT
        halt = 1; 
    }
    else if (instruction.op == 14){ // NDB
        print_debug = 0; 
    }
    else if (instruction.op == 15){
        stack_push(stack_pop() * -1); 
    }
    else if (instruction.op == 16){ // ADD
        op1 = stack_pop(); 
        op2 = stack_pop(); 
        stack_push(op2 + op1);
    }
    else if (instruction.op == 17){ // SUB
        op1 = stack_pop(); 
        op2 = stack_pop(); 
        stack_push(op1 - op2);
    }
    else if (instruction.op == 18){ // MUL
        stack_push(stack_pop() * stack_pop()); 
    }
    else if (instruction.op == 21){ // EQL
        stack_push(stack_pop() == stack_pop()); 
    }
    else if (instruction.op == 22){ // NEQ
        op1 = stack_pop(); 
        op2 = stack_pop(); 
        if (op1 == op2){
            stack_push(0); 
        }
        else {
            stack_push(1); 
        }
    }
    else if (instruction.op == 22){ // LSS
        op1 = stack_pop(); 
        op2 = stack_pop(); 
        
        stack_push(op1 < op2); 
    }
    else {
        // Probably like a halt condition or something idk 
    }
}

/* Handle instructions */
void process_instructions(){
    printf("\nTracing...\n"); 
    trace();
    for (int i = 0; i < INSTRUCTION_COUNT; i++){ 
        if (print_debug){
            printf("==> addr: %d     %s   %d    \n", PC, get_mnemonic(instruction_array[PC].op), instruction_array[PC].m); 
        }
        execute_instruction(instruction_array[PC++]); // Do some halt condition handling 
        trace(); 
        if (halt){
            exit(0); 
        }
    }
}
