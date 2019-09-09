#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h>

#define BUFFER_SIZE 1000

#define FileNAme "history.txt"

vector<char * > history_vector;

void update_history_vector(char * command)
{
   char *s =getenv("HISTSIZE");
   char *end;
   //cout<<" size *** "<< history_vector.size()<<" " << command<<"\n";

   long n = strtol(s,&end,10);

   if(n<=history_vector.size())
   {
        history_vector.erase(history_vector.begin());
        history_vector.push_back(command);
        return;
   }
   char *t=new char[100];
   strcpy(t,command);
   //cout<<"Yes";

   history_vector.push_back(t);

}


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

    update_history_vector(command);
}



void print_history()
{
    for(int i=0 ;i<history_vector.size();i++)
    {
        cout<<history_vector[i]<<"\n";
    }
}
