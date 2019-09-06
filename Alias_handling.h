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

	cout<<" \nvalue ="<<value;

	//char * p =(char *)malloc(value.length() * sizeof(char*) ); 
  	//cout<<"\n" << sizeof(p)<<" "<< value.length();
  	char p[1024];
  	int i;
    for (i = 0; i < value.length()+1; i++) { 
        p[i] = value[i]; 
        //cout << p[i]; 
    } 
    //p[i]=NULL;
    cout<<"\n p = "<<p;
    strcpy(command,p);
    //free(p);
}

// void init_alias()
// {
// 	char * ll="ls -alF";
// 	char * la="ls -A";
// 	char * l="ls -CF";
// 	string temp="ll";
//     alias_map.insert(pair<string, char *>(temp, "shrayans")); 
//     alias_map.insert(pair<string, char *>("la", la)); 
//     alias_map.insert(pair<string, char *>("l", l)); 
//     // //cout<<"alisas updated \n";
//     //  for (itr = alias_map.begin(); itr != alias_map.end(); ++itr) { 
//     //     cout <<"\n" << itr->first <<" "
//     //           << itr->second << '\n'; 
//     // } 
// }

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

	//cout<<key<<" "<<value;

    char * p =(char *)malloc(value.length() * sizeof(char) ); 
  	//cout<<"\n" << sizeof(p)<<" "<< value.length();
    for (int i = 0; i < value.length(); i++) { 
        p[i] = value[i]; 
        //cout << p[i]; 
    } 
    //cout<<" value of p ="<<p;
    
	alias_map.insert(pair<string, char *>(key, p) );
}


// int main()
// {

// 	for (int i = 0; i < 1; i++)
// 	{
// 		char c[100];
// 		cin.getline(c,100);
// 		char * argv[50];
// 		//cout<<c<<" " ;

// 		parseCommand_alias(c,argv);
// 		//cout<<argv[0]<<" ";
// 		if(!strcmp(argv[0], "alias"))
// 		{
// 			//cout<<"i m in";
// 			insert_alias_map(argv);
// 		}
// 	}

// 	init_alias();
// 	cout<<"enter command\n";
// 	char command[100];
// 	cin.getline(command,100);

// 	//char *argv[50];
// 	check_for_alias(command);


// 	// int i=0;
// 	// while(argv[i])
// 	// 	cout<<argv[i++]<<" " ;
// 	cout<<command<<"\n";
// }