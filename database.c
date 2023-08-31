/*****************************************************************
//
//  NAME:        Jonah Lene
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 26, 2022
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   File holds multiple functions that are called through
//   the user in user_interface.
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

extern int debug;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record that user input to the users
//                 account.
//
//  Parameters:    start (record **) : pointer to the first record
//                 uaccountno (int) : userʻs account number of 
//                                    record
//                 uname (char) : character array containing
//                                userʻs name
//                 uaddress (char) : character array containing
//                                   the userʻs address
//
****************************************************************/

void addRecord(struct record ** start, int uaccountno, char uname[], char uaddress[])
{
    struct record * temp;
    struct record * prev;
    struct record * newNode;
    int key;

    newNode = malloc(sizeof(struct record)); 
    key = uaccountno;

    if(debug == 0)
    {
        printf("\naddRecord function called!\n");
        printf("It holds the parameters start(the pointer to the record), uaccountno(the users account number), uname(the name the account is under), and uaddress(the accounts address).\n");
        printf("accNum = %d\naccName = %s\naccAddress = %s\n", uaccountno, uname, uaddress);
    }
    
    temp = *start;

    if(*start == NULL || key < (*temp).accountno)
    {
        (*newNode).next = temp;
        *start = newNode;
    }
    else
    { 
        temp = *start;
        
        while(temp != NULL && (*temp).accountno <= key)
        {
            prev = temp;
            temp = (*temp).next;
        }
        (*newNode).next = temp;
        (*prev).next = newNode;
    }
    (*newNode).accountno = uaccountno;
    strcpy((*newNode).name, uname);
    strcpy((*newNode).address, uaddress); 
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:  Prints all records for user.
//
//  Parameters:    start (record *) : Pointer to the start of 
//                                    record
//
****************************************************************/

void printAllRecords(struct record * start)
{
    struct record * temp;
    temp = start;

    if(debug == 0)
    {
        printf("\nprintAllRecords function called!\n");
        printf("It holds the parameter start(Pointer to the start of record).\n");
    }

    while(temp != NULL)
    {
        printf("\nRecord: \n");
        printf("Account number: %d\n", (*temp).accountno);
        printf("Account name: %s\n", (*temp).name);
        printf("Account address: %s\n", (*temp).address);
    
        temp = (*temp).next;    
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds and prints record from the account
//                 number.
//
//  Parameters:    start (record *) : pointer to the start 
//                                    of record
//                 uaccountnum (int) : record number
//
//  Return values:  0 : success
//
****************************************************************/

int findRecord(struct record * start, int uaccountnum)
{
    struct record * temp;
    int works;
    
    if(debug == 0)
    {
        printf("\nfindRecord function called!\n");
        printf("It holds the parameters pointer(the pointer to the record) and uaccountnum(the users account number).\n");
        printf("Account number = %d\n\n", uaccountnum);
    }

    temp = start;
    works = -1;

    while(temp != NULL)
    {
        if((*temp).accountno == uaccountnum && works == -1)
        {
            printf("Account number: %d\n", (*temp).accountno);           
            printf("Account name: %s\n", (*temp).name);
            printf("Account address: %s\n", (*temp).address);
            works = 0;
        }
        temp = (*temp).next;
    }
    return works;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes a specified record
//
//  Parameters:    uaccountno (int) : account number of record
//                 start (record **) : pointer to the start of 
//                                     record
//
//  Return values:  0 : success
//
****************************************************************/

int deleteRecord(struct record ** start, int uaccountno)
{
    struct record * temp;
    struct record * prev;
    struct record * remove;
    int key;
    int works;

    prev = NULL;
    remove = NULL;
    key = uaccountno;
    works = -1;

    if(debug == 0)
    {
        printf("\ndeleteRecord function called!\n");
        printf("It holds the parameters start(the pointer to the record) and uaccountnum(the users account number).\n");
        printf("User Account Number = %d\n", uaccountno);
    }

    temp = *start;

    if(*start == NULL || key <= 0)
    {
        works = -1;
    }
    else if((*temp).next == NULL)
    {
        if(key == (*temp).accountno)
        {
            free(temp);
            *start = NULL;
            works = 0;
        }
    }
    else
    {
        while((*temp).next != NULL && key > 0)
        {
            if(key == (*temp).accountno && prev == NULL)
            {
                remove = temp;
                *start = (*temp).next;
                temp = *start;
                free(remove);
                works = 0;
            }   
            else if(key == (*temp).accountno)
            {
                remove = temp;
                temp = (*temp).next;
                (*prev).next = temp;
                free(remove);
                works = 0;
            }
            else if(key != (*temp).accountno)
            {
                prev = temp;
                temp = (*temp).next;
            } 
        }
        if((*temp).next == NULL && key == (*temp).accountno)
        {
            (*prev).next = NULL;
            free(temp);
            works = 0;
        }
    }
    return works;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:    Writes data stored in the array into a 
//                  text file.   
//
//  Parameters:    start (struct record *): Start of record
//                 filename (char []) : The file we are are writing
//                                   to     
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int writefile(struct record * start, char filename[])
{
    FILE *wfile;
    struct record * temp;
    int works;

    wfile = fopen(filename, "w");
    temp = start;

    if(debug == 0)
    {
        printf("\nwritefile function called!\n");
        printf("It holds the parameters start(the pointer to the record) and character array filename(the file we are writing to.\n");
        printf("Writing File: %s\n", filename);
    }
    
    if(wfile == NULL)
    {
        works = -1;
    }
    else
    {
        while(temp != NULL)
        {
            fprintf(wfile, "%d\n", (*temp).accountno);
            fprintf(wfile, "%s\n", (*temp).name);
            fprintf(wfile, "%s\n", (*temp).address);
            temp = temp->next;
        }
        fclose(wfile);
        works = 0;
    }
    return works;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:    Reads data from a text file and stores it in
//                  the array.   
//
//  Parameters:    start (struct record **) : Pointer pointer to
//                                            start of record.
//                 filename (char []) : Name of file to be read.
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int readfile(struct record ** start, char filename[])
{
    FILE *rfile;
    char name[25];
    char address[80];
    int works;
    int accountnum; 
    int checker;  

    if(debug == 0)
    {
        printf("\nreadfile function called!\n");
        printf("It holds the parameters start(the pointer pointer to the start of record) and filename(the name of file to be read).\n");
        printf("Reading file: %s\n", filename);
    }

    rfile = fopen(filename, "r");

    if(rfile == NULL)
    {
        works = -1;
    }
    else
    {
        while(fscanf(rfile, "%d\n", &accountnum) != EOF)
        {
            fgets(name, 25, rfile);
            fgets(address, 80, rfile);
            checker = strlen(name);
            checker = strlen(address);
            if(name[checker - 1] == '\n')
            {
                name[checker - 1] = '\0';
            }
            if(address[checker - 1] == '\n')
            {
                address[checker - 1] = '\0';
            }
            addRecord(start, accountnum, name, address);
        }
        fclose(rfile);
        works = 0;
    }
    return works;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:    Realeses all the allocated spaces in the heap
//                  memory and assigns NULL to start.   
//
//  Parameters:    start (record **) : Pointer pointer to start
//                                     of the record. 
//
****************************************************************/

void cleanup(struct record ** start)
{
    struct record * temp;
    struct record * prev;
    
    temp = *start;
    prev = NULL;

    if(debug == 0)
    {
        printf("cleanup function called\n");
    }
    
    while(temp != NULL)
    {
        prev = temp;
        temp = temp->next;
        free(prev);
    }    

    *start = NULL;    
}


