/*****************************************************************
//
//  NAME:        Jonah Lene
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 26, 2022
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file contains main and  the getaddress method for
//   Project 1.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"

void getaddress (char [], int);

int debug = -1;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Main function displays Bank options to user
//                 and executes the userʻs command.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int main (int argc, char * argv[])
{
    int accountno;
    char name[30];
    char address[50];
    char input[30];
    char invalid_input[100];
    int num_checker;
    int end;
    int stop;
    int success;
    int i;

    struct record * start = NULL;
    end = -1;


    if(argc > 2)
    {
        printf("Incorrect format!\n");
        end = 1;
    }
    else if(strcmp(argv[0], "./project") == 0 && argc == 1)
    {
        end = -1;
    }
    else
    {

        if(strcmp(argv[1], "debug") == 0)
        {
            printf("\nDebug Mode Activated\n");
            debug = 0;
        }
        else
        {
            end = 1;
            printf("Incorrect format!\n");
        }
    }
    readfile(&start, "BankDatabase.txt");

    if(end < 0)
    {
        printf("\nWelcome to the bank! Here you can choose multiple options pertaining your back records and if you are new, you can create record that will be linked specifically to you and your account.\n");
    }

    while(end < 0)
    {
        printf("\nMenu: Type one of the below options into the console to access them. \n");
        printf("add: Add a new record in the database. \n");
        printf("printall: Print all records in the database. \n");
        printf("find: Find record(s) with a specified account #. \n");
        printf("delete: Delete existing record(s) from the database using the account #.\n");
        printf("quit: Exits out the program. Must enter the exact word 'quit'. \n");

        printf("\nEnter name of option you want to use: ");
        scanf("%s", input);

        if(strcmp(input, "add") == 0 || strcmp(input, "ad") == 0 || strcmp(input, "a") == 0)
        {
            stop = -1;

            while(stop < 0)
            {
                printf("Enter number for account: ");
                num_checker = scanf("%d", &accountno);

                if(num_checker != 0 && accountno > 0)
                {
                    printf("Your account number is: %d\n", accountno);
                    stop = 1;
                }
                else if(num_checker == 0)
                {
                    printf("Invalid input, enter postive number! Try again.\n");
                    fgets(invalid_input, 100, stdin);
                }
                else if(accountno <= 0)
                {
                    printf("Invalid input, enter postive number! Try again.\n");
                    fgets(invalid_input, 100, stdin);
                }
            }
            fgets(invalid_input, 100, stdin);
            printf("Enter name for account: ");
            fgets(name, 30, stdin);
            printf("Your account is under the name: %s", name);

            getaddress(address, 50);
            fgets(invalid_input, 100, stdin);
 
            for(i = 0; name[i] != '\0'; i++)
            {
                if(name[i] == '\n')
                {
                    name[i] = ' ';       
                }
            }
            addRecord(&start, accountno, name, address);
   
        }
        else if(strcmp(input, "printall") == 0 || strcmp(input, "p") == 0 || strcmp(input, "pr") == 0 || strcmp(input, "pri") == 0 || strcmp(input, "prin") == 0 || strcmp(input, "print") == 0 || strcmp(input, "printa") == 0 || strcmp(input, "printal") == 0)
        {
            printAllRecords(start); 
        }

        else if(strcmp(input, "find") == 0 || strcmp(input, "f") == 0 || strcmp(input, "fi") == 0 || strcmp(input, "fin") == 0)
        {
            stop = -1;

            while(stop < 0)
            {
                printf("Enter account number to find a record in the database: ");
                num_checker = scanf("%d", &accountno);

                if(num_checker == 0)
                {
                    printf("Invalid input, enter positive number! Try again.\n");
                    fgets(invalid_input, 100, stdin);
                }
                else if(accountno <= 0)
                {
                    printf("Invalid input, enter positive number! Try again.\n");
                    fgets(invalid_input, 100, stdin);
                }
                else
                {
                    success = findRecord(start, accountno);
                    if(success == 0)
                    {
                        printf("Record found\n");
                    }
                    else
                    {
                        printf("Record does not exist\n");
                    }  
                    stop = 1;
                }
            }
        }

        else if(strcmp(input, "delete") == 0 || strcmp(input, "d") == 0 || strcmp(input, "de") == 0 || strcmp(input, "del") == 0 || strcmp(input, "dele") == 0 || strcmp(input, "delet") == 0)
        {
            stop = -1;

            while(stop < 0)
            {
                printf("Enter account number to delete the record from the database: ");
                num_checker = scanf("%d", &accountno);

                if(num_checker == 0)
                {
                    printf("Invalid input, enter positive number! Try again.\n");
                    fgets(invalid_input, 100, stdin);
                }
                else if(accountno <= 0)
                {
                    printf("Invalid input, enter positive number! Try again.\n");
                    fgets(invalid_input, 100, stdin);
                }
                else
                {
                    success = deleteRecord(&start, accountno);
                    
                    if(success == 0)
                    {
                        printf("Record was deleted!\n");
                    }
                    else
                    {
                        printf("Record does not exist!\n");
                    }

                    stop = 1;
                }
            }
        }

        else if(strcmp(input, "quit") == 0)
        {
            writefile(start, "BankDatabase.txt");
            cleanup(&start);
            printf("\nProgram exited. Have a nice day!\n");
            end = 1;
        }

    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Function reads user input for address input
//                 and saves the address exactly how it looks.
//
//  Parameters:    accAddress (char*) : character pointer
//                 size (int) : the size of the array
//
//  Return values:  None, void function.
//
****************************************************************/

void getaddress(char accAddress[], int size)
{
    char end;
    char last;
    int counter;

    end = '*';
    counter = 0;

    if(debug == 0)
    {
        printf("\ngetaddress function called\n");
        printf("It holds the parameters accaddress(the users address) and size(the size limit for the address).\n");
    }

    printf("\nEnter an address for your account.\n");
    printf("Insert * symbol at the end of your address to indicate you are done: ");

    last = getchar();

    while(last != end && counter < size)
    {
        accAddress[counter] = last;
        counter++;
        last = getchar();

    }
    accAddress[counter] = '\0';
    getchar();
    printf("Your account address is: %s\n", accAddress);

    if(debug == 0)
    {
        printf("\nCurrent Parameters of getaddress:\n");
        printf("accAddress = %s\nsize = %d\n", accAddress, size);
        printf("End of getaddress function!\n");
    }
}

























