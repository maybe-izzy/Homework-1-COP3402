#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "stack.h"
#include "error_handling.h"

#define MAX_CODE_LENGTH 512
#define NUM_OPCODES 27 

// Stores all mnemonic.
static const char *mnemonics[NUM_OPCODES] =
    {"LIT", "RTN", "CAL", "POP", "PSI",
     "PRM", "STO", "INC", "JMP", "JPC",
     "CHO", "CHI", "HLT ", "NDB", "NEG",
     "ADD", "SUB", "MUL", "DIV", "MOD", 
     "EQL", "NEQ", "LSS", "LEQ", "GTR", 
     "GEQ", "PSP"
    };

// Strucure for instructions.
struct Instruction{
    int op; 
    int m; 
};

// Array used to store all instructions.
Instruction_T instruction_array[MAX_CODE_LENGTH]; 
int PC = 0; 
int debug_info = 1;
int halt = 0; 

// Checks if current opcode is legal.
int legal_op_code(int op){
    return 1 <= op && op <= NUM_OPCODES;
}

// Returns the mnemonic for a given opcode
// if it is legal a opcode. If the opcode
// is illegal a message is printed to stderr
// w/ with exit failure equal to one.
static const char *get_mnemonic(int op){
    if (!legal_op_code(op) ) {
	    error("Illegal opcode detected!"); 
    }
    return mnemonics[op - 1];
}

// Processes program instructions from a 
// given text file into an array of instructions.
void get_instructions(char *filename){
    FILE *fp = fopen(filename, "r"); 
    int i = 0; 
    int num_read; 
    int stop_reading = 0; 
    int op;
    int m;

    printf("%-5s %-5s %-5s", "Addr", "OP", "M"); 
    while(stop_reading != 1){
        num_read = fscanf(fp, "%d %d\n", &op, &m);
        if (!legal_op_code(op) || num_read < 2) {
	        stop_reading = 1;
        }
        else {
            printf("\n%-5d %-5s %-5d", i, get_mnemonic(op), m); 
            instruction_array[i].op = op; 
            instruction_array[i].m = m; 
            i++; 
        }  
    }
    fclose(fp);      
}

// Outputs debugging information.
void trace(){
    if (debug_info){
        printf("PC: %d BP: %d SP: %d", PC, stack_BP(), stack_SP());  
        print_stack(); 
    }
}

// Executes a given instruction using the stack memory.
void execute_instruction(Instruction_T instruction){
    if (instruction.op == 1){ // LIT
        stack_push(instruction.m);
    }
    else if (instruction.op == 2){ // RTN
        PC = stack_pop(); 
        set_BP(stack_pop()); 
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
        int address = stack_BP() - instruction.m; 
        int val = stack_fetch(address); 
        stack_push(val); 
    }
    else if (instruction.op == 7){ // STO
        stack_pop(); 
        int address = stack_SP() + instruction.m; 
        int val = stack_pop(); 
        stack_assign(address, val); 
    }
    else if (instruction.op == 8){ // INC
        stack_allocate(instruction.m); 
    }
    else if (instruction.op == 9){ // JMP
        PC = stack_pop(); 
    }
    else if (instruction.op == 10){ // JPC
        int op1 = stack_pop(); 
        if (op1 != 0){
            PC = instruction.m; 
        }
    }
    else if (instruction.op == 11){// CHO 
        putc(stack_pop(), stdout); 
    }
    else if (instruction.op == 12){ // CHI
        stack_push(getc(stdin));
    }
    else if (instruction.op == 13){ // HLT
        halt = 1; 
    }
    else if (instruction.op == 14){ // NDB
        debug_info = 0; 
    }
    else if (instruction.op == 15){
        stack_push(stack_pop() * -1); 
    }
    else if (instruction.op == 16){ // ADD
        stack_push(stack_pop() + stack_pop());
    }
    else if (instruction.op == 17){ // SUB
        int op1 = stack_pop(); 
        int op2 = stack_pop(); 
        stack_push(op1 - op2);
    }
    else if (instruction.op == 18){ // MUL
        stack_push(stack_pop() * stack_pop()); 
    }
    else if (instruction.op == 19){ // DIV
        int op1 = stack_pop(); 
        int op2 = stack_pop(); 
        if (op2 == 0){
            error("Divisor is zero in DIV instruction!"); 
        }
        stack_push(op1/op2); 
    }
    else if (instruction.op == 20){ // MOD
        int op1 = stack_pop(); 
        int op2 = stack_pop(); 
        if (op2 == 0){
            error("Modulus is zero in MOD instruction!"); 
        }
        stack_push(op1%op2);
    }
    else if (instruction.op == 21){ // EQL
        stack_push(stack_pop() == stack_pop()); 
    }
    else if (instruction.op == 22){ // NEQ
        stack_push(stack_pop() != stack_pop()); 
    }
    else if (instruction.op == 23){ // LSS
       stack_push(stack_pop() < stack_pop()); 
    }
    else if (instruction.op == 24){ // LEQ
        stack_push(stack_pop() <= stack_pop()); 
    }
    else if (instruction.op == 25){ // GTR
        stack_push(stack_pop() > stack_pop()); 
    }
    else if (instruction.op == 26){ // GEQ
        stack_push(stack_pop() >= stack_pop()); 
    }
    else if (instruction.op == 27){ // PSP
        stack_push(stack_SP()); 
    }
    else {
        error("Unidentified opcode detected!"); 
    }
}

// Handles the instructions and output.
void process_instructions(){
    printf("\nTracing ...\n"); 
    trace();
    while (!halt){ 
        if (debug_info){
            printf("\n==> addr: %-6d%-6s%-5d\n", PC, get_mnemonic(instruction_array[PC].op), instruction_array[PC].m); 
        }
        execute_instruction(instruction_array[PC++]); 
        trace(); 
    }
    printf("\n");
    exit(0); 
}