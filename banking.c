#include <stdio.h>
#include <stdlib.h>
#define Cmax 50
#define max_clients 20
#define max_accounts 20

typedef struct client {
    int id_cli;
    char name[Cmax];
    char lastname[Cmax];
} client;

typedef struct date {
    int day;
    int month;
    int year;
} date;

typedef struct account {
    int id_acc;
    int id_cli;
    date d_acc;
} account;

client clients[max_clients];
account accounts[max_accounts];
int choice;

void main_menu(void);
int sec_menu(int a);
void manage_client(int a);
void manage_account(int a);
void manage_transactions(int a);


int main(void)
{
    main_menu();
    sec_menu(choice);
}


void main_menu(void)
{
    printf("1- Manage clients \n");
    printf("2- Manage accounts \n");
    printf("3- Manage operations \n");
    printf("4- Exit \n");
    printf("Choose a menu: ");
    scanf("%i", &choice);

}

int sec_menu(int a)
{
    int ans;
    if (a == 1)
    {
        printf("\n 1- Add client \n");
        printf(" 2- Edit client \n");
        printf(" 3- Delete Clients \n");
        printf(" 4- Clients display \n");
        printf(" 5- Previous page \n");
        printf(" Choose a secondary menu: ");
        scanf("%i", &ans);
        manage_client(ans);
    }
    else if (a == 2)
    {
        printf("\n 1- Create account \n");
        printf(" 2- Search ID \n");
        printf(" 3- Account display \n");
        printf(" 4- Delete account \n");
        printf(" 5- Previous page \n");
        printf(" Choose a secondary menu: ");
        scanf("%i", &ans);
        manage_account(ans);
    }
    else if(a == 3)
    {
        printf("\n  1-Money withdrawal \n");
        printf("  2-Money transfer \n");
        printf("  3-Account inquiry");
        printf(" 4- Previous page \n");
        printf(" Choose a secondary menu: ");
        scanf("%i", &ans);
        manage_transactions(ans);
    }
    else if(a == 4)
    {
        return 0;
    }
    else
    {
        printf("Invalid key");
        return 1;
    }
    return 0;
}
void manage_client(int a)
{
    if(a == 1)
    {
        struct client new_cli;
        FILE *file;
        printf("Client ID:  ");
        scanf("%i", &new_cli.id_cli);
        printf("\nClient_name: ");
        scanf("%s", &new_cli.name);
        printf("\nClient last name:");
        scanf("%s", &new_cli.lastname);
        file = fopen("client.txt", "a");
        fwrite(&new_cli, sizeof(new_cli), 1, file);
        if(fwrite !=0)
        {
            printf("\nClient added successfully! ");
        }
    }
}

