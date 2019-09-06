#include<bits/stdc++.h>
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 
#include "IO_handle_header.h"
#include "History_maintain.h"
#include "Alias_handling.h"

using namespace std;


void printPromt()
{

  	uid_t uid;/*uid_t is a build in data type, which can hold small numbers*/
    string username;
    uid=getuid();
    username=getlogin();

	char pwd [200];
	getcwd(pwd, 100);

	char hostname[100];
    gethostname(hostname, 1024);

    string PS1="\n"+username+"@"+hostname+":~"+pwd;

    if(uid=0)
    {
    	PS1+="# ";
    }
    else
    {
		cout<<PS1<<"$ ";
	}
}

void parseCommand(char * command,char **argv)
{
		char* token = strtok(command, " "); 

	  	char ** temp=argv;
	  
		// Keep printing tokens while one of the 
		// delimiters present in str[]. 
		while (token != NULL) { 
			//printf("%s\n", token); 
	      	*temp=token;
	      	*temp++;
			token = strtok(NULL, " "); 
		} 

		*temp=NULL;
}



int main()
{
	
	while(1)
	{

		//clrscr();
		printPromt();
		
		pid_t pid;

	    char command[1024];

	    cin.getline(command,1024);

	    //updating history
	    update_History(command);

	    //check for alias in command
		check_for_alias(command);
		cout<<"\ncommand : "<<command<<"\n";

	  	if( checkIO(command) ){
	  		//cout<<"getio\n";
	  		handleIO(command);
	  		continue;
	  	}

	  	char * argv[50];
	  	parseCommand(command,argv);

	  	//cout<<argv[0]<<"\t";//<<argv[1];

	  	if(!strcmp(argv[0], "alias"))
		{
			//cout<<"i m in";
			insert_alias_map(argv);
			continue;
		}


	  	if(!strcmp(argv[0], "cd"))
	  	{	
	  		//cout<<"yes i m in cd\n";
	  		chdir(argv[1]);
	  		continue;
	  	}

	     pid=fork();

	     if(pid==0)
	     {
	     	if(execvp(argv[0], argv) < 0)    
                printf("Error: command not found\n");
	     }
	     else
	     	wait(NULL);
	     

	}


}
		


//cp /home/shrayans/raj.cpp /home/shrayans/Documents


//https://github.com/shrayans/myShell.git