#include <stdio.h>
#include <string.h>

#define MAX_CODE 100
//t1 = a + b
//t2 = t1 * c
//t3 = t2 - d
//result = t3


typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} IntermediateCode;

IntermediateCode code[MAX_CODE];
int codeCount = 0;

void readIntermediateCode() {
    // In a real scenario, you would read this from a file or input.
    // Here we hardcode for simplicity
    strcpy(code[0].op, "ADD");
    strcpy(code[0].arg1, "a");
    strcpy(code[0].arg2, "b");
    strcpy(code[0].result, "t1");

    strcpy(code[1].op, "MUL");
    strcpy(code[1].arg1, "t1");
    strcpy(code[1].arg2, "c");
    strcpy(code[1].result, "t2");

    strcpy(code[2].op, "SUB");
    strcpy(code[2].arg1, "t2");
    strcpy(code[2].arg2, "d");
    strcpy(code[2].result, "t3");

    strcpy(code[3].op, "MOV");
    strcpy(code[3].arg1, "t3");
    strcpy(code[3].arg2, "result");
    strcpy(code[3].result, "");

    codeCount = 4;
}

void generateMachineCode() {
    // Register and memory address mappings for simplicity
    int registerIndex = 1;
    int memoryAddress = 1000;
    char address[100][10];  // Mapping of variable names to addresses
    char addressMapping[100][10]; // Memory addresses corresponding to variable names
    int addressCount = 0;

    // Function to get or allocate address
    char* getAddress(char* var) {
        for (int i = 0; i < addressCount; i++) {
            if (strcmp(address[i], var) == 0) {
                return addressMapping[i];
            }
        }
        strcpy(address[addressCount], var);
        sprintf(addressMapping[addressCount], "%d", memoryAddress);
        memoryAddress++;
        addressCount++;
        return addressMapping[addressCount - 1];
    }

    for (int i = 0; i < codeCount; i++) {
        if (strcmp(code[i].op, "ADD") == 0) {
            printf("0001 0001 %s 0000  ; LOAD R1, %s (load from address %s into R1)\n", getAddress(code[i].arg1), code[i].arg1, getAddress(code[i].arg1));
            printf("0001 0010 %s 0000  ; LOAD R2, %s (load from address %s into R2)\n", getAddress(code[i].arg2), code[i].arg2, getAddress(code[i].arg2));
            printf("0011 0011 0001 0010  ; ADD R3, R1, R2 (R3 = R1 + R2)\n\n");
        } else if (strcmp(code[i].op, "MUL") == 0) {
            printf("0001 0100 %s 0000  ; LOAD R4, %s (load from address %s into R4)\n", getAddress(code[i].arg1), code[i].arg1, getAddress(code[i].arg1));
            printf("0100 0101 0011 0100  ; MUL R5, R3, R4 (R5 = R3 * R4)\n\n");
        } else if (strcmp(code[i].op, "SUB") == 0) {
            printf("0001 0110 %s 0000  ; LOAD R6, %s (load from address %s into R6)\n", getAddress(code[i].arg1), code[i].arg1, getAddress(code[i].arg1));
            printf("0101 0111 0101 0110  ; SUB R7, R5, R6 (R7 = R5 - R6)\n\n");
        } else if (strcmp(code[i].op, "MOV") == 0) {
            printf("0010 %s 0111 0000  ; STORE %s, R7 (store R7 to address %s)\n", getAddress(code[i].arg2), code[i].arg2, getAddress(code[i].arg2));
        }
    }
}






int main() {
    readIntermediateCode();
    generateMachineCode();
    return 0;
}

