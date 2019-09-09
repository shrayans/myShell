#include <stdio.h>
#include <fcntl.h> 
#include <sys/utsname.h>
#include <pwd.h>
#include <stdlib.h>

#include<bits/stdc++.h>
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  

#include <errno.h>   
#include <sys/wait.h>
#include<iostream> 

using namespace std;


std::vector<char *> file_type;
std::vector<char *> app_path;
std::vector<char *> app_name;



void handle_open(char * file)
{
	char *argv[10];
	char ** temp=argv;

 	char file_copy[100];
 	strcpy(file_copy,file);
 	char* token = strtok(file, ".");

	while (token != NULL) {  
		*temp=token;
		*temp++;
		token = strtok(NULL, " "); 
	} 

	*temp=NULL;
	*temp--;

	int i;
	for(i=0; i<file_type.size();i++)
	{
		if(!strcmp(file_type[i],*temp))
			break;
	}
	if(i>=file_type.size())
	{
		cout<<"Error:No associated application\n";
		return;
	}

	if(!fork()){
		close(1);
    	execlp(app_name[i], app_path[i], file_copy, NULL);
	}

}

void handle_$(char * command)
{
	command++;
	

	if(!strcmp(command, "$"))
	{
	  	cout<<getpid()<<"\n";
	  	return;
	}

	if(!strcmp(command, "?"))
	{
	  	cout<<last_proc_status<<"\n";
	  	return;
	}
	//cout<<command;
	if(getenv(command))
		printf("%s\n", getenv(command));

}




void init()
{

	// file_type.push_back("txt");
	// app_name.push_back("gedit");
	// app_path.push_back("/usr/bin/gedit");

	alias_map.insert({"~", getenv("HOME")} );
  	int fd, sz; 
  	char *c = (char *) calloc(1000, sizeof(char)); 

  	uid_t uid=getuid();

  	struct passwd * my_passwd;
	my_passwd = getpwuid(uid);

	struct utsname name;
	if (uname(&name)==-1) {
	    //die("%s",strerror(errno));
	    printf("Error in getting hostname");
	}
	const char* hostname=name.nodename;
  
  	fd = open("myrc.txt", O_RDONLY); 
  	if (fd < 0) { perror("Error: unable to load myrc"); exit(1); } 
   	sz = read(fd, c, 1000); 
	c[sz] = '\0'; 

	
	char* token = strtok(c, "\n");

	setenv("PATH",token,1); 
	
	setenv("USER",my_passwd->pw_name,1);

	setenv("HOME",my_passwd->pw_dir,1);// does overwrite

	setenv("HOSTNAME",hostname,1);

	char ps1[100]="";

	sprintf(ps1,"%s%s%s%s",getenv("USER"),"@",getenv("HOSTNAME"),":");
	
	setenv("PS1",ps1,1);

	token=strtok(NULL,"\n");

	setenv("HISTSIZE",token,1);

	token = strtok(NULL, "\n"); 

	while(token != NULL)
	{
		strcat(token,"");
		//cout<<token;
		//token = strtok(NULL, "\n"); 
		file_type.push_back(token);
		token = strtok(NULL, "\n"); 
		app_name.push_back(token);
		token = strtok(NULL, "\n"); 
		app_path.push_back(token);

		token = strtok(NULL, "\n"); 


	}

	// printf("PATH : %s\n", getenv("PATH"));
	// printf("PATH : %s\n", getenv("USER"));
	// printf("PATH : %s\n", getenv("PS1"));	

	// for(int i=0;i<file_type.size();i++)
	// {
	// 	cout<<"\n"<<file_type[i]<<" "<<app_name[i]<<" "<<app_path[i]<<"\n";
	// }


	close(fd);

	//return 0;
}