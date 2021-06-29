#include <stdio.h> 
#include <stdlib.h> 
#include<fcntl.h>
#include<string.h>				
#include<time.h>

long long int generateAccountNo();

	struct Customer
	{
		char username[30];
		char password[30];
		long long Acc_no;
		char type;
		int stat;
	};

	struct Account
	{
		long long int Acc_no;
		double balance;
		char type;
		int astat;
		
	};

	struct Transaction
	{
		long long int Acc_no;
		time_t t;
		int amount;
		double balance_rem;
		
	};

	long long int generateAcc_no()
	{
	srand(time(0));
 	long long int random=rand()%10000000;
	return random;
	}	
	

	int addAccount(int client_desc,long long int cust_Acc_no)
	{
				int ifile;
				long long int as;
				double tt;
				as = cust_Acc_no;
				ifile=open("account",O_WRONLY|O_APPEND);
				struct Account acc3;

				//write(client_desc,"Enter Account balance\n",sizeof("Enter Account balance\n")); 

				read(client_desc,&tt,sizeof(double));  
				printf("balance received = %lf",tt);
				printf("\n");
				acc3.balance=tt;
				
				//read(client_desc,&acc3.type, sizeof(char));
				//printf("Type received - %c",acc3.type);

				acc3.type = 'S';
				
				acc3.Acc_no=cust_Acc_no;						
				printf("Account no. :- %lli \n",acc3.Acc_no);
				write(client_desc,&as,sizeof(long long int));

				acc3.astat=1;									
				ssize_t s=write(ifile,&acc3,sizeof(acc3));		

				if(s>0){write(client_desc,"New account add Successful \n",sizeof("New account add Successful \n"));return 1;}
				else return -1;
	}


	int addAccount2(int client_desc)
	{
				int ifile;
				int h,g;
				ifile=open("account",O_WRONLY|O_APPEND);
				struct Account acc3;
				
				read(client_desc,&acc3.balance, sizeof(double));  
				
				write(client_desc,"Enter Account type(S,J)\n",sizeof("Enter Account type(S,J)\n"));
				read(client_desc,&acc3.type,sizeof(char));
				printf("Type received - %c",acc3.type);

				acc3.Acc_no=generateAcc_no();				
				printf("Account no. :- %lli \n",acc3.Acc_no);
				write(client_desc,&acc3.Acc_no,sizeof(long long int));
				acc3.astat=1;					
				h = addCustomer2(client_desc,acc3.Acc_no);
				printf("Account type = %c \n",acc3.type);
				if(acc3.type=='J')
				{
						write(client_desc,"New account add Successful \n",sizeof("New account add Successful \n"));
						
						g = addCustomer2(client_desc,acc3.Acc_no);


				}

				ssize_t s=write(ifile,&acc3,sizeof(acc3));		
				close(ifile);
				
				if(s>0){write(client_desc,"New account add Successful \n",sizeof("New account add Successful \n"));return 1;}
				else return -1;
	}


	int show_allaccont(int client_desc)
	{
				int ofile;
				struct Account show;
				
				ofile = open("account",O_RDONLY);
				while(read(ofile,&show,sizeof(show))!=0)
				{	if(show.astat!=0)
					{
					
					printf("Account number :- %lli \n",show.Acc_no);
					write(client_desc,&show.Acc_no,sizeof(long long int));
					printf("Account balance :- %lf \n",show.balance);
					write(client_desc,&show.balance,sizeof(double));
					printf("Account type :- %c \n",show.type);
					write(client_desc,&show.type,sizeof(char));
					printf("\n");

					}
				}
				write(client_desc,"X",sizeof("X"));
				close(ofile);
				return 1;
	}

	int checkUnique(char user_name[])
	{

				int efile,k;
				struct Customer cc;
				efile=open("customer",O_RDONLY);
				while(read(efile,&cc,sizeof(cc))!=0)
				{
					if( strcmp(cc.username,user_name)==0 )
					{
						return 0;
					}

				}

				return 1;
	}

	//Add customer by Admin
	int addCustomer(int client_desc)
	{
				int b=0;
				int ifile2,c=0;
				
				
				struct Customer cust;
				printf("Enter customer details :- \n");
				
				while(c==0)
				{
				char buffer2[20];
				read(client_desc,buffer2,sizeof(buffer2));

				c=checkUnique(buffer2);
				if(!c)
				{	
					write(client_desc,&c,sizeof(int));
				}

				write(client_desc,&c,sizeof(int));
				strcpy(cust.username,buffer2);
				}		

				read(client_desc,cust.password,sizeof(cust.password));
				read(client_desc,&cust.type,sizeof(char));	
				cust.Acc_no=generateAcc_no();
				printf("Account no. :- %lli \n",cust.Acc_no);

				cust.stat=1;

				b = addAccount(client_desc,cust.Acc_no);

				ifile2=open("customer",O_WRONLY|O_APPEND);	
				ssize_t s=write(ifile2,&cust,sizeof(cust));
				close(ifile2);
				if(s>0){printf("Write Successful\n");return 1;}
				else return -1;

	}

	int addCustomer2(int client_desc , int account_no)
	{
				int ifile2,c=0;
				
				struct Customer cust;

				while(c==0)
				{
				char buffer2[20];
				read(client_desc,buffer2,sizeof(buffer2));
				c=checkUnique(buffer2);
				if(!c)
				{	
					write(client_desc,&c,sizeof(int));
				}
				write(client_desc,&c,sizeof(int));
				strcpy(cust.username,buffer2);
				}
				
				read(client_desc,cust.password,sizeof(cust.password));
				read(client_desc,&cust.type,sizeof(char));
				cust.Acc_no= account_no;
				printf("Account no. :- %lli \n",cust.Acc_no);
				cust.stat=1;
				ifile2=open("customer",O_WRONLY|O_APPEND);	
				ssize_t s=write(ifile2,&cust,sizeof(cust));
				close(ifile2);
				if(s>0){printf("Write Successful\n");return 1;}
				else return -1;
	}



 	// Search Customer using Username
	long long int custDetails(char u_name[],int client_desc)
	{			int ofile;
				int flag=0;
				long long int ano;
				ofile=open("customer",O_RDONLY);
				struct Customer c2;
				while(read(ofile,&c2,sizeof(c2))!=0)
				{
				if(strcmp(c2.username,u_name)==0)
				{
				write(client_desc,&c2,sizeof(c2));
				ano=c2.Acc_no;
				flag=1;
				break;
				}

				}

				close(ofile);

				if(flag)
					return ano;
				else
					return 0;
	}
	//Modify Customer details
	int modify_Cust(char u_name[],int client_desc)
	{
				char choice;
				int ofile;
				int chek;
				int flag=0;
				char buffer[20];
				struct Customer c2;
				ofile=open("customer",O_RDWR);
				
				while(read(ofile,&c2,sizeof(c2))!=0)
				{

				if(strcmp(c2.username,u_name)==0)
				{
				flag=1;
				break;
				}
				
				}


				if(flag)
				{
				write(client_desc,&flag,sizeof(int));
				struct Customer c5;
				write(client_desc,&c2,sizeof(c2));
				read(client_desc,&c5,sizeof(c5));
				
				chek = lseek(ofile,-sizeof(c2),SEEK_CUR);
				chek = write(ofile,&c5,sizeof(c5));
				}
				else
				{
				write(client_desc,&flag,sizeof(int));
				close(ofile);
				return 0;
				}

			close(ofile);
				return 1;
	}


	
		
	// Delete Account and Customer using Username
	int Delete_Cust(char u_name[],int client_desc)
	{
		char choice;
		int ofile;
		int chek;
		int ccc;
		int flag=0;
		struct Customer c2;
		ofile=open("customer",O_RDWR);

		while(read(ofile,&c2,sizeof(c2))!=0)
	    {

		if(strcmp(c2.username,u_name)==0)
	    {
		flag=1;
		break;
	    }
		}

		if(flag)
		{

		ccc=Delete_Account(c2.Acc_no);

		write(client_desc,&flag,sizeof(int));
		struct Customer c5;
		write(client_desc,&c2,sizeof(c2));
		read(client_desc,&c5,sizeof(c5));
		
		chek = lseek(ofile,-sizeof(c2),SEEK_CUR);
		chek = write(ofile,&c5,sizeof(c5));
		}
		else
		{
		write(client_desc,&flag,sizeof(int));
		close(ofile);
		return 0;
		}

	close(ofile);
		return 1;

	}

	// Delete Account 
	int Delete_Account(long long anumber)
	{
		char choice;
		int oofile;
		int chek;
		int flag=0;
		struct Account a1;
		oofile=open("account",O_RDWR);

		while(read(oofile,&a1,sizeof(a1))!=0)
	    {
			if(a1.Acc_no == anumber)
			    {   
			    	if(a1.type=='S')
			    	a1.astat = 0;
			    	else
			    	a1.type='S';
					flag=1;
					break;
			   }
		}
		if(flag)
		{
		chek = lseek(oofile,-sizeof(a1),SEEK_CUR);
		chek = write(oofile,&a1,sizeof(a1));
		close(oofile);
		}
		else
		{
			printf("Account no. not found\n");
			close(oofile);
		}
	 
	 return 1;

	}
	//Modify Account
	int Modify_Account(int client_desc,long long anumber,int option,int amount)
	{
		
		int ofile,tfile;
		int chek;
		double ballance;
		int flag=0;
		struct Account a1;
		ofile=open("account",O_RDWR);

		while(read(ofile,&a1,sizeof(a1))!=0)
	    {													
			if(a1.Acc_no == anumber)
			    {	
			    	if(option==1)
			    	{
			    		a1.balance = a1.balance + amount;
			    		ballance = a1.balance;

			    	}
			    	else if(option==2)
			    	{	
			    		if(amount<=a1.balance)
			    		a1.balance = a1.balance - amount;	
			    		
			    		ballance = a1.balance;
			    	}
			    	else if(option ==3)
			    	{
			    		//balance enquiry

			    	}
			    	else if(option==5)
			    	{
			    		//Transaction table for the given account no.

			    	}
			    	
					flag=1;
					break;
			   }
		}
		if(flag)
		{
		write(client_desc,&flag,sizeof(int));
		write(client_desc,&a1,sizeof(a1));
		chek = lseek(ofile,-sizeof(a1),SEEK_CUR);
		chek = write(ofile,&a1,sizeof(a1));
		close(ofile);

		if(option==1 || option == 2)
	{
		struct Transaction T;
		T.Acc_no = anumber;

		if(option==1)
		T.amount = amount;
		else if(option==2)
		T.amount = -1*amount;
		time(&T.t);
		T.balance_rem = ballance;

		tfile = open("transaction",O_WRONLY|O_APPEND);
		write(tfile,&T,sizeof(T));
		close(tfile);
	}
		}
		else
		{
			write(client_desc,&flag,sizeof(int));
			close(ofile);
			return 0;
		}

	 
	    return 1;
	}


	int change_pass(int client_desc, char u_name[],char pass[])
	{
		int ofile;
		int chek;
		int flag=0;
		struct Customer c2;
		ofile=open("customer",O_RDWR);
		
		while(read(ofile,&c2,sizeof(c2))!=0)
		{

		if(strcmp(c2.username,u_name)==0)
		{
		flag=1;
		break;
		}
		
		}

		if(flag)
		{
		strcpy(c2.password,pass);
		write(client_desc,&flag,sizeof(int));
		chek = lseek(ofile,-sizeof(c2),SEEK_CUR);
		chek = write(ofile,&c2,sizeof(c2));
		}
		else
		{
		write(client_desc,&flag,sizeof(int));
		close(ofile);
		return 0;
		}

	close(ofile);
		return 1;
	}