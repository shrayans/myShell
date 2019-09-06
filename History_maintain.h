#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

#define FileNAme "history.txt"

void  update_History(char * command)
{

    FILE *fPtr;
    char filePath[100];

    fPtr = fopen(FileNAme, "a");

    if (fPtr == NULL)
    {
        printf("Error in updating history");
    }


    fputs(command, fPtr);
    fputs("\n",fPtr);

    fclose(fPtr);


}




