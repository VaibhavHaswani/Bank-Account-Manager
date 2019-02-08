#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
int opt,o;
struct {
	char name[30];
	long ID;
	long Num;
	int pin,age,fund;
}dat;
long size=sizeof(dat);
void delay(void);
int menu(void);
void atm(void);
void openAcc(void);
void deposit(void);
void checkBal(void);
void rmAcc(void);
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int main()
{
	
	o=menu();
	system("cls");
	switch(o)
	{
		case 1: atm(); 
		case 2: openAcc();
		case 3: deposit();
		case 4: checkBal();
		case 5: rmAcc();
		case 6: exit(2);
	}
	return 0;
}
 int menu() //main menu
 {
 	gotoxy(50,2);
 	printf("~ BANK ACCOUNT MANAGER ~");
 	gotoxy(70,4);
 	printf("BY- Vaibhav Haswani");
 	gotoxy(42,8);
 	printf("1>> ATM service");
 	gotoxy(42,10);
 	printf("2>> Open a bank account");
 	gotoxy(42,12);
 	printf("3>> Deposit Funds");
 	gotoxy(42,14);
 	printf("4>> Check balance");
 	gotoxy(42,16);
 	printf("5>> Close Account");
 	gotoxy(42,18);
 	printf("6>> Exit");
 	gotoxy(42,24);
 	printf("Choose option:");
 	scanf("%d",&opt);
 	return opt;
 }
 
 
 
 void atm()   // money withdraw service
 {
 	long accno;
 	char ch,ch1;
 	int pin,amount;
 	FILE *fp;
 	printf("Enter A/c no.:");
 	scanf("%d",&accno);
 	fp=fopen("bankdata.dat","rb+");
 	while(fread(&dat,size,1,fp)==1)
 	{
 		if(accno==dat.ID)
 		{
 		while(1)
  		{
  		printf("Enter pin:");
  		scanf("%d",&pin);
  		if(pin==dat.pin)
  		 {
  		printf("Your Available balance is: Rs %d\n",dat.fund);
  		printf("Enter Amount to withdraw:");
  		scanf("%d",&amount);
  		printf("Your Transcation is in process....\n");
  		dat.fund=dat.fund-amount;
  		delay();
  		printf("Please, collect the cash of Rs.%d\n",amount);
  		printf("Your available balance is- Rs.%d\n",dat.fund);
  		fseek(fp,-size,SEEK_CUR);
  		fwrite(&dat,size,1,fp);
  		fclose(fp);
  		break;
		 }
		  else
		  {
		  	printf("PIN not correct..\n");
		  	printf("Try again?(y/n)\n");
		  	ch=getch();
		  	if(ch=='y'||ch=='Y'){
		  		continue;
			  }
			  else{
			  	fclose(fp);
			  	break;
			    }
		  	
		  }
		  
	    }
 			
		}
	 }
	 
  printf("Continue to main menu?(y/n)");
  ch1=getch();
  if(ch1=='y'||ch1=='Y')
  {
  	system("cls");
  main();
  }
  else 
  exit(2);
 	
 }
 
 
 
 void openAcc()  //adding account
 {

 	FILE *fp,*fb;
 	fp=fopen("bankdata.dat","ab+");
 	if(fp==NULL)
 	{
 		fp=fopen("bankdata.dat","wb+");
	}
	printf("ENTER NAME:");
	scanf(" %[^\n]s",dat.name);
	printf("ENTER AGE(min age should be 18):");
	scanf("%d",&dat.age);
	if(dat.age<18)
	{
		printf("You are not eligible..");
		fclose(fp);
		exit(1);
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	printf("ENTER YOR MOBILE NO:");
	scanf("%d",&dat.Num);
	printf("Choose pin:");
	scanf("%d",&dat.pin);
	
	printf("Generating Bank ID...\n");
	fb=fopen("bid.dat","rb");
	if(fb==NULL)
	{
		fb=fopen("bid.dat","wb");
		long bnkid=1927820000;
		dat.ID=bnkid;
		fwrite(&bnkid,sizeof(bnkid),1,fb);
		fclose(fb);
	}
	else
	{
		long bnkid;
		fread(&bnkid,sizeof(bnkid),1,fb);
		bnkid++;
		dat.ID=bnkid;
		fclose(fb);
		fb=fopen("bid.dat","wb");
		fwrite(&bnkid,sizeof(bnkid),1,fb);
		fclose(fb);
	}
	delay();
	printf("Your BANK ID is:%d\n",dat.ID);
	printf("Deposit Funds (RS.1500 should be the minimum deposit of funds):");
	do{
		scanf("%d",&dat.fund);
		if(dat.fund<1500)
		printf("(Deposit min funds upto Rs1500):");
	}while(dat.fund<1500);
	fwrite(&dat,size,1,fp);
	fclose(fp);
	printf("~~ Account created successfully ~~\nThank You for joining Us..");
	delay();
	system("cls");
	main();	
 }
 
 
 
 
 
 
void deposit()   //money deposit fn
{
	FILE *fp;
    char ch;
	long bnkid;
	int fund;
	printf("ENTER Account No.:");
	scanf("%ld",&bnkid);
	fp=fopen("bankdata.dat","rb+");
	while(fread(&dat,size,1,fp)==1)
	{
		if(bnkid==dat.ID)
		{
			printf("Account data found...\n");
			printf("Deposit funds(Rs):");
			scanf("%d",&fund);
			dat.fund=dat.fund+fund;
			fseek(fp,-size,SEEK_CUR);
			fwrite(&dat,size,1,fp);
			printf("Funds Added Successfully..\n");
			fclose(fp);
			break;
		}
	}
	  printf("Continue to main menu?(y/n)");
  ch=getch();
  if(ch=='y'||ch=='Y')
  {
  	system("cls");
  main();
  }
  else 
  exit(3);
}






void checkBal() // check balance fn
{
  FILE *fp;
  char ch,ch1;
  int pin;
  long acid;
  printf("ENTER A/c number:");
  scanf("%ld",&acid);
  fp=fopen("bankdata.dat","rb");
  while(fread(&dat,size,1,fp)==1)
  {
  	if(acid==dat.ID)
  	{
  		while(1)
  		{
  		printf("Enter pin:");
  		scanf("%d",&pin);
  		if(pin==dat.pin)
  		 {
  		printf("Your A/c balance is: Rs %d\n",dat.fund);
  		fclose(fp);
  		break;
		  }
		  else
		  {
		  	printf("PIN not correct..\n");
		  	printf("Try again?(y/n)\n");
		  	ch=getch();
		  	if(ch=='y'||ch=='Y'){
		  		continue;
			  }
			  else{
			  	fclose(fp);
			  	break;
			    }
		  	
		  }
		  
	    }
	}
	
  }
  printf("Continue to main menu?(y/n)");
  ch1=getch();
  if(ch1=='y'||ch1=='Y')
  {
  	system("cls");
  main();
  }
  else 
  exit(2);
  
}


void rmAcc()
{
 FILE *fp,*ft;
  char ch,ch1,ch2;
  int pin;
  long acid;
  printf("ENTER A/c number:");
  scanf("%ld",&acid);
  fp=fopen("bankdata.dat","rb");
  while(fread(&dat,size,1,fp)==1)
  {
  	if(acid==dat.ID)
  	{
  		while(1)
  		{
  		printf("Enter pin:");
  		scanf("%d",&pin);
  		if(pin==dat.pin)
  		 {
  		 	printf("Are you sure you want to continue? (y/n)\n");
  		 	ch2=getch();
  		 	if(ch2=='y'||ch2=='Y')
  		 	{
  		 		rewind(fp);
  		 		ft=fopen("temp.dat","wb");
  		 		while(fread(&dat,size,1,fp)==1)
  		 		{
  		 		if(acid!=dat.ID)
  		 		fwrite(&dat,size,1,ft);
  		 	    }
  		 	    fclose(ft);
  		 	    fclose(fp);
  		 	    remove("bankdata.dat");
  		 	    rename("temp.dat","bankdata.dat");
  		 	    printf("Account deleted Successfully..");
  		 	    break;
  		 	    
  		 	}
  		 	else
  		 	break;
		    }
		  else
		  {
		  	printf("PIN not correct..\n");
		  	printf("Try again?(y/n)\n");
		  	ch=getch();
		  	if(ch=='y'||ch=='Y'){
		  		continue;
			  }
			  else{
			  	fclose(fp);
			  	break;
			    }
		  	
		  }
		  
	    }
	}
	
  }
  printf("Continue to main menu?(y/n)");
  ch1=getch();
  if(ch1=='y'||ch1=='Y')
  {
  	system("cls");
  main();
  }
  else 
  exit(2);
  
	
}









void delay(void)
{
int a,b;
for(a=1;a<36750;a++)
{
for(b=1;b<36750;b++)
{
	
}
}	
}
