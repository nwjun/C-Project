#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void acc_details();
void option();
void input();
int compare();
int acc_valid();

void create();
void display();
void search();
void deposit();
void withdraw();
void delete_acc();

typedef struct
{
    char acc_num[20];
    char name[20];
    char bank[50];
    double balance;
}acc_type;

acc_type account[20];

int num = 0;

int main(void)
{
    option();
    input();

    return 0;
}

void option(void)
{
    printf("***** Welcome to Bank Application *****\n");
    printf("\nPress 0 to create a new account\n");
    printf("Press 1 to display all records.\n");
    printf("Press 2 to search a record.\n");
    printf("Press 3 to deposit amount.\n");
    printf("Press 4 to withdraw amount.\n");
    printf("Press 5 to delete an account\n");
    printf("Press 6 to exit\n");
}

void input(void)
{
    int opt, result;

//validate input: only allowed number between 0-6
    do
    {
        printf("\nEnter choice(0-6): ");
        result = scanf("%d", &opt);

        if(result == 0)
            fflush(stdin);

    }while(result != 1 ||opt < 0 || opt > 6);

    switch(opt)
    {
        case 0: create(); break;
        case 1: display(); break;
        case 2: search(); break;
        case 3: deposit(); break;
        case 4: withdraw(); break;
        case 5: delete_acc(); break;
        case 6: return 0; break;
    }

    option();
    input();
}

void create(void)
{
    char acc_num[20];
    int result;

    printf("\nEnter account number      : ");
    scanf("%s", acc_num);

    if(acc_valid(acc_num) == -1){

        strcpy(account[num].acc_num, acc_num);

        printf("Enter account holder name : ");
        scanf("%s", account[num].name);
        printf("Enter account bank        : ");
        scanf("%s", account[num].bank);


//validate input: only allowed number
        do
        {
            printf("Enter account balance     : ");
            result= scanf("%lf", &account[num].balance);

            if(result==0)
                fflush(stdin);


        }while(result != 1);

        printf("\n\n***** Account Details *****\n\n");
        printf("Account number      : %s\n",account[num].acc_num);
        printf("Account holder name : %s\n",account[num].name);
        printf("Account bank        : %s\n",account[num].bank);
        printf("Account balance     : %.2lf\n\n",account[num].balance);

        ++num;

        qsort(account, num, sizeof(acc_type), compare);
    }

    else
        printf("Account already existed!\n\n");
}

void display(void){
    if(num <= 0)
        printf("\nNo account found.\n\n");


    else
    {
        printf("\n\n***** Account Details *****\n");

        for(int n=0; n<num; n++)
        {
            acc_details(n);
        }
    }
}

void search(void)
{
    char acc_num[20];
    int n;

    if(num == 0)
    {
        printf("No account added!\n");
    }

    else
    {
        printf("\nEnter account number      : ");
        scanf("%s", acc_num);

        n = acc_valid(acc_num);

        if(n== -1)
            printf("Account not found!");

        else
        {
            acc_details(n);
        }
    }
}

void deposit(void)
{
    char n[20];
    int result, acc;
    double money = 0;

    if(num <= 0)
    {
        printf("\nNo account found.\n\n");
    }

    else{
        printf("\nEnter account number: ");
        scanf("%s", n);

        acc = acc_valid(n);

        if(acc == -1)
            printf("Account not found!\n");

        else
        {
            //validate input
            do
            {
                printf("Deposit: ");
                result= scanf("%lf", &money);

                if(result==0)
                    fflush(stdin);

            }while(result != 1);

            account[acc].balance += money;
            acc_details(acc);
        }
    }
}

void withdraw(void)
{
    char n[20];
    int result, acc;
    double money = 0;

    if(num <= 0)
    {
        printf("\nNo account found.\n\n");
    }

    else
    {
        printf("\nEnter account number: ");
        scanf("%s", n);

        acc = acc_valid(n);

        if(acc == -1)
            printf("Account not found!\n");

        else
        {
            //validate input
            do
            {
                printf("Withdraw: ");
                result= scanf("%lf", &money);

                if(result==0)
                    fflush(stdin);

            }while(result != 1);

            if(account[acc].balance < money)
                printf("Insufficient balance!\n");


            else
                account[acc].balance -= money;

            acc_details(acc);
        }
    }
}

void delete_acc(void)
{
    char acc_num[20];
    int n;

    if(num <= 0)
    {
        printf("\nNo account found.\n\n");
    }

    else
    {
        printf("\nEnter account number you wish to delete:");
        scanf("%s", acc_num);

        n = acc_valid(acc_num);

        if(n == -1){
            printf("Invalid account number!\n");
        }

        else
        {
            //copy n+1 details to n
            if(num != 1)
            {
                for(; n < (num - 1); n++)
                {
                    strcpy(account[n].acc_num, account[n+1].acc_num);
                    strcpy(account[n].name, account[n+1].name);
                    strcpy(account[n].bank, account[n+1].bank);
                    account[n].balance = account[n+1].balance;
                }
            }

            //clear last

            --num;
        }
    }
}


int acc_valid(char* acc_num)
{

    for(int n = 0; n < num; n++)
    {
        if(strcasecmp(acc_num, account[n].acc_num) == 0)
            return n;
    }

    return -1;
}

void acc_details(int n)
{
    printf("\nAccount %2d          :\n", n + 1);
    printf("Account number      : %s\n",account[n].acc_num);
    printf("Account holder name : %s\n",account[n].name);
    printf("Account bank        :%s\n",account[n].bank);
    printf("Account balance     : %.2lf\n\n\n",account[n].balance);
}

int compare(const void *p, const void *q)
{
    acc_type *a = (acc_type *)p, *b = (acc_type *)q;

    return strcmp(a->acc_num,b->acc_num);
}
