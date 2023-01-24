#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "stack.h"

#define MAX_CODE_LENGTH 512

int INSTRUCTION_COUNT = 0; 
int SP = 0; // Stack pointer    
int PC = 0; // Program counter  
int BP = 0; // Base pointer

struct Instruction{
    int op; 
    int m; 
};

void trace(Stack_T stack){
    printf("PC: %d BP: %d SP: %d\n", PC, BP, SP); 
    print_stack(stack); 
}

/* Prints out decoded program memnonic */
void print_memnonic(Instruction_T instruction){    
    switch (instruction.op){
        case (1): 
            printf("LIT");
            break;  
        case (2): 
            printf("RTN"); 
            break; 
    } 
}


/* Processes program instructions from text file into an array of instructions */
Instruction_T *get_instructions(char *filename){
    Instruction_T *instruction_array = (Instruction_T*) malloc(MAX_CODE_LENGTH * sizeof(struct Instruction)); 
    FILE *fp = fopen(filename, "r"); 
    int i = 0; 

    while (!feof(fp)){  
        fscanf(fp, "%d %d", &instruction_array[i].op, &instruction_array[i].m); 
        i++; 
        INSTRUCTION_COUNT++; 
    }
    fclose(fp);      

    return instruction_array; 
}

/* Handle instructions */
void process_instructions(Instruction_T *instruction_array, Stack_T stack){
    printf("\nTracing...\n"); 
    for (int i = 0; i < INSTRUCTION_COUNT; i++){
        trace(stack);

        // Output specific instruction info 
        printf("==> addr: %d\t", i); 
        print_memnonic(instruction_array[i]);
        printf("\t%d\n", instruction_array[i].m); 

        execute_instruction(instruction_array[PC], stack); // Do some halt condition handling 
        PC = PC + 1;
        trace(stack); // Print initial state  
    }
}

/* Execute a given instruction using the stack memory */
void execute_instruction(Instruction_T instruction, Stack_T stack){
    
    // Decode the instructions 
    if (instruction.op == 1){ 
        // 
        push(stack, instruction.m); 
    }
    else if (instruction.op == 15){ 
        // Negate the value in the top of the stack
        push(stack, (pop(stack) * -1)); 
    }
    else if (instruction.op == 16){
        
    }
    else if (instruction.op == 17){
        
    }
    else if (instruction.op == 18){
        
    }
    else if (instruction.op == 19){
        
    }
    else if (instruction.op == 20){
        
    }
    else {
        // Probably like a halt condition or something idk 
    }
    
}