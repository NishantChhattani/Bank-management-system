#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include<stdlib.h>
#include"data.h"


int main()
{

char buff[10];

char uname[30];
double balance;
long long int acc_no;
int ab;
char type;
char buffer[30];
char pass[30]; 
int choice;
int flag=-1;
int input;
int input2;

   printf("   				 BANKING MANAGEMENT SYSTEM    		\n \n");

   printf("Enter Credentials :- ");
   printf("\nUsername - ");
   scanf("%30[^\n]",uname);

   printf("Password - ");
   getchar();
   scanf("%30[^\n]",pass);


struct sockaddr_in server;
int socket_desc;
socket_desc = socket(AF_INET, SOCK_STREAM, 0);
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(34040);
connect(socket_desc, (void *)(&server), sizeof(server));

	write(socket_desc,&uname,sizeof(uname));
	write(socket_desc,&pass,sizeof(pass));
	read(socket_desc,buff, sizeof(buff));
	if(strcmp("failure",buff)!=0)
	{
	if(strcmp("Admin",buff)==0)
	flag=1;
	else
	if(strcmp("NonAdmin",buff)==0)
	flag=0;
	}
	else
	{
	printf("Invalid Credentials");
	}

	if(flag==1)
	{
		while(input!=8)
		{

		printf("  \n\n 				WELCOME ADMIN	\n \n");
		printf("...................................ADMIN MENU................................... \n");
		printf("1)Add Account\n");			
		printf("2)Add Customer\n");				
		printf("3)Show All Active Accounts\n");        
		printf("4)Search Customer \n");	
		printf("5)Modify Customer\n");				
		printf("6)Delete Customer\n");
		printf("7)Exit\n");
		scanf("%d",&input);

		write(socket_desc,&input,sizeof(int));

		switch(input)
			{
			
			 case 1 : 
						 printf("\n Add new Account :- \n\n");
						 getchar();
						 double balll;
						 printf("Enter account details \n\n");
						 printf("Enter account Balance \n");

						 scanf("%lf",&balll);
						 write(socket_desc,&balll,sizeof(double));
						 // Msg to read type 
						 read(socket_desc,buffer, sizeof(buffer));
						 printf("%s",buffer);
						 getchar();
						 scanf("%c",&type);
						 //getchar();
						 write(socket_desc,&type,sizeof(char));

						 read(socket_desc,&acc_no, sizeof(long long int));
						 printf("Account Number:- %lli \n",acc_no);
						 //read success

						 printf("       \n               Add new Account Holders details :-  \n\n");

						 while(1)
							{	
								char buffer2[20];
								printf("Enter Username (unique) \n");
								getchar();
								scanf("%20[^\n]",buffer2);
								//getchar();
								write(socket_desc,buffer2,sizeof(buffer2));

								read(socket_desc,&ab,sizeof(int));
								//printf("ab = %d\n",ab);
								if(ab!=0)
								break;
								else
								printf("Username not Unique\n");
							}

						printf("Enter Password\n");
						getchar();
						scanf("%20[^\n]",pass);
						write(socket_desc,pass,sizeof(pass));
						char typee;
						printf("Enter Customer type (A-Admin , R-Regular))\n");
						getchar();
						scanf("%c",&typee);
						write(socket_desc,&typee,sizeof(char));
						read(socket_desc,buffer, sizeof(buffer));
						printf("%s",buffer);

						if(type=='J')
						{

							printf("       \n          Add Joint Account Holder Details  \n\n");

						 while(1)
							{	
								char buffer2[20];
								printf("Enter Username (unique) \n");
								getchar();
								scanf("%20[^\n]",buffer2);
								//getchar();
								write(socket_desc,buffer2,sizeof(buffer2));

								read(socket_desc,&ab,sizeof(int));
								//printf("ab = %d\n",ab);
								if(ab!=0)
								break;
								else
								printf("Username not Unique\n");
							}

						printf("Enter Password\n");
						getchar();
						scanf("%20[^\n]",pass);
						write(socket_desc,pass,sizeof(pass));
						char typee;
						printf("Enter Customer type (A-Admin , R-Regular))\n");
						getchar();
						scanf("%c",&typee);
						write(socket_desc,&typee,sizeof(char));
						read(socket_desc,buffer, sizeof(buffer));
						printf("%s",buffer);




						}

						break;
	  						

			case 2 : 	
						printf("\nAdd Customer :- \n\n");
						printf("Enter customer details :- \n");
						char pass[20];
						double bal;
						char type3;
						char type[2];
						while(1)
						{	
							char buffer2[20];
							printf("\nEnter Username (unique) \n");
							getchar();
							scanf("%20[^\n]",buffer2);

							write(socket_desc,buffer2,sizeof(buffer2));

							read(socket_desc,&ab,sizeof(int));
							
							if(ab!=0)
							break;
							else
							printf("Username not Unique\n");
						}

						printf("Enter Password\n");
						getchar();
						scanf("%20[^\n]",pass);
						write(socket_desc,pass,sizeof(pass));

						printf("Enter Customer type ( A-Admin , R-Regular)) \n");
						getchar();
						scanf("%2[^\n]",type);
						write(socket_desc,type,sizeof(type));

						printf("\n                Enter Account details associated with customer \n\n");

						
					 	printf("Enter account Balance");
					 	printf("\n");

					 	scanf("%lf",&bal);
					 	write(socket_desc,&bal,sizeof(bal));

					 	//printf("Account type (S-Single,J-Joint) \n");
					 	//getchar();
					 	//scanf("%c",type3);
						//getchar();
						//write(socket_desc,&type3,sizeof(char));

						read(socket_desc,&acc_no, sizeof(long long int));
						printf("Account Number:- %lli \n",acc_no);
						 //read success
						read(socket_desc,buffer, sizeof(buffer));
						printf("%s",buffer);

						break;

			case 3:		printf("Show all Accounts :- \n\n");
			  				struct Account B;
			  				int count;
			  				read(socket_desc,&count,sizeof(int));
			  				printf("total accounts : %d\n",count);
			  				while(count--)
			  				{		

			  						read(socket_desc,&B,sizeof(B));
			  						if(B.astat==1)
			  						{
			  						printf("Account number :- %lli \n",B.Acc_no);
									printf("Account balance :- %lf \n",B.balance);
									printf("Account type :- %c ",B.type);
									printf("\n\n");
									}
			  				}
			  				break;


	  	    case 4:		printf("Show Customer Details \n\n");
	  						printf("Enter Customer Username \n");
	  						char uname[20];
	  						scanf("%s",&uname);
	  						write(socket_desc,uname,sizeof(uname));

	  						struct Customer c3;
	  						
	  						read(socket_desc,&c3,sizeof(c3));
	  						if(c3.stat!=0)
	  						{
	  						printf("Account Holder username :- %s ",c3.username);
							printf("\n");
							printf("Account Holder Password :- %s ",c3.password);
							printf("\n");
							printf("Account number :- %lli ",c3.Acc_no);
							printf("\n");
							printf("Account Priviledge ( A-Admin , R- R-Regular) :- %c ",c3.type);
							printf("\n");
							printf("Account status :- %d ",c3.stat);
							printf("\n");
							}
							else
							{
								printf("This Account was deleted");
							}
	  						break;


  		    case 5:		printf("Modify Customer \n\n");
  						printf("Enter Customer Username to Modify \n");
  						int aa;
  						char uname1[20];
  						scanf("%s",&uname1);
  						write(socket_desc,uname1,sizeof(uname1));
  						
  						read(socket_desc,&aa,sizeof(int));
	  						if(aa)
	  							{
			  						struct Customer c4;
			  						read(socket_desc,&c4,sizeof(c4));
			  						int ch;
			  						printf("Enter option to Modify : \n 1) Username \n 2) Password \n 3) Acccont type \n");
			  								getchar();
			  								//getchar();
									scanf("%d",&ch);

									switch(ch){

									case 1 : { 
										printf("Enter new username ");
										getchar();
										scanf("%20[^\n]",c4.username);
										getchar();
										break;
									}

									case 2 : { 
										printf("Enter new password \n");
										getchar();
										scanf("%20[^\n]",c4.password);
										break;
									}
									case 3 : { 
										printf("Change Account Priviledge to A or R ? ");
										getchar();
										scanf("%c",&c4.type);
										break;
									}

									default : printf("Wrong input");
											  break;

									}

									printf("Account Holder username :- %s ",c4.username);
									printf("\n");
									printf("Account Holder Password :- %s ",c4.password);
									printf("\n");
									printf("Account number :- %lli ",c4.Acc_no);
									printf("\n");
									printf("Account type :- %c ",c4.type);
									printf("\n");
									printf("Account status :- %d ",c4.stat);
									printf("\n");



									write(socket_desc,&c4,sizeof(c4));
									break;

									}
							else
									{
										printf("Wrong username \n");
										break;
									}

			case 6:		printf("Delete Customer \n");
							printf("Enter Customer Username to Delete \n");
	  						int a3;
	  						char uname2[20];
	  						char chhoice;
	  						scanf("%s",&uname2);
	  						write(socket_desc,uname2,sizeof(uname2));
	  						
	  						read(socket_desc,&a3,sizeof(int));
	  						if(a3)
			  						{
			  						struct Customer c5;
			  						read(socket_desc,&c5,sizeof(c5));
			  						printf("Account Holder username :- %s ",c5.username);
									printf("\n");
									printf("Account Holder Password :- %s ",c5.password);
									printf("\n");
									printf("Account number :- %lli ",c5.Acc_no);
									printf("\n");
									printf("Account type :- %c ",c5.type);
									printf("\n");
									printf("Account status :- %d ",c5.stat);
									printf("\n");

			  						printf("\nAre you sure you want to delete the above Customer ( Y or N ) \n");
			  						getchar();
									scanf("%c",&chhoice);
									if(chhoice == 'Y' || chhoice == 'y')
									{
										c5.stat = 0;
										printf("USER DELETED \n");
									}
									else
									{
										printf("Cancelled !");
									}

									write(socket_desc,&c5,sizeof(c5));
			  						}
	  						else
	  						printf("Invalid Username");
	  						break;


	  		case 7:			exit(1);
	  						break;
											

	  		default:		printf("Invalid Input\n");
	  						break;
			
	  			

			}

								printf("\n\n\nEnter Any key to return to menu .....\n");
								getchar();
								getchar();

	  	}

	}
					else if(flag==0)
					{

						while(1)
						{

						printf("   	\n\n			   WELCOME Customer		\n \n");
						printf("............................CUSTOMER MENU.....................................\n");
						printf("\n\n");
						printf("1)Deposit Money \n");			
						printf("2)Withdraw Money\n");				
						printf("3)Balance enquiry \n");        
						printf("4)Password change \n");	
						printf("5)Veiw Transaction Details\n");				
						printf("6)Exit\n");
						printf("\n \n Enter your choice :- \n");
						scanf("%d",&input2);

						write(socket_desc,&input2,sizeof(int));
								switch(input2)
								{

								case 1: printf("\nDeposit Money\n");
										struct Customer c;
										int deposit;
										int val;
										read(socket_desc,&c,sizeof(c));
										printf("Account Holder username :- %s \n",c.username);
										printf("Account number :- %lli ",c.Acc_no);
										printf("\n");
										printf("Enter Amount to Deposit\n");
										scanf("%d",&deposit);
										write(socket_desc,&deposit,sizeof(int));
										read(socket_desc,&val,sizeof(int));

										if(val)
										{	
											printf("\n\nUpdated Account status\n\n");
											struct Account a6;
											read(socket_desc,&a6,sizeof(a6));
											printf("Account Number :- %lli ",a6.Acc_no);
											printf("\n");
											printf("Account Balance:- %lf ",a6.balance);
											printf("\n");
											printf("Account Status :- %d ",a6.astat);
											printf("\n");
											printf("Account type :- %c ",a6.type);
											printf("\n");
										}
										else
										{
											printf("Invalid Details\n");
										}

										break;

								case 2: printf("\nWithdraw Money\n");
										struct Customer cc;
										int depositt;
										int valu;
										read(socket_desc,&cc,sizeof(cc));
										printf("Account Holder username :- %s \n",cc.username);
										printf("Account number :- %lli ",cc.Acc_no);
										printf("\n");
										printf("Enter Amount to Withdraw\n");
										scanf("%d",&depositt);
										write(socket_desc,&depositt,sizeof(int));
										read(socket_desc,&valu,sizeof(int));

										if(valu)
										{	
											printf("\n\nUpdated Account status\n\n");
											struct Account a6;
											read(socket_desc,&a6,sizeof(a6));
											printf("Account Number :- %lli ",a6.Acc_no);
											printf("\n");
											printf("Account Balance:- %lf ",a6.balance);
											printf("\n");
											printf("Account Status :- %d ",a6.astat);
											printf("\n");
											printf("Account type :- %c ",a6.type);
											printf("\n");
										}
										else
										{
											printf("Invalid Details\n");
										}
										break;

								case 3 : printf("\nBalance enquiry\n");

										struct Customer c5;
										
										int value;
										read(socket_desc,&c5,sizeof(c5));
										read(socket_desc,&value,sizeof(int));
										if(value)
										{	
											struct Account a7;
											read(socket_desc,&a7,sizeof(a7));
											printf("Account Number :- %lli ",a7.Acc_no);
											printf("\n");
											printf("Account Balance:- %lf ",a7.balance);
											printf("\n");
											printf("Account Status :- %d ",a7.astat);
											printf("\n");
										}
										else
										{
											printf("Invalid Details\n");
										}
										
			

										 break;

								case 4: printf("\nPassword Change :- \n");
										char passw[20];
										int f;
										printf("Enter new Password :- \n");
										getchar();
										scanf("%20[^\n]",passw);
										write(socket_desc,&passw,sizeof(passw));
										read(socket_desc,&f,sizeof(int));
										if(f)
										printf("Password Updated Successfully\n");
										else
										printf("Password updation failed\n");
										break;

								case 5: printf("\nView Customer Details\n");
										struct Customer c9;
										int count4=0;
										int valll;
										read(socket_desc,&c9,sizeof(c9));
										printf("Account Holder username :- %s \n",c9.username);
										printf("Account number :- %lli \n\n ",c9.Acc_no);
										printf("\n");

										read(socket_desc,&valll,sizeof(int));
										struct Account a6;
										read(socket_desc,&a6,sizeof(a6));
										
										struct Transaction TT;
											
										write(socket_desc,&c.Acc_no,sizeof(long long int));

										read(socket_desc,&count4,sizeof(int));
										printf("Count = %d\n",count4);
										while(count4--)
										{
											read(socket_desc,&TT,sizeof(TT));
											printf("Accont Number : %lli \n",TT.Acc_no);
											printf("Amount : %d \n",TT.amount);
											printf("Balance remaining : %lf \n",TT.balance_rem);
											printf("Transaction date and time: %s \n \n", ctime(&TT.t));
										}


										break;

								case 6: printf("Session Ended\n");
										exit(1);


								default: printf("invalid input");
										 break;

								}

								printf("Enter Any key to return to menu .....\n");
								getchar();
								getchar();

						}


					}

	return 0;
}
