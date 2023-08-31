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
//  DATE:        March 26, 2022
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   Contains the function prototypes for the database in 
//   Project 1.
//
****************************************************************/

void addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char []);
int readfile(struct record **, char []);
void cleanup(struct record **);
