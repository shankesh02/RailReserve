#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{              /*Structure*/
	char name[50];
	int age;
	char gender[10];
	long long int cno;
	int train_no;
	int no_of_passengers;
}resinfo;

void login();               /*Function declaration*/
void reservation(void);
float charge(int,int);
void viewtrains(void);
void printticket(char name[],int,char gender[],long long int,int,int,float);
char train(int);
void display();
void cancellation(void);

int main()
{
    system("cls");
	printf("\t\t*******************************************************\n");
	printf("\t\t|                                                     |\n");
	printf("\t\t|         -----------------------------------         |\n");
	printf("\t\t|           TRAIN TICKET RESERVATION SYSTEM           |\n");
	printf("\t\t|         -----------------------------------         |\n");
	printf("\t\t|                                                     |\n");
	printf("\t\t*******************************************************\n\n\n");
    printf(" \n Press any key to continue...");
    getch();
    system("cls");
	login();
	int mc;
	start:
	system("cls");
	printf("\n|=================================|\n");
	printf("|   TRAIN RESERVATION SYSTEM      |");
	printf("\n|=================================|");
	printf("\n|1>> Reserve A Ticket             |");
	printf("\n|---------------------------------|");
	printf("\n|2>> View All Available Trains    |");
	printf("\n|---------------------------------|");
	printf("\n|3>> Cancel Reservation           |");
	printf("\n|---------------------------------|");
	printf("\n|4>> Display File                 |");
	printf("\n|---------------------------------|");
	printf("\n|5>> Exit                         |");
	printf("\n|---------------------------------|");
	printf("\n\n-->");
	scanf("%d",&mc);
	switch(mc)
	{
		case 1:
			reservation();
			break;
		case 2:
			viewtrains();
			printf("\n\nPress any key to go back to main menu...");
			getch();
			break;
		case 3:
			cancellation();
			break;
        case 4:
            display();
            break;
		case 5:
			return(0);
		default:
			printf("\nInvalid Choice...");
			getch();
	}
    goto start;
	return(0);
}

void login()                       /*Login function*/
{
    int a=0,i=0,log=0;
    char uname[15],c=' ',pword[15];
    login1:
    system("cls");
    printf("\n\n1.For new login\n2.For existing login");
    printf("\n\nEnter your choice: ");
    scanf("%d",&log);
    switch(log)
    {
        case 1:
            {
                FILE *fl;
                fl=fopen("Login.txt","a");
                printf("\n  *************************  LOGIN  *************************\n  ");
                printf(" \n                 ENTER USERNAME:-");
                scanf("%s", &uname);
                printf(" \n                 ENTER PASSWORD:-");
                while(i<15)
                {
                    pword[i]=getch();
                    c=pword[i];
                    if(c==13)
                        break;
                    else
                        printf("*");
                    i++;
                }
                pword[i]='\0';
                i=0;
                fprintf(fl,"username:%s\t\t password: %s\n",uname,pword);
                fclose(fl);
                printf("  \n\n\n    WELCOME TO OUR RAILWAYS TICKET BOOKING SYSTEM ! \n\tYOUR LOGIN IS SUCCESSFUL !");
                printf("\n\n\n\t\tPress any key to continue...");
                getch();
                break;
            }

        case 2:
            {
                int z=0;
                char user[15],cn=' ',pwd[15];
                FILE *fr;
                fr=fopen("Login.txt","r");
                printf("\n  *************************  LOGIN  *************************\n  ");
                printf(" \n                 ENTER USERNAME:-");
                scanf("%s", &user);
                printf(" \n                 ENTER PASSWORD:-");
                while(z<15)
                {
                    pwd[z]=getch();
                    cn=pwd[z];
                    if(cn==13)
                        break;
                    else
                        printf("*");
                    z++;
                }
                pwd[z]='\0';
                z=0;
                while(fscanf(fr,"username:%s\t\t password: %s\n",&uname,&pword)!= EOF)
                {
                    if(strcmp(user,uname)==0 && strcmp(pwd,pword)==0)
                    {
                        printf("  \n\n\n    WELCOME TO OUR RAILWAYS TICKET BOOKING SYSTEM ! \n\tYOUR LOGIN IS SUCCESSFUL !");
                        printf("\n\n\n\t\tPress any key to continue...");
                        getch();
                        break;
                    }
                    else
                    {
                        printf("\n\t\tPlease sign up first!");
                    }
                }
                fclose(fr);
                break;
            }
        default:
            {
                printf("\n\t\tInvalid Choice!");
                getch();
                goto login1;
            }
    }
    system("cls");
}

void reservation(void)              /*Reservation function*/
{
	char confirm;
	float charges;
    resinfo rs;
	FILE *fp,*p;
	fp=fopen("Reserved.txt","a");
	p=fopen("Res.txt","a");
	system("cls");
    printf("\nEnter your name:> ");
	fflush(stdin);
	scanf("%[^\n]",&rs.name);
	printf("\nEnter your age:> ");
	scanf("%d",&rs.age);
	printf("\nEnter your gender (Male/Female):> ");
	scanf("%s",&rs.gender);
	printf("\nEnter you mobile number:> ");
	scanf("%lld",&rs.cno);
	printf("\nEnter number of passengers:> ");
	scanf("%d",&rs.no_of_passengers);
	printf("\n\n>>Press enter to view available trains<< ");
	getch();
	system("cls");
	viewtrains();
	printf("\n\nEnter train number:> ");
	start1:
	scanf("%d",&rs.train_no);
	if(rs.train_no>=22370 && rs.train_no<=22379)
	{
		charges=charge(rs.train_no,rs.no_of_passengers);
		printticket(rs.name,rs.age,rs.gender,rs.cno,rs.no_of_passengers,rs.train_no,charges);
	}
	else
	{
		printf("\nInvalid Train Number!\nEnter again--> ");
		goto start1;
	}
    start:
	printf("\n\nConfirm Ticket (y/n):> ");
	scanf(" %c",&confirm);
	if(confirm=='y')
	{
		fprintf(fp,"\nName: %s\t\tAge: %d\t\tGender: %s\t\tMobile No.: %lld\t\tNo. of Passengers: %d\t\tTrain No.: %d\t\tCost: %.2f\t\t(BOOKED)",rs.name,rs.age,rs.gender,rs.cno,rs.no_of_passengers,rs.train_no,charges);
		fprintf(p,"Name: %s\t\tAge: %d\t\tGender: %s\t\tMobile no.: %lld\t\tTrain no.: %d\t\tNo. of Passengers: %d\n",rs.name,rs.age,rs.gender,rs.cno,rs.train_no,rs.no_of_passengers);
		printf("******************");
		printf("\n Reservation Done\n");
		printf("******************");
		printf("\nPress any key to go back to main menu...");
	}
	else
	{
		if(confirm=='n')
        {
			printf("\nReservation Not Done!\nPress any key to go back to  main menu...");
		}
		else
		{
			printf("\nInvalid choice entered! ");
			goto start;
		}
	}
	fclose(fp);
	fclose(p);
    getch();
}

void viewtrains(void)                 /*Viewtrains function*/
{
	system("cls");
	printf("-------------------------------------------------------------------------------------------------");
	printf("\nTr.No\tName\t\t\tDestination\t\t\t\tCharges\t\tTime\n");
	printf("-------------------------------------------------------------------------------------------------");
	printf("\n22370\tCharminar Express\tTambaram to Hyderabad\t\t\tRs.2000\t\t09:00 am");
	printf("\n22371\tDeccan Express\t\tMumbai To Pune\t\t\t\tRs.1000\t\t12:00 pm");
	printf("\n22372\tGoa Express\t\tVasco da Gama To Hazrat Nizamuddin\tRs.1500\t\t08:00 am");
	printf("\n22373\tKarnataka Express\tBangalore To New Delhi\t\t\tRs.2500\t\t11:00 am");
	printf("\n22374\tKovai Express\t\tCoimbatore To Chennai\t\t\tRs.1000\t\t07:00 am");
	printf("\n22375\tMalgudi Express\t\tMysore To Yeshwantpur Junction\t\tRs.1700\t\t09:30 am");
    printf("\n22376\tRajdhani Express\tNew Delhi To Bangalore\t\t\tRs.2500\t\t13:00 pm");
    printf("\n22377\tRajdhani Express\tNew Delhi To Patna\t\t\tRs.1500\t\t16:00 pm");
    printf("\n22378\tSangamithra Express\tBangalore To Patna\t\t\tRs.2000\t\t15:35 pm");
    printf("\n22379\tYoga Express\t\tAhmedabad To Haridwar\t\t\tRs.3000\t\t16:15 pm");
}

float charge(int train_no,int no_of_passengers)             /*Charges function*/
{
    if (train_no==22370)
	{
		return(2000.0*no_of_passengers);
	}
	if (train_no==22371)
	{
		return(1000.0*no_of_passengers);
	}
	if (train_no==22372)
	{
		return(1500.0*no_of_passengers);
	}
	if (train_no==22373)
	{
		return(2500.0*no_of_passengers);
	}
	if (train_no==22374)
	{
		return(1000.0*no_of_passengers);
	}
	if (train_no==22375)
	{
		return(1700.0*no_of_passengers);
	}
	if (train_no==22376)
	{
		return(2500.0*no_of_passengers);
	}
	if (train_no==22377)
	{
		return(1500.0*no_of_passengers);
	}
	if (train_no==22378)
	{
		return(2000.0*no_of_passengers);
	}
	if (train_no==22379)
	{
		return(3000.0*no_of_passengers);
	}
}

void printticket(char name[],int age,char gender[],long long int cno,int no_of_passengers,int train_no,float charges)       /*Printticket function*/
{
	system("cls");
	printf("-----------------------------------------------------------\n");
	printf("\t\t\t  TICKET\n");
	printf("-----------------------------------------------------------\n\n");
	printf("Name:\t\t\t%s",name);
	printf("\nAge:\t\t\t%d",age);
	printf("\nGender:\t\t\t%s",gender);
	printf("\nMobile Number:\t\t%lld",cno);
	printf("\nNumber Of Passengers:\t%d",no_of_passengers);
	printf("\nTrain Number:\t\t%d",train_no);
	train(train_no);
	printf("\nCharges:\t\t%.2f",charges);
}

char train(int train_no)                                                    /*Train function*/
{
    if (train_no==22370)
	{
		printf("\nTrain:\t\t\tCharminar Express");
		printf("\nDestination:\t\tTambaram to Hyderabad");
		printf("\nDeparture:\t\t9 am ");
	}
	if (train_no==22371)
	{
		printf("\nTrain:\t\t\tDeccan Express");
		printf("\nDestination:\t\tMumbai To Pune");
		printf("\nDeparture:\t\t12 pm");
	}
	if (train_no==22372)
	{
		printf("\nTrain:\t\t\tGoa Express");
		printf("\nDestination:\t\tVasco da Gama To Hazrat Nizamuddin");
		printf("\nDeparture:\t\t8 am");
	}
	if (train_no==22373)
	{
		printf("\nTrain:\t\t\tKarnataka Express");
		printf("\nDestination:\t\tBangalore To New Delhi");
		printf("\nDeparture:\t\t11 am ");
	}
	if (train_no==22374)
	{
		printf("\nTrain:\t\t\tKovai Express");
		printf("\nDestination:\t\tCoimbatore to Chennai");
		printf("\nDeparture:\t\t7 am");
	}
	if (train_no==22375)
	{
		printf("\ntrain:\t\t\tMalgudi Express");
		printf("\nDestination:\t\tMysore To Yeshwantpur Junction");
		printf("\nDeparture:\t\t9:30 am ");
	}
	if (train_no==22376)
	{
		printf("\ntrain:\t\t\tRajdhani Express");
		printf("\nDestination:\t\tNew Delhi To Bangalore");
		printf("\nDeparture:\t\t13 pm ");
	}
	if (train_no==22377)
	{
		printf("\ntrain:\t\t\tRajdhani Express");
		printf("\n Destination:\t\tNew Delhi To Patna");
		printf("\nDeparture:\t\t16 pm ");
	}
	if (train_no==22378)
	{
		printf("\ntrain:\t\t\tSangamithra Express");
		printf("\nDestination:\t\tBangalore to Patna");
		printf("\nDeparture:\t\t15:35 pm ");
	}
	if (train_no==22379)
	{
		printf("\ntrain:\t\t\tYoga Express");
		printf("\nDestination:\t\tAhmedabad To Haridwar");
		printf("\nDeparture:\t\t16:15 pm");
	}
}

void cancellation()                                    /*Cancellation function*/
{
	resinfo rs;
	FILE *t,*k,*s;
	t=fopen("Reserved.txt","r");
	k=fopen("Reserved.txt","a");
	s=fopen("Res.txt","r");
	if (t==NULL)
	{
		printf("\n\t\t  NO RECORD ADDED!");
	}
	else
    {
        system("cls");
        int trainnum,np;
        long long int mno;
        printf("\nEnter your mobile no.:> ");
        scanf("%lld",&mno);
        printf("\nEnter the train no.:> ");
        scanf("%d",&trainnum);
        printf("\nEnter the number of tickets reserved:> ");
        scanf("%d",&np);
        while(fscanf(s,"Name: %s\t\tAge: %d\t\tGender: %s\t\tMobile no.: %lld\t\tTrain no.: %d\t\tNo. of Passengers: %d\n",&rs.name,&rs.age,&rs.gender,&rs.cno,&rs.train_no,&rs.no_of_passengers)!=EOF)
        {
            if(mno==rs.cno && trainnum==rs.train_no && np==rs.no_of_passengers)
            {
                printf("\n\nYour Ticket Has Been Cancelled!");
                fprintf(k,"\nName: %s\t\tAge: %d\t\tGender: %s\t\tMobile No.: %lld\t\tNo. of Passengers: %d\t\tTrain No.: %d\t\t(CANCELLED)",&rs.name,rs.age,rs.gender,rs.cno,rs.no_of_passengers,rs.train_no);
                printf("\n\n\tPress any key to go back to main menu...");
            }
            getch();
        }
    }
    fclose(t);
    fclose(k);
    fclose(s);
}

void display()                      /*Display function*/
{
    char ch;
	FILE *ptr;
	ptr=fopen("Reserved.txt","r");
	if(ptr==NULL)
    {
        printf("\n\t\t  NO RECORD ADDED!");
    }
    else
    {
        printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t    FILE");
        printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        do
        {
            ch=fgetc(ptr);
            putchar(ch);
        }while(ch!=EOF);
    }
    fclose(ptr);
    printf("\n\n\t\tPress any key to go back to main menu...");
    getch();
}
