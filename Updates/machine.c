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
        case (3): 
            printf("CAL");
            break;  
        case (4): 
            printf("POP"); 
            break;
        case (5): 
            printf("PSI");
            break;  
        case (6): 
            printf("PRM"); 
            break;
        case (7): 
            printf("STO");
            break;  
        case (8): 
            printf("INC"); 
            break;
        case (9): 
            printf("JMP");
            break;  
        case (10): 
            printf("JPC"); 
            break; 
        case (11): 
            printf("CHO");
            break;  
        case (12): 
            printf("CHI"); 
            break;
        case (13): 
            printf("HLT");
            break;  
        case (14): 
            printf("NDB"); 
            break;
        case (15): 
            printf("NEG");
            break;  
        case (16): 
            printf("ADD"); 
            break; 
        case (17): 
            printf("SUB");
            break;  
        case (18): 
            printf("MUL"); 
            break;
        case (19): 
            printf("DIV");
            break;  
        case (20): 
            printf("MOD"); 
            break;
        case (21): 
            printf("EQL");
            break;  
        case (22): 
            printf("NEQ"); 
            break; 
        case (23): 
            printf("LSS");
            break;  
        case (24): 
            printf("LEQ"); 
            break;
        case (25): 
            printf("GTR");
            break;  
        case (26): 
            printf("GEQ"); 
            break;
        case (27): 
            printf("PSP"); 
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
    trace(stack); 
    for (int i = 0; i < INSTRUCTION_COUNT; i++){
        

        // Output specific instruction info 
        printf("==> addr: %d\t", i); 
        print_memnonic(instruction_array[i]);
        printf("\t%d\n", instruction_array[i].m); 

        execute_instruction(instruction_array[PC], stack); // Do some halt condition handling 

        trace(stack); // Print initial state  
    }
}

/* Execute a given instruction using the stack memory */
void execute_instruction(Instruction_T instruction, Stack_T stack){
    
    // Decode the instructions 
    if (instruction.op == 1){ 
        // Literal push: stack[SP] ← n; SP ← SP + 1
        push(stack, instruction.m);
        SP++;
        PC++;
    }
    else if (instruction.op == 2){ // -----------------------------FIXMEE: Address needs to be updated in here. May be address should
                                   // be a global variable
        
        // Returns from a subroutine and restores the caller’s AR:
        // PC ← stack[SP − 1]; BP ← stack[SP − 2]; SP ← SP − 2
        
        PC = pop(stack); // Top of stack holds the return address to the previous AR
        BP = pop(stack); // The value at SP − 2 should be zero.
        SP -= 2; // This will have the SP point the top of the previous AR.
 
    }
    else if (instruction.op == 3){ // -----FIXMEE: Needs to print last two elements of the stack
                                  // The address needs to be updated here.
        
        // Call the procedure at code index p, generating a new activation record
        // and setting PC to p: stack[SP] ← BP; (dynamic link)
        // stack[SP + 1] ← PC; (return address)
        // BP ← SP; SP ← SP + 2; PC ← p;

        PC = instruction.m;
        BP = SP;
        push(stack, 0);
        push(stack, (SP-1));
        SP = SP + 2;
    }
    else if (instruction.op == 4){ 
        // Pop the stack: SP ← SP − 1;
        
        pop(stack);
        SP--;
        PC++; 
    }
    else if (instruction.op == 5){ 
        // Push the element at address stack[SP − 1] on top of the stack:
        // stack[SP − 1] ← stack[stack[SP − 1]]

        push(stack, top(stack));
        PC++;
        SP++;
        
         
    }
    else if (instruction.op == 6){ 
        // Parameter at stack[BP − o] is pushed on the stack:
        // stack[SP] ← stack[BP − o]; SP ← SP + 1

        push(stack, get_value(stack, BP - instruction.m));
        PC++;
        SP++;
         
    }
    else if (instruction.op == 7){ 
        // Store stack[SP − 2] into the stack at address stack[SP − 1] + o and pop
        // the stack twice:
        // stack[stack[SP − 1] + o] ← stack[SP − 2]; SP ← SP − 2
        
        //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< WORKING HERE!!!! 1_26_23 at 11:37 am <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        PC++;
        SP -= 2;
         
    }
    else if (instruction.op == 8){ 
        // Allocate m locals on the stack: SP ← SP + m
        
        int i = 0;
        while(i < instruction.m)
        {    
            push(stack, 0);
            i++;
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 9){
        // Jump to the address in stack[SP − 1] and pop:
        // PC ← stack[SP − 1]; SP ← SP − 1
    }
    else if (instruction.op == 10){
        // Jump conditionally: if the value in stack[SP − 1] is not 0, then jump to
        // a and pop the stack:
        // if stack[SP − 1] ̸= 0 then {PC ← a} ; SP ← SP − 1

    }
    else if (instruction.op == 11){
        // Output of the value in stack[SP − 1] to standard output as a character
        // and pop:
        // putc(stack[SP − 1], stdout); SP ← SP − 1
        
    }
    else if (instruction.op == 12){
        // Read an integer, as character value, from standard input and store it in
        // the top of the stack, but on EOF or error, store -1:
        // stack[SP] ← getc(stdin); SP ← SP − 1
        
    }
    else if (instruction.op == 13){
        // Halt the program’s execution
    }
    else if (instruction.op == 14){
        // Stop printing debugging output   
    }
    else if (instruction.op == 15){ 
        // Negate the value in the top of the stack
        push(stack, (pop(stack) * -1));
        PC++; 
    }
    else if (instruction.op == 16){
        // Add the top two elements in the stack:
        // stack[SP − 2] ← stack[SP − 1] + stack[SP − 2]; SP ← SP − 1
        
        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        int result = operand2 + operand1;

        push(stack, result);
        SP++;

        PC++;
    }
    else if (instruction.op == 17){
        // Subtract the 2nd to top element from the top one:
        // stack[SP − 2] ← stack[SP − 1] − stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        int result = operand2 - operand1;

        push(stack, result);
        SP++;

        PC++;
    }
    else if (instruction.op == 18){
        // Multiply the top two elements in the stack:
        // stack[SP − 2] ← stack[SP − 1] × stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        int result = operand2 * operand1;

        push(stack, result);
        SP++;

        PC++;
    }
    else if (instruction.op == 19){
        // Divide the top element by the 2nd from top element:
        // stack[SP − 2] ← stack[SP − 1]/stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        int result = operand2 / operand1;

        push(stack, result);
        SP++;

        PC++;   
    }
    else if (instruction.op == 20){
        // Modulo, result is the remainder of the top by the 2nd from top element
        // of the stack:
        // stack[SP − 2] ← stack[SP − 1]modstack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        int result = operand2 % operand1;

        push(stack, result);
        SP++;

        PC++;
    }
    else if (instruction.op == 21){
        // Are (the contents of) the top and 2nd from top element equal?
        // stack[SP − 2] ← stack[SP − 1] = stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        if(operand1 == operand2)
        {
            push(stack, 1);
            SP++;
        }
        else
        {
            push(stack, 0);
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 22){
        // Are (the contents of) the top and 2nd from top element different?
        // stack[SP − 2] ← stack[SP − 1] ̸= stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        if(operand1 != operand2)
        {
            push(stack, 1);
            SP++;
        }
        else
        {
            push(stack, 0);
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 23){
        // Is (the contents of) the top element strictly less than the 2nd from top
        // element?
        // stack[SP − 2] ← stack[SP − 1] < stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        if(operand1 < operand2)
        {
            push(stack, 1);
            SP++;
        }
        else
        {
            push(stack, 0);
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 24){
        // Is (the contents of) the top element no greater than the 2nd from top
        // element?
        // stack[SP − 2] ← stack[SP − 1] ≤ stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        if(operand1 <= operand2)
        {
            push(stack, 1);
            SP++;
        }
        else
        {
            push(stack, 0);
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 25){
        // Is (the contents of) the top element strictly greater than the 2nd from top?
        // stack[SP − 2] ← stack[SP − 1] > stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        if(operand1 > operand2)
        {
            push(stack, 1);
            SP++;
        }
        else
        {
            push(stack, 0);
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 26){
        // Is (the contents of) the top element no less than the contents of the 2nd
        // from top element?
        // stack[SP − 2] ← stack[SP − 1] ≥ stack[SP − 2]; SP ← SP − 1

        int operand1 = pop(stack);
        SP--;
        int operand2 = pop(stack);
        SP--;

        if(operand1 >= operand2)
        {
            push(stack, 1);
            SP++;
        }
        else
        {
            push(stack, 0);
            SP++;
        }
        PC++;
    }
    else if (instruction.op == 27){
        // Push SP (i.e., the address itself) on top of the stack:
        // stack[SP] ← SP; SP ← SP + 1

        push(stack, SP);
        SP++; 

        PC++; 
    }
    else {
        // Probably like a halt condition or something idk 
    }
    
}