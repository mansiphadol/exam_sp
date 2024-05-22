//lab 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256 // max length the program can read from a file
#define MAX_SYMBOLS 100  // max symbols the program can handle
#define MAX_LITERALS 100 // max literals the program can handle

typedef struct {
    char label[20]; // stores symbol's name
    int address;    // stores symbol's address
} SymbolTableEntry;

typedef struct {
    char literal[20];
    int address;
} LiteralTableEntry;

SymbolTableEntry symbolTable[MAX_SYMBOLS];
LiteralTableEntry literalTable[MAX_LITERALS];
int lc = 0; // Location counter

void addToSymbolTable(char label[]) {
    strcpy(symbolTable[lc].label, label); // copies label to the label field in symbol table at index lc
    symbolTable[lc].address = lc;        // initialises the address of the label field
}

void addToLiteralTable(char literal[]) {
    strcpy(literalTable[lc].literal, literal); //Copies the literal to the literal field of the literalTable at index lc.
    literalTable[lc].address = lc;
}

void processLine(char line[]) {
    char *token;
    char *delim = " \t\n"; // Delimiters: space, tab, newline
    char *label, *opcode, *operand;

    // Tokenize the line
    token = strtok(line, delim); //strtok: Splits the line into tokens based on delimiters.
    if (token != NULL) {
        label = token;    //Assigns the first token to label
        token = strtok(NULL, delim);
        if (token != NULL) {
            opcode = token;  //assigns second token to opcode
            token = strtok(NULL, delim);
            if (token != NULL) {
                operand = token; // assigns third token to operand

                // Process label
                if (strcmp(label, "START") != 0 && strcmp(label, "END") != 0) // if the label is neither start or end then add it to the table
                    addToSymbolTable(label);

                // Process operand
                if (operand[0] == '=') {
                    addToLiteralTable(operand); //Checks if the operand starts with '=' and adds it to the literal table if true.
                }

                // Increment location counter
                lc++;
            }
        }
    }
}

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];

    // Open the input file
    file = fopen("Input_Pass_1_of_2_pass.asm", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        processLine(line);
    }

    // Close the file
    fclose(file);

    // Output symbol table
    printf("Symbol Table:\n");
    for (int i = 0; i < lc; i++) {
        printf("%s\t%d\n", symbolTable[i].label, symbolTable[i].address);
    }

    // Output literal table
    printf("\nLiteral Table:\n");
    for (int i = 0; i < lc; i++) {
        printf("%s\t%d\n", literalTable[i].literal, literalTable[i].address);
    }

    return 0;
}
