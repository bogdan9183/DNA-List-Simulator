//
// Created by bogdan on 20.03.2016.
//
#ifndef TEMA1_SD_FUNCTIONS_H
#define TEMA1_SD_FUNCTIONS_H
#endif //TEMA1_SD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod {
    char info;
    char snod;
    struct Nod *next;
} Nod;

typedef struct Stack {
    char name[3];
    char command[20];
    struct Stack *next;
} Stack;

Stack *Commands;

Nod *List1, *List2;

void init(Nod**, char*);
void Insert(Nod**, int, int, char, char );
void InsertParser(char*);
void EditElement(Nod **, int, int, char, char);
void EditElementParser(char *);
void Delete(Nod **, int, int);
void DeleteParser(char *);
void PrintLine(Nod*, FILE*);
void Parse(char *, int);
void citire(char *);
void Reverse(Nod **);
void PrintReverse(Nod*, FILE*);
void printStack(Stack *);
void popStack(Stack **);
void pushStack(char *, Stack **, char *);
Nod *Retriever(int , int , int );
void ex();
