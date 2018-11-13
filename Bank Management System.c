#include<stdio.h>
#include<string.h>
#include<windows.h>

void menu();
void new_acc();
void save_to_file();
void view_list();
void transact();
void erase();
void see();
void close();
void edit();
int main_exit;

struct
{
    char name[60];
    int acc_no;
    char address[60];
    char ID[15];
    int phone;
    char acc_type[10];
    float amt;
    char date[15];
    char dob[15];
} add,check,rem,transaction,upd;

int main()
{
    menu();
    return 0;
}

void menu()
{
    int choice;
    system("cls");
    printf("\n\n\t\t ###### BANK MANAGEMENT SYSTEM ######");
    printf("\n\n\t\t\t##### MAIN MENU #####");
    printf("\n\n\n\n\t\t1.Create new account\t\t\n\n\t\t2.For transactions\n\n\t\t3.Check the details of an existing account\n\n\t\t4.Change information of an existing account\n\n\t\t5.Closing an account\n\n\t\t6.View customer's list\n\n\t\t7.Exit\n\n\n\n\n\t\tEnter your choice(1/2/3/4/5/6/7): ");
    scanf("%d",&choice);
    system("cls");
    switch(choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        transact();
        break;
    case 3:
        see();
        break;
    case 4:
        edit();
    case 5:
        erase();
        break;
    case 6:
        view_list();
        break;
    case 7:
        close();
        break;
    }
}

void new_acc()
{
    int choice;
    FILE *ptr;
    ptr=fopen("bank management system.txt","a+");
    system("cls");
    printf("\n\n\t\t\t OPENING NEW ACCOUNT ");
    printf("\n\n\n Enter today's date(dd/mm/yyyy): ");
    scanf("%s",add.date);
    printf("\n Enter the account number: ");
    scanf("%d",&add.acc_no);
    printf("\n Enter the name: ");
    scanf("%s",add.name);
    printf("\n Enter the date of birth(dd/mm/yyyy): ");
    scanf("%s",add.dob);
    printf("\n Enter the address: ");
    scanf("%s",add.address);
    printf("\n Enter the ID number: ");
    scanf("%s",add.ID);
    printf("\n Enter the phone number: ");
    scanf("%d",&add.phone);
    printf("\n Enter the amount to deposit: ");
    scanf("%f",&add.amt);
    printf("\n Type of account:\n\t#Saving\n\t#Current\n\t#Fixed(for 5 year)\n\n\tEnter your choice: ");
    scanf("%s",add.acc_type);
    save_to_file();
}

void save_to_file()
{
    int choice;
    FILE *ptr;
    ptr=fopen("bank management system.txt","a+");
    fprintf(ptr,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
    fclose(ptr);
    printf("\n\n\n Account created successfully!!!");
    printf("\n\n\n\t\t Enter 1 to go to the main menu and 0 to exit: ");
    scanf("%d",&main_exit);
    system("cls");
    if (main_exit==1)
        menu();
    else if(main_exit==0)
        close();
}
void transact()
{
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen("bank management system.txt","r");
    newrec=fopen("new.txt","w");
    printf("\n\t\t\t\tMONEY TRANSECTION\n\n\n\n");
    printf(" Enter the account no. of the customer: ");
    scanf("%d",&transaction.acc_no);
    while (fscanf(old,"%d %s %s %s %s %d %s %f %s",&add.acc_no,add.name,add.date,add.address,add.ID,&add.phone,add.acc_type,&add.amt,add.dob)!=EOF)
    {
        if(transaction.acc_no==add.acc_no)
        {
            test=1;
            if(strcmpi(add.acc_type,"fixed1")==0)
            {
                printf("\n\n YOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                system("cls");
                menu();
            }
            printf("\n\n Do you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1/2): ");
            scanf("%d",&choice);
            if (choice==1)
            {
                printf("\n Enter the amount you want to deposit: ");
                scanf("%f",&transaction.amt);
                add.amt+=transaction.amt;
                fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
                printf("\n\n Deposit successful!!!");
                printf("\n\n Your available balance: %.2f\n\n",add.amt);
            }
            else
            {
                printf("\n Enter the amount you want to withdraw: ");
                scanf("%f",&transaction.amt);
                add.amt-=transaction.amt;
                fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
                printf("\n\n Withdraw successful!!!");
                printf("\n\n Your available balance: %.2f\n\n",add.amt);
            }
        }
        else
        {
            fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("bank management system.txt");
    rename("new.txt","bank management system.txt");
    if(test!=1)
    {
        printf("\n\n Record not found!!!");
        printf("\n\n\n Enter 0 to try again,1 to return to main menu and 2 to exit: ");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==0)
            transact();
        else if (main_exit==1)
            menu();
        else if (main_exit==2)
            close();
    }
    else
    {
        printf("\n\n Enter 1 to go to the main menu and 0 to exit: ");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
    }
}

void view_list()
{
    FILE *view;
    view=fopen("bank management system.txt","r");
    int test=0;
    system("cls");
    printf("\n\n\t\t\tCUSTOMER'S LIST");
    printf("\n ACC. NO.\t NAME\t\t\tADDRESS\t\t\tPHONE\n");
    while(fscanf(view,"%d %s %s %s %s %d %s %f %s",&add.acc_no,add.name,add.dob,add.address,add.ID,&add.phone,add.acc_type,&add.amt,add.date)!=EOF)
    {
        printf("\n %d\t\t %s\t\t\t%s\t\t\t%d",add.acc_no,add.name,add.address,add.phone);
        test++;
    }
    fclose(view);
    if (test==0)
    {
        system("cls");
        printf("\n\n NO RECORDS!!!\n");
    }
    printf("\n\n Enter 1 to go to the main menu and 0 to exit: ");
    scanf("%d",&main_exit);
    system("cls");
    if (main_exit==1)
        menu();
    else if(main_exit==0)
        close();
}

void erase()
{
    FILE *old,*newrec;
    int test=0;
    old=fopen("bank management system.txt","r");
    newrec=fopen("new.txt","w");
    printf("\n\t\t\tCLOSING an ACCOUNT\n\n");
    printf("\n\n Enter the account no. of the customer you want to delete: ");
    scanf("%d",&rem.acc_no);
    while (fscanf(old,"%d %s %s %s %s %d %s %f %s",&add.acc_no,add.name,add.dob,add.address,add.ID,&add.phone,add.acc_type,&add.amt,add.date)!=EOF)
    {
        if(rem.acc_no!=add.acc_no)
            fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
        else
        {
            test=1;
            printf("\n\n Record deleted successfully!!!\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("bank management system.txt");
    rename("new.txt","bank management system.txt");
    if(test==0)
    {
        printf("\n\n Record not found!!!");
        printf("\n\n Enter 0 to try again,1 to return to main menu and 2 to exit: ");
        scanf("%d",&main_exit);
        if (main_exit==1)
            menu();
        else if (main_exit==2)
            close();
        else if(main_exit==0)
            erase();
    }
    else
    {
        printf("\n\n Enter 1 to go to the main menu and 0 to exit: ");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
    }
}

void see()
{
    system("color 6");
    FILE *ptr;
    int test=0,rate;
    int choice;
    float time;
    float intrst;
    ptr=fopen("bank management system.txt","r");
    printf("\n\n\t\t\tACCOUNT INFORMATION");
    printf("\n\n Do you want to check by\n\n1.Account no\n\n2.Name\n\n\n\nEnter your choice: ");
    scanf("%d",&choice);
    if (choice==1)
    {
        printf(" Enter the account number: ");
        scanf("%d",&check.acc_no);
        while (fscanf(ptr,"%d %s %s %s %s %d %s %f %s",&add.acc_no,add.name,add.dob,add.address,add.ID,&add.phone,add.acc_type,&add.amt,add.date)!=EOF)
        {
            if(check.acc_no==add.acc_no)
            {
                system("cls");
                test=1;
                printf("\n\n Account NO.: %d\n\n Name:%s \n\n Date of birth: %s \n\n Address: %s \n\nID No:%s \n\n Phone number: %d \n\n Type Of Account: %s \n\n Current balance: %.2f \n\n Opening account date: %s\n\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,
                       add.acc_type,add.amt,add.date);
            }
        }
    }
    else if (choice==2)
    {
        printf("\n Enter the name: ");
        scanf("%s",&check.name);
        while (fscanf(ptr,"%d %s %s %s %s %d %s %f %s",&add.acc_no,add.name,add.dob,add.address,add.ID,&add.phone,add.acc_type,&add.amt,add.date)!=EOF)
        {
            if(strcmpi(add.name,check.name)==0)
            {
                system("cls");
                test=1;
                printf("\n\n Account NO.: %d\n\n Name:%s \n\n Date of birth: %s \n\n Address: %s \n\n ID No:%s \n\n Phone number: %d \n\n Type Of Account: %s \n\n Current balance: %.2f \n\n Opening account date : %s\n\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,
                       add.acc_type,add.amt,add.date);
            }
        }
    }
    fclose(ptr);
    if(test!=1)
    {
        system("cls");
        printf("\n\n Record not found!!!");
        printf("\n\n Enter 0 to try again,1 to return to main menu and 2 to exit: ");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else if (main_exit==2)
            close();
        else if(main_exit==0)
            see();
    }
    else
    {
        printf("\n\n Enter 1 to go to the main menu and 0 to exit: ");
        scanf("%d",&main_exit);
    }
    if (main_exit==1)
    {
        system("cls");
        menu();
    }
    else
    {
        system("cls");
        close();
    }
}

void close()
{
    system("color FC");
    printf("\n\n\t\t\tCODE BY TANZIM & SAIDUR\n\n");
}
void edit()
{
    system("color 9");
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen("bank management system.txt","r");
    newrec=fopen("new.txt","w");
    printf("\n\t\t\tUpdate Account Information");

    printf("\n\n\n Enter the account no. of the customer whose info you want to change:");
    scanf("%d",&upd.acc_no);
    while(fscanf(old,"%d %s %s %s %s %d %s %f %s",&add.acc_no,add.name,add.dob,add.address,add.ID,&add.phone,add.acc_type,&add.amt,add.date)!=EOF)
    {
        if (add.acc_no==upd.acc_no)
        {
            test=1;
            printf("\n Which information do you want to change?\n 1. Name\n 2. Address\n 3. Phone\n\n Enter your choice(1/2/3): ");
            scanf("%d",&choice);
            system("cls");
            if(choice==1)
            {
                printf("\n\n Enter the new name: ");
                scanf("%s",upd.name);
                fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,upd.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
                system("cls");
                printf("Changes saved!");
            }
            else if(choice==2)
            {
                printf("\n\n Enter the new address: ");
                scanf("%s",upd.address);
                fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,upd.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
                system("cls");
                printf("Changes saved!");
            }
            else if(choice==3)
            {
                printf("\n\n Enter the new phone number: ");
                scanf("%d",&upd.phone);
                fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,upd.phone,add.acc_type,add.amt,add.date);
                system("cls");
                printf("Changes saved!");
            }

        }
        else
            fprintf(newrec,"%d %s %s %s %s %d %s %f %s\n",add.acc_no,add.name,add.dob,add.address,add.ID,add.phone,add.acc_type,add.amt,add.date);
    }
    fclose(old);
    fclose(newrec);
    remove("bank management system.txt");
    rename("new.txt","bank management system.txt");
    if(test!=1)
    {
        system("cls");
        printf("\n\n Record not found!!!");
        printf("\n\n Enter 0 to try again,1 to return to main menu and 2 to exit: ");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)

            menu();
        else if (main_exit==2)
            close();
        else if(main_exit==0)
            edit();
    }
    else
    {
        printf("\n\n\n Enter 1 to go to the main menu and 0 to exit: ");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
    }
}
