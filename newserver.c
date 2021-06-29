
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include"data.h"
#include<stdlib.h>

int main()
{

int a,b,c,d;
char buff[30];
char buff2[30];
int ifile;
int user_choice=-1;
int flag=0;
int flag2=-1;

struct sockaddr_in server, client;
int socket_desc, size_client, client_desc;
socket_desc = socket(AF_INET, SOCK_STREAM, 0);
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(34040);
if(bind(socket_desc, (void *)(&server), sizeof(server)) < 0)
{
	perror("Error on binding:");
	exit(EXIT_FAILURE);
}
	listen(socket_desc, 3);		
		while(1)
		{
			size_client = sizeof(client);
			if((client_desc = accept(socket_desc, (struct sockaddr*)&client,&size_client)) < 0) 
			{
				perror("Error on accept:");
				exit(EXIT_FAILURE);
			}
			if(fork() == 0)
			{
				read(client_desc,buff,sizeof(buff));
				read(client_desc,buff2,sizeof(buff2));
				

				   struct Customer cst;
				   ifile = open("customer",O_RDONLY);
				   while(read(ifile,&cst,sizeof(cst))!=0)
				   {

				      if((strcmp(cst.username,buff)==0) && (strcmp(cst.password,buff2)==0))
				      {
				         flag=1;

				         if(cst.type=='A')
				         flag2=1;
				     	 else
				     	 flag2=0;
				         break;
				      }

				   }

				   printf("flag = %d",flag);
				   if(flag)
				   {	
				   if(flag2)	
				   	write(client_desc,"Admin",sizeof("Admin"));
				    else
				    write(client_desc,"NonAdmin",sizeof("NonAdmin"));
				   }
				   else
				   write(client_desc,"failure",sizeof("failure"));


				if(flag2==1)
				{
					while(1)
					{
					//Initiate Admin Operations
					read(client_desc,&user_choice, sizeof(int));
					printf("choice = %d \n",user_choice);

					switch(user_choice)
					{	
						case 1 : printf("Adding new Account \n");
								 a = addAccount2(client_desc);
								 break;


						case 2 : printf("Add new customer \n");
								 a = addCustomer(client_desc);
								 break;


						case 3: printf("Show all Account \n\n");
								int ofile;
								int h;
								int count=0,count2=0;
								ofile=open("account",O_RDONLY);
								struct Account A;
								while(read(ofile,&A,sizeof(A))!=0)
								{
									count++;

								}
								
								printf("Count = %d\n",count);
								
								write(client_desc,&count,sizeof(int));
								h=lseek(ofile,0,SEEK_SET);
							
								  while(read(ofile,&A,sizeof(A))!=0)
									{
								      write(client_desc,&A,sizeof(A));
									}
								close(ofile);
								break;


						case 4: printf("Show Customer Details \n");
								char use_name[30];
								read(client_desc,use_name,sizeof(use_name));
								printf("Input by client %s \n",use_name);
								a = custDetails(use_name,client_desc);
								break;

						case 5: printf("Modify Customer Details \n");
								char user_name[30];
								read(client_desc,user_name,sizeof(user_name));
								printf("Input by client %s \n",user_name);
								
							    b = modify_Cust(user_name,client_desc);

								break;

						case 6:	printf("Delete Customer \n");
								char usr_name[30];
								read(client_desc,usr_name,sizeof(usr_name));
								printf("Input by client %s \n",usr_name);
								
							    b = Delete_Cust(usr_name,client_desc);

							    break;



						case 8: printf("Exiting \n");
								 exit(1);



						default: printf("invalid input");
								 break;



					}

				}

				}
				else
				{
					// Regular Customer side

					//while(user_choice != 8)
					while(1)
					{
					//Initiate Regular User Operations
					int amount;
					long long int ano;
					read(client_desc,&user_choice, sizeof(int));
					printf("choice = %d \n",user_choice);

					switch(user_choice)
					{	
						case 1 : ano = custDetails(buff,client_desc);
								 c =read(client_desc,&amount,sizeof(int));
								 b = Modify_Account(client_desc,ano,1,amount);
								 break;


						case 2 : ano = custDetails(buff,client_desc);
								 c =read(client_desc,&amount,sizeof(int));
								 b = Modify_Account(client_desc,ano,2,amount);
								 break;

						case 3 : ano = custDetails(buff,client_desc);
								 b = Modify_Account(client_desc,ano,3,0);
								 break;


						case 4: printf("Password Change\n");
								char newpass[20];
								read(client_desc,&newpass,sizeof(newpass));
								int l = change_pass(client_desc,buff,newpass);
								break;



						case 5 : printf("View all Details");
								 ano = custDetails(buff,client_desc);
								 long long int q;
								 int countt=0;
								 int g;
								 b = Modify_Account(client_desc,ano,5,0);
								 struct Transaction R;
								 read(client_desc,&q,sizeof(long long int));
								 int tfile = open("transaction",O_RDONLY);

								 while(read(tfile,&R,sizeof(R))!=0)
								 {
								 	if(R.Acc_no == q)
								 	countt++;
								 }
								 printf("Count = %d\n",countt);
								 write(client_desc,&countt,sizeof(int));

								 g=lseek(tfile,0,SEEK_SET);

								 
								 while(read(tfile,&R,sizeof(R))!=0)
								 {
								 	if(R.Acc_no == q)
								 	write(client_desc,&R,sizeof(R));
								 }

								 close(tfile);
								 
								 break;




						default: printf("invalid input");
								 break;




					}

					}

		
				close(client_desc);
				exit(EXIT_SUCCESS);


				}
			}	
			else
			{
			close(client_desc);
			}
			
		}
























	return 0;
}