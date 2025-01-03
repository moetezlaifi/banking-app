#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int balance;
} account;

client clients[max_clients];
account accounts[max_accounts];
int choice;

void main_menu(void);
int sec_menu(int a);
int manage_client(int a);
int manage_account(int a);
int manage_transactions(int a);
int compare(const void* a, const void* b);


int main(void)
{
    main_menu();
}


void main_menu(void)
{
    printf("1- Manage clients \n");
    printf("2- Manage accounts \n");
    printf("3- Manage operations \n");
    printf("4- Exit \n");
    printf("Choose a menu: ");
    scanf("%i", &choice);
    printf("\n__________________________________\n");
    sec_menu(choice);

}

int sec_menu(int a)
{
    int ans;
    if (a == 1)
    {
        printf("\n 1- Add client \n");
        printf(" 2- Edit client \n");
        printf(" 3- Delete Client \n");
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
        printf(" 3- Previous page \n");
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
        printf("ERROR 1: Invalid Key ! \n");
        return 1;
    }
    printf("\n__________________________________\n");
    return 0;
}
int manage_client(int a)
{
    if(a == 1)
    {
        struct client new_cli;
        FILE *file;
        printf("\nClient ID:  ");
        scanf("%i", &new_cli.id_cli);
        printf("\nClient_name: ");
        scanf("%s", new_cli.name);
        printf("\nClient last name:");
        scanf("%s", new_cli.lastname);
        file = fopen("client.txt", "a");
        fwrite(&new_cli, sizeof(new_cli), 1, file);
        printf("\nClient added successfully! \n");
        fclose(file);

    }
    else if(a == 2)
    {
        struct client original_cli;
        struct client new_cli;
        FILE *file;
        printf("\nClient ID: ");
        scanf("%i", &new_cli.id_cli);
        printf("\nClient_name: ");
        scanf("%s", new_cli.name);
        printf("\nClient last name: ");
        scanf("%s", new_cli.lastname);
        file = fopen("client.txt", "r");
        int nbClients = 0;
        while(fread(&original_cli, sizeof(struct client), 1, file))
        {
            clients[nbClients] = original_cli;
            nbClients++;
        }
        fclose(file);
        remove("client.txt");
        FILE *newfile;
        newfile = fopen("client.txt", "w");
        for(int i = 0; i < nbClients; i++)
        {
            if(clients[i].id_cli == new_cli.id_cli)
            {
                fwrite(&new_cli, sizeof(new_cli), 1, newfile);
            }
            else
            {
                fwrite(&clients[i], sizeof(clients[i]), 1, newfile);
            }
        }
        fclose(newfile);
        printf("\nClient modified successfully !\n");
    }
    else if(a == 3)
    {
        struct client original_cli;
        struct client new_cli;
        FILE *file;
        printf("\nClient ID: ");
        scanf("%i", &new_cli.id_cli);
        file = fopen("client.txt", "r");
        int nbClients = 0;
        while(fread(&original_cli, sizeof(struct client), 1, file))
        {
            clients[nbClients] = original_cli;
            nbClients++;
        }
        fclose(file);
        remove("client.txt");
        FILE *newfile;
        newfile = fopen("client.txt", "w");
        for(int i = 0; i < nbClients; i++)
        {
            if(clients[i].id_cli != new_cli.id_cli)
            {
                fwrite(&clients[i], sizeof(new_cli), 1, newfile);
            }
        }
        fclose(newfile);
        printf("\nClient deleted successfully !\n");
    }
    else if(a == 4)
    {
        struct client original_cli;
        printf("Clients: \n");
        FILE *file;
        file = fopen("client.txt", "r");
        int nbClients = 0;
        while(fread(&original_cli, sizeof(struct client), 1, file))
        {
            clients[nbClients] = original_cli;
            nbClients++;
        }
        qsort(clients,nbClients,sizeof(client),compare);
        for (int i = 0; i < nbClients; i++)
        {
            printf("ID: %i \nName: %s \nLast Name: %s\n", clients[i].id_cli, clients[i].name, clients[i].lastname);
        }

    }
    else if(a == 5)
    {
        main_menu();
        return 0;
    }
    else
    {
        printf("ERROR 1: Invalid Key ! \n");
        return 1;
    }
    printf("\n__________________________________\n");
    main_menu();
    return 0;
}
int manage_account(int a)
{
    if(a == 1)
    {
        struct account new_acc;
        FILE *file;
        printf("\nAccount ID: ");
        scanf("%i", &new_acc.id_acc);
        printf("\nClient ID: ");
        scanf("%i", &new_acc.id_cli);
        printf("\nAccount balance: ");
        scanf("%i", &new_acc.balance);
        if(new_acc.balance < 250)
        {
            printf("ERROR 5: Not enough balance !");
            return 5;
        }
        printf("\nCreation date: ");
        printf("\nDay: ");
        scanf("%i", &new_acc.d_acc.day);
        printf("Month: ");
        scanf("%i", &new_acc.d_acc.month);
        printf("Year: ");
        scanf("%i", &new_acc.d_acc.year);
        file = fopen("account.txt", "a");
        fwrite(&new_acc, sizeof(new_acc), 1, file);
        fclose(file);
        printf("\nAccount added successfully !\n");

    }
    else if(a == 2)
    {
        int search_id;
        printf("\nAccount ID: ");
        scanf("%i", &search_id);
        struct account search_acc;
        FILE *file;
        file = fopen("account.txt", "r");
        int nbAcc = 0;
        int test = 0;
         while(fread(&search_acc, sizeof(struct account), 1, file))
         {
            if(search_acc.id_acc == search_id)
            {
                test = 1;
                printf("\nAccount ID: %i \nClient ID: %i \nAccount balance: %i\nCreation date: %i/%i/%i \n", search_acc.id_acc, search_acc.id_cli, search_acc.balance, search_acc.d_acc.day, search_acc.d_acc.month, search_acc.d_acc.year);
            }
            nbAcc++;
         }
         if (test == 0)
         {
            printf("ERROR 2: Account not found :( !\n");
            return 2;
         }

    }
    else if(a == 3)
    {
        struct account acc;
        FILE *file;
        file = fopen("account.txt", "r");
        int nbAcc = 0;
         while(fread(&acc, sizeof(struct account), 1, file))
         {
            printf("\nAccount ID: %i \nClient ID: %i \nAccount balance: %i\nCreation date: %i/%i/%i \n", acc.id_acc, acc.id_cli, acc.balance, acc.d_acc.day, acc.d_acc.month, acc.d_acc.year);
            nbAcc++;
         }
    }
    else if(a == 4)
    {
        struct account acc;
        struct account new_acc;
        FILE *file;
        printf("\nAccount ID: ");
        scanf("%i", &new_acc.id_acc);
        file = fopen("account.txt", "r");
        int nbAcc = 0;
        while(fread(&acc, sizeof(struct account), 1, file))
        {
            accounts[nbAcc] = acc;
            nbAcc++;
        }
        fclose(file);
        remove("account.txt");
        FILE *newfile;
        newfile = fopen("account.txt", "w");
        int test = 0;
        for(int i = 0; i < nbAcc; i++)
        {
            if(accounts[i].id_acc != new_acc.id_acc)
            {
                fwrite(&accounts[i], sizeof(new_acc), 1, newfile);
            }
            else
            {
                test = 1;
            }
        }
        if (test == 0)
         {
            printf("ERROR 2: Account not found :( !\n");
            return 2;
         }
        fclose(newfile);
        printf("\nAccount deleted successfully !\n");
    }
    else if(a == 5)
    {
        main_menu();
        return 0;
    }
    else
    {
        printf("ERROR 1: Invalid key !");
        return 1;
    }
    printf("\n__________________________________\n");
    main_menu();
    return 0;
}

int manage_transactions(int a)
{
    if(a == 1)
    {
        struct account acc;
        struct account new_acc;
        FILE *file;
        printf("\nAccount ID: ");
        scanf("%i", &new_acc.id_acc);
        file = fopen("account.txt", "r");
        int nbAcc = 0;
        while(fread(&acc, sizeof(struct account), 1, file))
        {
            accounts[nbAcc] = acc;
            nbAcc++;
        }
        fclose(file);
        remove("account.txt");
        FILE *newfile;
        newfile = fopen("account.txt", "w");
        int test = 0;
        for(int i = 0; i < nbAcc; i++)
        {
            if(accounts[i].id_acc == new_acc.id_acc)
            {
                test = 1;
                int amount;
                printf("\nPlease specify the amount you would like to withdraw.");
                scanf("%i", &amount);
                if(amount > 500)
                {
                    printf("\nERROR 3 Limit exceeded !\n");
                    return 3;
                }
                else if(amount > accounts[i].balance)
                {
                    printf("\nERROR 4: unsufficient balance\n");
                    return 4;
                }
                else
                {
                    accounts[i].balance = accounts[i].balance - amount;
                    printf("\nAccount ID: %i \nClient ID: %i \nAccount balance: %i\nCreation date: %i/%i/%i \n", accounts[i].id_acc, accounts[i].id_cli, accounts[i].balance, accounts[i].d_acc.day, accounts[i].d_acc.month, accounts[i].d_acc.year);
                }
            }
            fwrite(&accounts[i], sizeof(new_acc), 1, newfile);
        }
        if (test == 0)
         {
            printf("ERROR 2: Account not found :( !\n");
            return 2;
         }
        fclose(newfile);
    }
    else if(a == 2)
    {
        struct account acc;
        struct account new_acc;
        struct account reciever_acc;
        FILE *file;
        printf("\nSender account ID: ");
        scanf("%i", &new_acc.id_acc);
        printf("\nReciever account ID: ");
        scanf("%i", &reciever_acc.id_acc);
        file = fopen("account.txt", "r");
        int nbAcc = 0;
        while(fread(&acc, sizeof(struct account), 1, file))
        {
            accounts[nbAcc] = acc;
            nbAcc++;
        }
        fclose(file);
        remove("account.txt");
        FILE *newfile;
        newfile = fopen("account.txt", "w");
        int test_sender = 0;
        int test_reciever = 0;
        int amount;
        printf("\nPlease specify the amount you would like to transfer.");
        scanf("%i", &amount);
        for(int i = 0; i < nbAcc; i++)
        {
            if(accounts[i].id_acc == new_acc.id_acc)
            {
                test_sender = 1;
                if(amount > accounts[i].balance)
                {
                    printf("\nERROR 4: unsufficient balance\n");
                    return 4;
                }
            }
            if(accounts[i].id_acc == reciever_acc.id_acc)
            {
                test_reciever = 1;
            }
        }
        if (test_sender == 0)
         {
            printf("ERROR 2: Sender account not found :( !\n");
            return 2;
         }
         if (test_reciever == 0)
         {
            printf("ERROR 2: Reciever account not found :( !\n");
            return 2;
         }
        for(int i = 0; i < nbAcc; i++)
        {
            if(accounts[i].id_acc == new_acc.id_acc)
            {
                accounts[i].balance = accounts[i].balance - amount;
                printf("\nSender Account:\nAccount ID: %i \nClient ID: %i \nAccount balance: %i\nCreation date: %i/%i/%i \n", accounts[i].id_acc, accounts[i].id_cli, accounts[i].balance, accounts[i].d_acc.day, accounts[i].d_acc.month, accounts[i].d_acc.year);
            }
            if(accounts[i].id_acc == reciever_acc.id_acc)
            {
                accounts[i].balance += amount;
                printf("\nReciever Account:\nAccount ID: %i \nClient ID: %i \nAccount balance: %i\nCreation date: %i/%i/%i \n", accounts[i].id_acc, accounts[i].id_cli, accounts[i].balance, accounts[i].d_acc.day, accounts[i].d_acc.month, accounts[i].d_acc.year);
            }
            fwrite(&accounts[i], sizeof(new_acc), 1, newfile);
        }
        fclose(newfile);
    }
    else if(a == 3)
    {
        main_menu();
        return 0;
    }
    else
    {
        printf("ERROR 1: Invalid key !");
        return 1;
    }
    printf("\n__________________________________\n");
    main_menu();
    return 0;
}
int compare(const void* a, const void* b)
{
    const client *c1 = a;
    const client *c2 = b;
    return strcmp(c1 -> name, c2 -> name);
}

