#include<bits/stdc++.h>
#include <stdio.h> 


using namespace std;

map<string, char *> alias_map;
map<string, char *>::iterator itr; 

void parseCommand_alias(char * command,char **argv)
{
		char* token = strtok(command, " "); 

	  	char ** temp=argv;
	  
		// Keep printing tokens while one of the 
		// delimiters present in str[]. 
		while (token != NULL) { 
			 
	      	*temp=token;
	      	*temp++;
			token = strtok(NULL, " "); 
		} 

		*temp=NULL;

		//cout<<command<<"\n";

}

void check_for_alias(char * command)
{
	//cout<<"i mhere\n";
	char * argv[50];
	parseCommand_alias(command,argv);
	
	char ** temp=argv;
	//cout<<"i m here \n";

	while(*temp)
	{
		//printf("%s", *temp);

		itr=alias_map.find(*temp);

		if(itr!=alias_map.end())
		{
			*temp=itr->second;
			//cout<<"I m in";
		}

		*temp++;
	}

	string value="";

	temp=argv;

	while(*temp )
	{
		//cout<<*temp<<"i m \n";
		value=value+*temp;
		value=value+" ";
		*temp++;
	}

	//cout<<" \nvalue ="<<value;

	//char * p =(char *)malloc(value.length() * sizeof(char*) ); 
  	//cout<<"\n" << sizeof(p)<<" "<< value.length();
  	char p[1024];
  	int i;
    for (i = 0; i < value.length()+1; i++) { 
        p[i] = value[i]; 
        //cout << p[i]; 
    } 
    //p[i]=NULL;
    //cout<<"\n p = "<<p;
    strcpy(command,p);
    //free(p);
}


char p[256];

void insert_alias_map(char ** argv)
{
	string key=argv[1];
	char ** temp =argv+4;
	string value="";
	//cout<<argv[4];
	while(*(temp+1) )
	{
		value=value+*temp;
		value=value+" ";
		*temp++;
	}

	cout<<key<<" \t"<<value;

     
  	//cout<<"\n" << sizeof(p)<<" "<< value.length();
    for (int i = 0; i <= value.size(); i++) { 
        p[i] = value[i]; 
        //cout << p[i]; 
    } 
   // cout<<" value of p ="<<p;
    pair <string, char*> PAIR1 ; 
  
    PAIR1.first = key; 
    PAIR1.second = p ;
    //cout<<PAIR1.second; 
	alias_map.insert(PAIR1);
}


