#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

struct private_files          // sruct for storing private files
	{
		char name[100];
		char password[100];
	};
	struct private_files stk_private[10];
	static int prvt_index = 0;

void tokenize(char buff[100],char res[100])   // function to tokenize input and store result in output
{
		char *token;
		char seprator[2] = "/";
		token = strtok(buff, seprator);
		while( token != NULL )
		{
			strcpy(res,token);
			token = strtok(NULL, seprator);
		}
	
}

void printcurrdir()          // function to print current directory
{
		char my_pwd[1024]; 
		char res[100];
	    getcwd(my_pwd, sizeof(my_pwd)); 
	    tokenize(my_pwd,res);
	    printf("%s ", res);
}

int my_cd(char input[100])        // function to change directory to desired input
{
		char s[100];
		int res = chdir(input);
		if(res == 0)
		{
			printf("Directory changed to: %s\n",getcwd(s,100));
		}
		else
		{
			printf("Error!   Path not correct\n");
		}
}

void my_ls1()              // function to print all files/directories in curr working dir ("ls")
{

 	DIR *dir = opendir(".");           // open current working directory
	struct dirent *dir_fd;
	while((dir_fd = readdir(dir)) != NULL)       // read data from directory opened
	{
	    int i=0,flag =0;
	    for(;i<prvt_index;i++)                   // chaeck is curr dir is private ?
		{
			if(!strcmp(stk_private[i].name,dir_fd->d_name) )      
			{
					flag = 1;
			}
		}
		if(!strcmp(".",dir_fd->d_name) || !strcmp("..",dir_fd->d_name))
			flag=1;
		if(flag == 0)                             // print all dir names which are not private
			printf(" %s\n", dir_fd->d_name);
	    
	}
	closedir(dir);
}


int my_ls_search(char * input)   // function to search if input name is in current dir
{
	 int ans =0;
	 DIR *dir = opendir(".");           // open current working directory
	struct dirent *dir_fd;
	while((dir_fd = readdir(dir)) != NULL)     // read data from directory opened
	{
	  	if(!strcmp(dir_fd->d_name,input))
	  		ans = 1;
	}
	closedir(dir);
	return ans;
}

//------------------------------------Stack for push pop ------------------------------------
	

static int stkptr = -1;
static int size = 10;

char stack[10][100] = {{0}};    // stach for storing addressess

int IsEmpty()      // checks if stack is empty
{
	return stkptr == -1;
}

int IsFull()      //checks if stack is full
{
	return stkptr == size - 1;
}

int push(char * data)    // for inserting data in stack
{
	if (!IsFull())
	{
		stkptr++;
		strcpy(stack[stkptr],data);
		return 1;
	}
	else
	{
		printf("Error: Stack Full!\n");
		return 0;
	}
}

int pop(char * data)    // for removing data from stack
{
	if (!IsEmpty())
	{
		strcpy(data,stack[stkptr]);
		stkptr--;
		return 1;
	}
	else
	{
		printf("Error: Stack Empty!\n");
		return 0;
	}
}

int showtop(char * data)    // returns value on the top of stack
{
	if (!IsEmpty())
	{
		strcpy(data,stack[stkptr]);
		return 1;
	}
	else
	{
		printf("Error: Stack Empty!\n");
		return 0;
	}
}

void printStack()   // prints data of stack
{
	int i = 0;
	while (i < stkptr + 1) {
		printf("%s\n",stack[i]);
		i++;
	}
	
}


void takeinput()    // function to take input from user and respond accordingly
{
	char buff[100];        // for taking input
	char buff1[100];

     // -------------------     how to use Message  --------------------
	system("clear");
	printf("--------------How to Use--------------\n");
	printf("1)    cd/\"newpath\"      e.g cd/home/xyz\n");
	printf("2)    push/\"newpath\"    e.g push/home/\n");
	printf("3)    pop-showtop\n");     
	printf("4)   \"folder/file name\"-private   e.g Labs-private\n");
	printf("5)    ls-private\n");
	printf("----------write \"exit\" to terminate--------");

	// --------------  taking input ---------------------
	while(1)
	{
		printf("\n%s","17L-4154 - "); 
		printcurrdir();
		printf("%s ",">");

		                          // take input
		scanf("%s",buff);
		strcpy(buff1,buff);
		char * sep = "/";
		int flag=0,flag2=0; 
		if(strstr(buff,"-") != 0)    // separator is -
			flag=1;
		if(strstr(buff,"/") != 0)     // separator is /
			flag2=1;
	
		char * in = strtok(buff, sep);
		char * rem = strtok(NULL, "");
		char dest[100] = "/";
		int flag_ls =0;
		int flag_pop =0;
		int flag_private =0;
	
		if(rem == 0 && flag ==1)    // if separator "/" not found and separator "-" found 
		{
			sep = "-";
			in = strtok(buff, sep);
			rem = strtok(NULL, "");
			strcpy(dest,rem);
			if(!strcmp(in, "ls"))
			{
				flag_ls = 1;
			}
			if(!strcmp(rem, "private"))
			{
				flag_private = 1;
			}
			else if(!strcmp(in, "pop"))
			{
				flag_pop = 1;
			}
			
		}
		else if(rem != 0 && flag2 == 1)      // if separator "/" found 
		{
			char src[90];
			strcpy(src,rem);   			// adding "/" 
			strcat(dest, src);
		}

		if(!strcmp(in, "ls") && flag_ls == 0)   // simple ls no parimeter("-")
		{
			my_ls1();
		}

		else if(!strcmp(in, "cd"))        // check for cd    
		{
			if(rem==NULL)
    			printf("Error: Please enter new path correctly\n" );
    		else
				my_cd(dest);
		}
		
		else if(!strcmp(in, "pwd"))      //  check for pwd
		{
			char my_pwd[1024]; 
    		getcwd(my_pwd, sizeof(my_pwd)); 
    		printf("%s\n",my_pwd);
		}
		else if(!strcmp(in, "push"))      // check for push
		{
			char curr_dir[1024]; 
    		getcwd(curr_dir, sizeof(curr_dir)); 
    		if(rem==NULL)
    			printf("Error: Please enter new path as well\n" );
    		else
    			{
    				push(curr_dir);
    				my_cd(dest);
    			}
		}
		else if(!strcmp(in, "pop") && flag_pop == 0) // check for simple pop 
		{
			char curr_dir[100];
    		int output = pop(curr_dir);
    		if(output == 1)
    		{
    			my_cd(curr_dir);
    		}
    		else
    			printf("Stack Empty!\n");
		}
		else if(!strcmp(in, "pop") && (!strcmp(dest, "showtop")) && flag_pop == 1)  // check for pop-showtop
		{
			char curr_dir[100];
    		int output = showtop(curr_dir);
    		if(output == 1)
    			printf("%s\n",curr_dir );
    		else
    			printf("Stack Empty!\n");
		}
										
		else if(flag_private == 1 && flag_ls == 0 )   // check for private a file
		{								    
			 int output = my_ls_search(in);
			 char pass[100];
			 if(output == 1)              // if file is in curr dir
			 {
			 	printf("Plaese Enter Password\n");
			 	scanf("%s",pass);
			 	strcpy(stk_private[prvt_index].name,in);
			 	strcpy(stk_private[prvt_index].password,pass);
			 	prvt_index++;
			 	printf("\"%s\" Protected\n",in);

			 }
			 else
			 {
			 	printf("No such directory/file found\n");
			 }

		}
		else if(flag_ls == 1 && !strcmp(in, "ls") && !strcmp(rem, "private"))  // check for ls-private
		{
				char pass[100];
				printf("Please enter Password \n");
				scanf("%s",pass);
				int i=0,index=0,output =0,count=0;
				char dir_names[10][100];
				for(;i<prvt_index;i++)
				{
					if(!strcmp(stk_private[i].password,pass))
						{
							strcpy(dir_names[index],stk_private[i].name);
							output = my_ls_search(dir_names[index]);
							if(output == 1)
								{
									printf(" %s\n",dir_names[index]);
									count++;
								}
							index++;
						}
				}
				if(count == 0)
							printf("Error: No files! or incorrect Password\n");
				else
					my_ls1();          // those which are not protected
		}
		else if(!strcmp(buff, "exit"))   // exit program
		{
				break;
		}
		else        // if nothing match
		{
			printf("Error: Please follow syntax\n");
		}
	}
}

// ------------------------------- Main Function ---------------------------------------------
int main(int argc, char* argv[])
{

	takeinput();

	return 0;
}
