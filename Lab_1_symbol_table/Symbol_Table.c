#include <stdio.h>      // Standard input-output library for file operations and printing
#include <stdlib.h>     // Standard library for memory allocation, process control, etc.
#include <string.h>     // String handling functions
#include <ctype.h>      // Character handling functions (e.g., isspace)


int checkDataType(char *string, char *(*Datatypes)[6]) //compares the input string with the datatypes array and check whether it is present or not?
{
    char **array = *Datatypes;
    for (int i = 0; i < 6; i++)
    {
        if (strstr(string, array[i]))
        {
            return i;
        }
    }
    return -1;
}
void trim(char **line, char *Data) //moving the line pointer forward by length of data
{
    *line = *line + strlen(Data);
}
int main()
{
    FILE *fileptr = fopen("InputCode.c", "r");
    if (fileptr == NULL)
    {
        perror("fopen");
        exit(1);
    }

    static const char *Datatypes[6] = {"char", "short", "int", "long", "float", "double"};
    int DataSize[6] = {1, 2, 4, 4, 4, 8};
    char buffer[256];
    int address = 100;
    printf("\nSymbol\tType\tLength\tAddress\n\n");
    while (fgets(buffer, sizeof(buffer), fileptr))
    {
        char *line = strdup(buffer); // creating duplicate string and store in buffer
        while (isspace((unsigned char)*line)) //skipping white spaces
            line++;

        if (*line == '\0') // skipping white spaces
        {
            continue;
        }
        int ret = checkDataType(line, &Datatypes);  //Checks for a datatype in the line.

        if (ret != -1) // if the datatype is found
        {
            trim(&line, Datatypes[ret]); //trims the datatype from the line
            while (isspace((unsigned char)*line)) // skips white spaces after datatype
                line++;

            char symbol[100];
            memset(symbol, 0, sizeof(symbol)); //initialises the symbol buffer
            while (*line != ';') // loops until end of declaration
            {
                if (*line == ',') // end of the variable
                {
                    printf("%s\t%s\t%d\t%d\n", symbol, Datatypes[ret], DataSize[ret], address);
                    address = address + DataSize[ret]; // updating memory address
                    memset(symbol, 0, sizeof(symbol)); // resetting symbol buffer for next var
                }
                else if (*line == '[') // handles array declaration
                {
                    strncat(symbol, &line[0], 1);
                    line++;
                    strncat(symbol, &line[0], 1);
                    int num = (int)(*line) - 48; // converts int array size to character
                    line++;
                    strncat(symbol, &line[0], 1);
                    if (line[1] != ';') line++;

                    printf("%s\t%s\t%d\t%d\n", symbol, Datatypes[ret], num * DataSize[ret], address);
                    address = address + DataSize[ret] * num; // updating memory address

                    memset(symbol, 0, sizeof(symbol)); //resetting symbol buffer

                }
                else
                {
                    strncat(symbol, &line[0], 1); //adds variable name in the table
                }
                line++; // next character
            }
            if (symbol[0] != '\0') // prints last symbol in line if exists
            {
                printf("%s\t%s\t%d\t%d\n", symbol, Datatypes[ret], DataSize[ret], address);
                address = address + DataSize[ret];
            }
        }
    }
    fclose(fileptr);

    return 0;
}
