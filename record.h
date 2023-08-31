/*****************************************************************
//
//  NAME:        Ravi Narayan
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        Match 26, 2022
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the structure for Project 1.
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
