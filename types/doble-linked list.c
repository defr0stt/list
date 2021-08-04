#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN 20

typedef struct Numb_Line
{
    char* line;
} Struct_1;

typedef struct Prev_Next
{
    Struct_1 data;
    Prev_Next* prev, * next;          //adress of the next element           
} Struct_2;

Struct_2* start, * finish;           //pointers on the start and finish
char end[] = "#";


char* Input(Struct_1* numb_line, int& counter);          // entering word
void New_Elem(Struct_1 numb);                            // list formation
void Add(Struct_2* new_elem, Struct_2* old_elem);        // adding elements in list
void Print();                                            // print elements
void Clear_All(Struct_2* start);                         // clear all elements
void Back_Print();                                       // backprint elements    
void Delete_Elem(int n);                                 // deleting an element

int main()
{
    system("chcp 1251");
    system("cls");

    int a = 0, ct = 1;
    Struct_1 input_info;
    Struct_1 input_info_2;
    Struct_1 input_info_1;

        int count = 1;
        printf("\n\t--------------------------------------\n\t|         Double-linked list         |\n\t--------------------------------------\n");
        printf("\n\tEnter your data (# - end of entering) : \n\n");

        while (strcmp(Input(&input_info, count), end) != 0)
            New_Elem(input_info);

        printf("------------------------------------------------------------------------------------------------------------------------");
        printf("\n\tWord list :\n\n");
        Print();

        printf("\n\tWord list (backprint) :\n\n");
        Back_Print();

        printf("\nEnter the element what you whant to delete : ");
        scanf_s("%d", &count);
        Delete_Elem(count);

        printf("\n\n\tAfter deleting :\n\n");
        Print();

        printf("\n------------------------------------------------------------------------------------------------------------------------");

        Clear_All(start);
    return 0;
}



char* Input(Struct_1* numb_line, int& counter)
{
    char temp[LEN];
    printf("  Word №%d - ", counter);
    gets_s(temp);
    if (strcmp(temp, end) != 0)
    {
        numb_line->line = (char*)malloc(strlen(temp) + 1);      //dyn memory for line
        strcpy(numb_line->line, temp);
        counter++;
        rewind(stdin);                  //clearing the buffer
    }
    else
        numb_line->line = NULL;         //end of the line
    return temp;
}

void New_Elem(Struct_1 numb)
{
    Struct_2* elem;
    Struct_2* position;                                 //position the element where it needs to insert
    elem = (Struct_2*)malloc(sizeof(Struct_2));         //dyn memory for list
    elem->data = numb;

    if (start == NULL)        //if elem count =1
    {
        elem->prev = NULL;
        elem->next = NULL;
        start = elem;
        finish = elem;
        return;             //go out of a function
    }
    position = elem->next;
    Add(elem, position);
}

void Add(Struct_2* new_elem, Struct_2* position)
{
    if (position != NULL)
    {
        finish->next = new_elem;
        new_elem->prev = finish;
        new_elem->next = NULL;
        finish = new_elem;
    }
}

void Print()
{
    Struct_2* elem = start;
    int i = 1;
    while (elem != NULL)
    {
        printf("%-2d - %-20s\n", i, elem->data.line);
        elem = elem->next;
        i++;
    }
}

void Back_Print()
{
    Struct_2* elem = finish;
    int i = 1;
    while (elem != NULL)
    {
        printf("%-2d - %-20s\n", i, elem->data.line);
        elem = elem->prev;
        i++;
    }
}

void Clear_All(Struct_2* start)
{
    while (start != NULL)
    {
        Struct_2* start_1;
        start_1 = start;
        start = start->next;
        if (start_1->data.line != NULL)
        {
            free(start_1->data.line);
            free(start_1);
            start_1->data.line = NULL;
            start_1->prev = NULL;
            start_1->next = NULL;
        }
    }
}



void Delete_Elem(int n)
{
    Struct_2* elem_1 = start;
    int counter_1 = 1;

    while (1)
    {
        if (counter_1 == n)
        {
            printf("\nDeleting the line #%d - %s", n, elem_1->data.line);
            break;
        }
        counter_1++;
        elem_1 = elem_1->next;
    }

    if (elem_1 == start)
    {
        start = start->next;
        start->prev = NULL;
        free(elem_1->data.line);
        free(elem_1);
        elem_1->data.line = NULL;
        elem_1->prev = NULL;
        elem_1->next = NULL;
    }
    else
    {
        elem_1->prev->next = elem_1->next;
        elem_1->next->prev = elem_1->prev;
        free(elem_1->data.line);
        free(elem_1);
        elem_1->data.line = NULL;
        elem_1->prev = NULL;
        elem_1->next = NULL;
    }
}