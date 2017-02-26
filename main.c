#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void help()
{
    printf("\nAssembler For a 16 Bit ISA");
    printf("\nUse : assembler path/to/file\n\n");
//     printf("\nOptions");
//     printf("\n-d=[value] : sets debug on for value 1");
//     printf("\n-a         : show Authors");
//     printf("\n-h         : show Help");
}

int main(int argc, char **argv) {
    
    if(argc < 2)
    {
        printf("\nNo File Selected !!!\n");
        help();
        return 0;
    }
    
    FILE* fptr = fopen(argv[1],"r");
    if(fptr == NULL)
    {
        printf("\nCannot Read File !!!\n");
        help();
        return 0;
    }
    fseek(fptr, 0, SEEK_END);
	long tempsize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	char *tempstr = malloc (sizeof (char) * tempsize);
	fscanf(fptr,"%s[^\n]",tempstr); //reading content before the null character
    printf("input = %s\n",tempstr);
    fscanf(fptr,"%s[^\n]",tempstr); //reading content before the null character
    printf("input = %s\n",tempstr);
	fclose(fptr);
     Parser* pr = createParser(tempstr);
     char* output = parse(pr);
     
    if(parserHasError(pr))
    {
        long lineno = 0;
        long pos = 0;
        long ins = 0;
        char* error = parserError(pr,&lineno,&pos,&ins);
        printf("\nError in Instruction %ld at %ld:%ld \n",ins,lineno,pos);
        printf("\n%s",error);
        return 0;
    }
    printf("\n\n");
    printf("%s",output);
    printf("\n\n");
    
    return 0;
}
