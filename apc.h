#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1


#include <stdio.h>
#include <stdlib.h>


typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;


data_t compareList(Dlist *temp, Dlist *temp_head);
void print_list(Dlist **head);
void free_list(Dlist **head);
data_t insert_at_last(Dlist **head, Dlist **tail, data_t data);
data_t insert_at_first(Dlist **head, Dlist **tail, data_t data);
data_t addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
data_t subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
data_t division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
data_t sub_for_div(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
data_t multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
#endif
