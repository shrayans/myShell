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
#include "Init.h"

using namespace std;

// bool script_flag=false;
// char  script_path[150]="default_file.txt";

void exec_for_script(char * command)
{
	int fd = open(script_path, O_CREAT | O_RDWR | O_APPEND,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	int sz = write(fd, command, strlen(command));
	sz = write(fd, "\n", strlen("\n"));  
	int x=dup(1);

	if(!fork())
	{
		pid_t pid;
		char * argv[50];
	  	parseCommand_IO(command,argv);

	  	//cout<<argv[0]<<"\t";//<<argv[1];
	  	dup2(fd,1);

	  	if(!strcmp(argv[0], "alias"))
		{
			//cout<<"i m in";
			insert_alias_map(argv);
			//continue;
		}


	  	if(!strcmp(argv[0], "cd"))
	  	{	
	  		//cout<<"yes i m in cd\n";
	  		chdir(argv[1]);
	  		//continue;
	  	}

	     pid=fork();

	     if(pid==0)
	     {
	     	if(execvp(argv[0], argv) < 0)    
                printf("Error: command not found\n");
            abort();
	     }
	     else{
	     	wait(NULL);
	     	abort();
	     }
	     
	}
	else
	{
		//wait(NULL);
		dup2(1,x);
		close(fd);
	}
}

void printPromt()
{

  	uid_t uid;/*uid_t is a build in data type, which can hold small numbers*/
    string username;
    uid=getuid();
 //    username=getlogin();

	char pwd [200];
	getcwd(pwd, 100);

	// char hostname[100];
 //    gethostname(hostname, 1024);

 //    string PS1="\n"+username+"@"+hostname+":~"+pwd;

    if(uid=0)
    {
    	cout<<"\n"<<getenv("PS1")<<"# ";
    }
    else
    {
		cout<<"\n"<<getenv("PS1")<<pwd<<"$ ";
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

char command_copy[1024];

int main()
{
	init();
	
	while(1)
	{

		//clrscr();
		printPromt();
		
		pid_t pid;
		int status;

	    char command[1024];

	    cin.getline(command,1024);

	    //updating history

	    update_History(command);

	    //check for alias in command
		check_for_alias(command);
		//cout<<"\ncommand : before script-"<<command<<"\n";

		strcpy(command_copy,command);


	  	if( checkIO(command) ){
	  		//cout<<"getio\n";
	  		handleIO(command);
	  		continue;
	  	}


	  	char * argv[50];
	  	parseCommand(command,argv);

		if(argv[0]==NULL)
			continue;
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

	  	if(!strcmp(argv[0], "exit"))
	  	{	
	  		exit(0);
	  	}	  	

	  	if(!strcmp(argv[0], "record"))
	  	{	
	  		if(!strcmp(argv[1],"start"))
	  			script_flag=true;
	  		else
	  			script_flag=false;

	  		if(argv[2]!=NULL)
	  			strcpy(script_path,argv[2]);

	  		getcwd(script_path,150);
	  		strcat(script_path,"/record_file.txt");
	  		cout<<"\n"<<script_path;
	  		continue;
	  	}

	  	if(!strcmp(argv[0], "open") && argv[1]!=NULL)
	  	{	
	  		//cout<<"yes i m in cd\n";
	  		handle_open(argv[1]);
	  		continue;
	  	}

	  	if(!strcmp(argv[0], "history"))
	  	{
	  		print_history();
	  		continue;
	  	}

	  	if(!strcmp(argv[0], "echo"))
	  	{
	  		if(*argv[1]=='$')
	  		{
	  			handle_$(argv[1]);
	  			continue;
	  		}
	  		//continue;
	  	}

	  	if(!strcmp(argv[0], "export"))
	  	{
	  		setenv(argv[1],argv[2],1);
	  		continue;
	  	}

	  	if(script_flag)
		{
			exec_for_script(command_copy);
		}
		//cout<<"\ncommand : after script-"<<command_copy<<"\n";

	     pid=fork();

	     if(pid==0)
	     {
	     	if(execvp(argv[0], argv) < 0){    
                printf("Error: Command not found");
                
                exit(1);

            }
	     }
	     else{
	     	waitpid(pid, &status, 0);
	     	last_proc_status=WEXITSTATUS(status);
	     //cout<<"\nLast process status "<<last_proc_status;
	 		}
	}


}
		


//cp /home/shrayans/raj.cpp /home/shrayans/Documents


//https://github.com/shrayans/myShell.git

//https://github.com/IIIT-OS-PG/shell-shrayans