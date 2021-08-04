#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN 20

typedef struct Numb_Line
{
    char* line;
} Struct_1;

typedef struct Next
{
    Struct_1 data;
    Next * next;          //adress of the next element ;          
} Struct_2;

Struct_2* start, * finish;           //pointer on the start and finish
char end[] = "#";


char* Input(Struct_1* numb_line, int& counter);          // entering word
void New_Elem(Struct_1 numb);                            // list formation
void Add(Struct_2* new_elem, Struct_2* old_elem);        // adding elements in list
void Print();                                            // print elements
void Clear_All(Struct_2* start);                         // clear all elements   
void Delete_Elem(int n);                                 // deleting an element

int main()
{
    system("chcp 1251");
    system("cls");

    Struct_1 input_info;
    Struct_1 input_info_1;

    int count = 1;
    printf("\n\t--------------------------------------\n\t|         Single-linked list         |\n\t--------------------------------------\n");
    printf("\n\tEnter your data (# - end of entering) : \n\n");

    while (strcmp(Input(&input_info, count), end) != 0)
        New_Elem(input_info);

    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("\n\tWord list :\n\n");
    Print();

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
        numb_line->line = (char*)malloc(strlen(temp) + 1);      //виділення ДП для рядка
        strcpy(numb_line->line, temp);
        counter++;
        rewind(stdin);                  //очищення буферу
    }
    else
        numb_line->line = NULL;         //кінець рядка
    return temp;
}

void New_Elem(Struct_1 numb)
{
    Struct_2* elem;
    Struct_2* position;                                 //вказівники на сам елемент та позицію, куди він має вставитись
    elem = (Struct_2*)malloc(sizeof(Struct_2));         //виділення ДП для списку
    elem->data = numb;

    if (start == NULL)        //якщо елемент 1 у списку
    {
        elem->next = NULL;
        start = elem;
        finish = elem;
        return;             //вихід з функції
    }
    position = elem->next;
    Add(elem, position);
}

void Add(Struct_2* new_elem, Struct_2* position)
{
    if (position != NULL)
    {
        finish->next = new_elem;
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
            start_1->next = NULL;
        }
    }
}



void Delete_Elem(int n)
{
    Struct_2* elem_1 = start, * elem_2 = start;
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
        if(counter_1>=3)
            elem_2 = elem_2->next;
    }

    if (elem_1 == start)
    {
        start = start->next;
        free(elem_1->data.line);
        free(elem_1);
        elem_1->data.line = NULL;
        elem_1->next = NULL;
    }
    else
    {
        elem_2->next = elem_1->next;
        free(elem_1->data.line);
        free(elem_1);
        elem_1->data.line = NULL;
        elem_1->next = NULL;
    }
}