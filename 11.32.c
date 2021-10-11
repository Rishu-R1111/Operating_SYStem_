#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NULL 0
struct list_element
{
char item(40];
struct list_element *next;
};

typedef struct list_element node;

int menu(void);
void create(node *pt);
node *insert(node *pt);
node *remove(node *pt);
void display(node *pt);

main()

{
    node *start;
    int choice;
    do
    {
        choice = menu();
        switch (choice)
        {
        case 1: /* create the linked list*/
            start = (node *)malloc(sizeof(node));
            create(start);
            printf(" \n");
            display(start);
            continue;
        case 2: /* add one component*/
            start = insert(start);
            printf(" \n");
            display(start);
            continue;

        case 3: /* delete one component*/
            start = remove(start);
            printf("\n");
            display(start);
            continue;
        default: /* terminate computation*/
            printf("End of computation\n");
        }
    } while (choice I = 4);
}

int menu(void) /* generate the main menu*/

    int choice;
do
{
    printf("\nMain menu:\n");
    printf(" 1	CREATE the linked list\n");

printf("2  ADD a component\n");
printf("3  DELETE a component\n");
printf("4  END\n");
printf("Please enter your choice (1, 2, 3 or 4) -> ");
 scanf("%d", &choice);
if (choice < 1 11 choice > 4)
printf("\nERROR - Please try again\n"); 
while ( choice < 1|| choice > 4);
printf("\n"); return(choice);
}

void create(node *record)	/* create a linked list*/
/* argument points to the current node*/

printf("Data item (type \"END\" when finished): ");
 scanf(" %["\n]", record->item);
if (strcmp(record->item, "END") -- O) record->next = NULL;
else {
    /* allocate space for next node*/
    record->next = (node *)malloc(sizeof(node));
    /* create the next node*/ create(record->next);

    return;
