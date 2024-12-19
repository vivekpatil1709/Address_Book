/**************************************************************************************************************************************************
														ADDRESSBOOK PROJECT
**************************************************************************************************************************************************/
/*
	Name : Vivek Bharat Patil
	Date : 04/09/2024
	Description : AddessBook Project Using  the File I/O
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int choice,count;                                        // created global variables
char search[11],ch;
struct Details                                          // Structure of 4 members 
{
	char name[20];
	char email[40];
	char address[20];
	char mob[11];
};

void Add_Details(struct Details);                                  // function prototypes 
void Print_Details();
void Search_Details(struct Details);
void Edit_Details(struct Details);
void Delete_Details(struct Details);
char * search_function();
void Copying();

int main()
{
	struct Details User;                                        // Creation of Structure Variable
	system("clear");
	while(1)                                                    // infinte looping to show the prompt
	{
		printf("-------------------------------\n");
		printf("\tADDRESSBOOK\n");
		printf("-------------------------------\n");
		printf("1.Add Details\n2.Print Details\n3.Search Details\n4.Edit Details\n5.Delete Details\n6.Exit\n-------------------------------\nEnter the choice : ");
		scanf(" %d",&choice);
		system("clear");
		switch(choice)                                           // Selecting the option using Switch Case
		{
			case 1 : Add_Details(User);                          // Calling the function when the User calling
			         break;
			case 2 : Print_Details();
			         break;
			case 3 : Search_Details(User);
			         break;
			case 4 : Edit_Details(User);
			         break;
			case 5 : Delete_Details(User);
			         break;
			case 6 : system("clear");
					 printf("*************** PROGRAM TERMINATED ***************\n");
					 return 0;
			default: printf("Invalid Entry...!!\n");
		}
		while(1)
		{
			printf("Do you want to continue (Y/n): ");
			scanf(" %c",&ch);
			system("clear");
			if(ch=='Y' || ch=='y')
				break;
			else if(ch=='N' || ch=='n')
				return 0;
			else
				printf("Command Not Found\n");
		}
	}
}
void Add_Details(struct Details User)                                     // function use 
{
	char *name_str=malloc(20*sizeof(name_str));
	char *email_str=malloc(20*sizeof(email_str));
	char *address_str=malloc(20*sizeof(address_str));
	char *mob_str=malloc(20*sizeof(mob_str));
	FILE *fptr1=fopen("Data.csv","r");                                   // Opening the file in read mode
	FILE *fptr2=fopen("Temp.csv","w");                                   // Opening the file in write mode

	fscanf(fptr1,"%d\n",&count);                                        // Storing the count value to understand the data count
	fprintf(fptr2,"%d\n",count+1);                                      // Printing the count+1 value int the temporary file
	
	int flag=0;
	for(int i=0;i<count;i++)
	{
		fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User.name,User.email,User.address,User.mob);   // Read the data from the main file to Structure varaiable 
		fprintf(fptr2,"%s,%s,%s,%s\n",User.name,User.email,User.address,User.mob);               // Write the data from the Structure varaiable to temporary file
	}
	printf("-------------------------------\n");
	printf("Enter the Name : ");                                           // Read the Data from the User
	scanf(" %[^\n]",name_str);
	printf("Enter the Email Address : ");
	while(1)
	{
		scanf(" %[^\n]",email_str);
		int S=0,str=0,L=0;
		if(strlen(email_str)>=6 && strlen(email_str)<=30)
		{
			if(strstr(email_str,".com")!=NULL)
				str=1;
			for(int i=0;i<strlen(email_str);i++)
			{
				if(email_str[i]=='@')
					S=1;
				else if(email_str[i]>='a' && email_str[i]<='z')
					L=1;
			}
		}
		if(S==1 && str==1 && L==1)
			break;
		printf("Invalid Email Address...!!\nPelase,Re-Enter the Email Address : ");
	}                                               
	printf("Enter the Location : ");
	scanf(" %[^\n]",address_str);
	printf("Enter the Mobile No. : ");
	while(1)
	{
		scanf(" %[^\n]",mob_str);
		if(strlen(mob_str)==10)                                      // Checking the Valid Entry of the Number
		{
			int Y=0;
			for(int i=0;i<strlen(mob_str);i++)
			{
				if(!(mob_str[i]>='0' && mob_str[i]<='9'))
				{
					Y=1;
					break;
				}
			}
			if(!(Y==1))
			{
				system("clear");
				break;
			}
			printf("Invalid Mobile No...!!\nYou have Entered Alphabet or Special Character\nPelase,Re-Enter the Mobile No. : ");
		}
		else
			printf("Invalid Mobile No...!!\nYou have Entered Alphabet or Special character or Extra Digits\nPelase,Re-Enter the Mobile No. : ");                        
    }
	for(int i=0;i<count;i++)
	{
		fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User.name,User.email,User.address,User.mob);
		if(strcmp(User.mob,mob_str)==0)
		{
			flag=1;
			printf("-----------------------------------------------\n");
            printf("\t\tCONTACT\n");
            printf("-----------------------------------------------\n");
			printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",User.name,User.email,User.address,User.mob);
			printf("-----------------------------------------------\n");
			printf("You Entered Data is Already Avaiable is the Database.\n");
			
			break;
		}
	}
	if(!flag)
	{
		printf("Data Added Successfully...!!\n");
		fprintf(fptr2,"%s,%s,%s,%s\n",name_str,email_str,address_str,mob_str);
		fclose(fptr1);                                          // Closing of both the files
		fclose(fptr2);         
		Copying();                                               // Copying the temporary file Data character by character to the main file
	}
	free(name_str);
	free(email_str);
	free(address_str);
	free(mob_str);                                              
}

int ascend(char *a, char *b)
{
	return *a > *b;
}

int descend(char *a, char *b)
{
	return  *a < *b;
}
void Print_Details()
{
	FILE *fptr1=fopen("Data.csv","r");                         // Opening the file in read mode  
	
	int (*fptr)(char *,char *);
	fscanf(fptr1,"%d\n",&count);

	struct Details User[count];
	if(count==0)
	{
		printf("EMPTY FILE ... !!\n");
		return;
	}
	while(1)
	{
		printf("----------------------------\nDisplay Menu : \n----------------------------\n1.A to Z\n2.Z to A\n3.Regular\n4.Exit\n----------------------------\nEnter the choice : ");
		scanf("%d",&choice);
		if(choice==1)
		{
			fptr=ascend;
			break;
		}
		else if(choice==2)
		{
			fptr=descend;
			break;
		}
		else if(choice==3)
			break;
		else if(choice==4)
		{
			system("clear");
			return;
		}
		else
			printf("Invalid Choice...!!\n");
	}

	if(choice==1 || choice==2)
	{
		for(int j=0; j<count; j++)
			fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User[j].name,User[j].email,User[j].address,User[j].mob);
	}
	system("clear");
	if(choice==1 || choice==2)
	{
		for(int i=0;i<count-1;i++)
		{
			for(int j=0;j<count-i-1; j++)
			{
				if(fptr(User[j].name,User[j+1].name))
				{
					char temp[30];
					strcpy(temp,User[j].name);
					strcpy(User[j].name,User[j+1].name);
					strcpy(User[j+1].name,temp);
					strcpy(temp,User[j].email);
					strcpy(User[j].email,User[j+1].email);
					strcpy(User[j+1].email,temp);
					strcpy(temp,User[j].address);
					strcpy(User[j].address,User[j+1].address);
					strcpy(User[j+1].address,temp);
					strcpy(temp,User[j].mob);
					strcpy(User[j].mob,User[j+1].mob);
					strcpy(User[j+1].mob,temp);
				}
			}
		}
	}
	for(int i=0;i<count;i++)
	{
		if(choice==3)
			fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User[i].name,User[i].email,User[i].address,User[i].mob);
		printf("-----------------------------------------------\n");
        printf("\t\tCONTACT %d\n",i+1);                                          // Print All Data
        printf("-----------------------------------------------\n");
		printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",User[i].name,User[i].email,User[i].address,User[i].mob);
        printf("-----------------------------------------------\n");
	}
	                                                        
	fclose(fptr1);
}

void Search_Details(struct Details User)
{
	FILE *fptr1=fopen("Data.csv","r");                              // Opening the file in read mode
	if(search_function() == NULL)
		return;
	fscanf(fptr1,"%d\n",&count);
	for(int i=0;i<count;i++)
	{
		fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User.name,User.email,User.address,User.mob);
		if(strcmp(search,User.email)==0 || strcmp(search,User.mob)==0)
		{                                                      // Print the Searched Contact
			printf("-----------------------------------------------\n");
            printf("\t\tCONTACT\n");
            printf("-----------------------------------------------\n");
			printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",User.name,User.email,User.address,User.mob);
			printf("-----------------------------------------------\n");
			return;
		}
	}
	system("clear");
	printf("Data Not Found...!!\n");
	fclose(fptr1);
}

void Edit_Details(struct Details User)
{
	FILE *fptr1=fopen("Data.csv","r");                  // Opening the file in read mode
	FILE *fptr2=fopen("Temp.csv","w");                  // Opening the file in write mode

	fscanf(fptr1,"%d\n",&count);
	fprintf(fptr2,"%d\n",count);
	
	int flag=0;
	if(search_function() == NULL)
		return;
	for(int i=0;i<count;i++)
	{
		fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User.name,User.email,User.address,User.mob);
		if(strcmp(search,User.email)==0 || strcmp(search,User.mob)==0)
		{
			flag=1;
			system("clear");
            printf("-----------------------------------------------\n");              // Printing the Contact before the edit
            printf("\t\tCONTACT\n");
            printf("-----------------------------------------------\n");
			printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",User.name,User.email,User.address,User.mob);
			printf("-----------------------------------------------\n");
			printf("--------------------------\n");
			printf("What do you what to Edit\n");
			while(1)
			{
                printf("--------------------------\n1.Name\n2.Email Address\n3.Location\n4.Mobile No.\n--------------------------\nEnter the choice : ");
				scanf(" %d",&choice);
				if(choice==1)
				{
					printf("Enter the New name : ");                           // Editing the New name and store in the main file
					scanf(" %[^\n]",User.name);	
				}
				else if(choice==2)
				{
					printf("Enter the New Email Address : ");
					while(1)
					{
						scanf(" %[^\n]",User.email);
						int S=0,str=0,L=0;
						if(strstr(User.email,".com")!=NULL)
							str=1;
						for(int i=0;i<strlen(User.email);i++)
						{
							if(User.email[i]=='@')
								S=1;
							else if(User.email[i]>='a' && User.email[i]<='z')
								L=1;
						}
						if(S==1 && str==1 && L==1)
							break;
						printf("Invalid Email Address...!!\nPelase,Re-Enter the New Email Address : ");
					}
				}
				else if(choice==3)
				{
					printf("Enter the New Location : ");
					scanf(" %[^\n]",User.address);
				}
				else if(choice==4)
				{
					printf("Enter the New Mobile No.: ");
					while(1)
					{
						scanf(" %[^\n]",User.mob);
						if(strlen(User.mob)==10)                                      // Checking the Valid Entry of the Number
						{
							int Y=0;
							for(int i=0;i<strlen(User.mob);i++)
							{
								if(!(User.mob[i]>='0' && User.mob[i]<='9'))
								{
									Y=1;
									break;
								}
							}
							if(!(Y==1))
							{
								system("clear");
								break;
							}
							printf("Invalid Mobile No...!!\nYou have Entered Alphabet or Special Character\nPelase,Re-Enter the Mobile No. : ");
						}
						else
							printf("Invalid Mobile No...!!\nYou have Entered Alphabet or Special character or Extra Digits\nPelase,Re-Enter the Mobile No. : ");                        
                    }
				}
				else	
					printf("Invalid Entry...!!\nEnter the Choice Again\n");
                if(choice<=4 && choice>=1)
                {
					int i=1,k;
    				while(i<=100)
    				{
        				printf("\rUpdating[");
        				for(int j=1;j<=i;j++)                          
        	    			printf("-");                                          
				        for(k=i;k<100;k++)
    	    			    printf(" ");
			        	printf("]%d%%",i);   
        				fflush(stdout);
			        	usleep(20000);
	      				i++;
    				}   
					system("clear");
                    printf("-----------------------------------------------\n");           // Printing the Contact after the edit
                    printf("\t\tCONTACT\n");
                    printf("-----------------------------------------------\n");
			        printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",User.name,User.email,User.address,User.mob);
			        printf("-----------------------------------------------\n");
                    fprintf(fptr2,"%s,%s,%s,%s\n",User.name,User.email,User.address,User.mob);
                    break;
                }
			}
		}
		else
			fprintf(fptr2,"%s,%s,%s,%s\n",User.name,User.email,User.address,User.mob);
	}
	fclose(fptr1);
	fclose(fptr2);
	if(flag)
	{
		Copying();
		printf("Data Edit Successfully...!!\n");
		return;
	}
	printf("Data Not Available...!!\n");
}
void Delete_Details(struct Details User)
{
	FILE *fptr1=fopen("Data.csv","r");                               // Opening the file in read mode
	FILE *fptr2=fopen("Temp.csv","w");                               // Opening the file in write mode

	fscanf(fptr1,"%d\n",&count);
	fprintf(fptr2,"%d\n",count-1);
	
	int flag=0;
	if(search_function() == NULL)
		return;
	for(int i=0;i<count;i++)
	{
		fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",User.name,User.email,User.address,User.mob);
		if(strcmp(search,User.email)==0 || strcmp(search,User.mob)==0)
        {
            printf("-----------------------------------------------\n");               // Printing the Data to delete 
            printf("\t\tCONTACT\n");
            printf("-----------------------------------------------\n");
			printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",User.name,User.email,User.address,User.mob);
			printf("-----------------------------------------------\n");
            while(1)
            {
                printf("Do you want to delete this contact(Y/N) : ");
                scanf(" %c",&ch);
				system("clear");
                if(ch=='Y' || ch=='y')                                                 // Again asking the User to delete the data or not
				    break;
			    else if(ch=='N' || ch=='n')
				    return;
			    else
				    printf("Command Not Found\n");
            }
            flag=1;
            continue;
        }
		fprintf(fptr2,"%s,%s,%s,%s\n",User.name,User.email,User.address,User.mob);	
	}
	fclose(fptr1);
	fclose(fptr2);
	if(flag)
	{
		int i=1,k;
    	while(i<=100)
    	{
        	printf("\rDeleting[");
        	for(int j=1;j<=i;j++)
        	    printf("-");
	        for(k=i;k<100;k++)
    	        printf(" ");
        	printf("]%d%%",i);   
        	fflush(stdout);
        	usleep(20000);
	        i++;
    	}
		Copying();
		system("clear");
		printf("\nData Deleted Successfully...!!\n");
		return;
	}
	printf("Data Not Available...!!\n");	
}

char * search_function()
{
	while(1)
	{
		printf("----------------------------\nYou want to Search by :\n----------------------------\n1.Email\n2.Mobile No.\n3.Exit\n----------------------------\nEnter the Choice : ");
		scanf("%d",&choice);
		system("clear");
		if(choice==1)
		{
			printf("Enter the Email to Search : ");                   // Searching the given email and matching the email with the Data  
			scanf(" %[^\n]",search);
			system("clear");
			return search;
		}
		else if(choice==2)
		{
			printf("Enter the Mobile No. to Search : ");                   // Searching the given mobile and matching the no. with the Data  
			scanf(" %[^\n]",search);
			system("clear");
			return search;
		}
		else if(choice==3)
			return NULL;
		else
			printf("Invalid Choice...!!\n");
	}
}

void Copying()
{
	FILE *fptr1=fopen("Data.csv","w");                                   // Opening the file in write mode
	FILE *fptr2=fopen("Temp.csv","r");                                   // Opening the file in read mode
	char ch;
	while((ch=fgetc(fptr2)) != EOF)
		fputc(ch,fptr1);                                                // Copying all the Data character by character from one file to another 
	fclose(fptr1);
	fclose(fptr2);
}