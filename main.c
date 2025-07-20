#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 
 * Function: print_list
 * --------------------
 * Prints the doubly linked list from head to tail.
 */
void print_list(Dlist **head)
{
    if (*head == NULL)
    {
        printf("List is empty");
        return;
    }

    while ((*head) != NULL)
    {
        printf("%d", (*head)->data);
        *head = (*head)->next;
    }
    printf("\n");
}

/* 
 * Function: compareList
 * ---------------------
 * Compares two numbers represented by doubly linked lists.
 * Returns:
 *   -1 : if num1 < num2
 *    1 : if num1 > num2
 *    0 : if num1 == num2
 */
int compareList(Dlist *num1, Dlist *num2)
{
    if (!num1 || !num2) return -1;

    // Count the number of digits in both lists
    size_t count1 = 0, count2 = 0;
    Dlist *temp1 = num1, *temp2 = num2;

    while (temp1) { count1++; temp1 = temp1->next; }
    while (temp2) { count2++; temp2 = temp2->next; }

    // Compare lengths
    if (count1 < count2) return -1;
    if (count1 > count2) return 1;

    // If equal length, compare digit by digit
    temp1 = num1;
    temp2 = num2;
    while (temp1 && temp2)
    {
        if (temp1->data < temp2->data) return -1;
        if (temp1->data > temp2->data) return 1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

/* 
 * Function: insert_at_last
 * ------------------------
 * Inserts a new node at the end of the doubly linked list.
 */
data_t insert_at_last(Dlist **head, Dlist **tail, data_t val)
{
    Dlist *n = malloc(sizeof *n);
    if (!n) return FAILURE;

    n->data = val;
    n->next = NULL;

    if (*tail)
    {
        n->prev = *tail;
        (*tail)->next = n;
        *tail = n;
    }
    else
    {
        n->prev = NULL;
        *head = *tail = n;
    }

    return SUCCESS;
}

/* 
 * Function: insert_at_first
 * -------------------------
 * Inserts a new node at the beginning of the doubly linked list.
 */
data_t insert_at_first(Dlist **head, Dlist **tail, data_t val)
{
    Dlist *n = malloc(sizeof *n);
    if (!n) return FAILURE;

    n->data = val;
    n->prev = NULL;

    if (*head)
    {
        n->next = *head;
        (*head)->prev = n;
        *head = n;
    }
    else
    {
        n->next = NULL;
        *head = *tail = n;
    }

    return SUCCESS;
}

/* 
 * Function: free_list
 * -------------------
 * Frees all nodes in a doubly linked list.
 */
void free_list(Dlist **head)
{
    Dlist *t;
    while (*head)
    {
        t = *head;
        *head = (*head)->next;
        free(t);
    }
}

/* 
 * Main Function
 * -------------
 * Parses input, builds lists, and performs arithmetic operations
 * on large numbers using linked list representation.
 */
int main(int argc, char* argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    char operator = argv[2][0];
    char sign1 = '+', sign2 = '+';

    // Check for negative signs
    if (argv[1][0] == '-') sign1 = '-';
    if (argv[3][0] == '-') sign2 = '-';

    // Convert argv[1] to linked list
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]))
        {
            insert_at_last(&head1, &tail1, argv[1][i] - '0');
        }
    }

    // Convert argv[3] to linked list
    for (int i = 0; i < strlen(argv[3]); i++)
    {
        if (isdigit(argv[3][i]))
        {
            insert_at_last(&head2, &tail2, argv[3][i] - '0');
        }
    }

    // Count digits and check if numbers are zero
    Dlist *temp1 = head1, *temp2 = head2;
    data_t num1_count = 0, num2_count = 0;
    data_t num1 = 1, num2 = 1;

    while (temp1) { num1_count++; temp1 = temp1->next; }
    if (num1_count == 1 && head1->data == 0) num1 = 0;

    while (temp2) { num2_count++; temp2 = temp2->next; }
    if (num2_count == 1 && head2->data == 0) num2 = 0;

    // Switch-case for operations
    switch (operator)
    {
        case '+':
            // Both positive
            if (sign1 == '+' && sign2 == '+')
            {
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                    print_list(&headR);
            }
            // Both negative
            else if (sign1 == '-' && sign2 == '-')
            {
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                {
                    printf("-");
                    print_list(&headR);
                }
            }
            // One positive, one negative
            else if ((sign1 == '+' && sign2 == '-') || (sign1 == '-' && sign2 == '+'))
            {
                if (compareList(head1, head2) >= 0)
                {
                    if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                        (sign1 == '-') ? printf("-") : 0, print_list(&headR);
                }
                else
                {
                    if (subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == SUCCESS)
                        (sign2 == '-') ? 0 : printf("-"), print_list(&headR);
                }
            }
            break;

        case '-':
            // Both positive or both negative
            if ((sign1 == '+' && sign2 == '+') || (sign1 == '-' && sign2 == '-'))
            {
                if (compareList(head1, head2) >= 0)
                {
                    if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                        (sign1 == '-') ? printf("-") : 0, print_list(&headR);
                }
                else
                {
                    if (subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == SUCCESS)
                        (sign1 == '-') ? 0 : printf("-"), print_list(&headR);
                }
            }
            // Different signs, convert to addition
            else
            {
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                {
                    if (sign1 == '-') printf("-");
                    print_list(&headR);
                }
            }
            break;

        case 'x':
            // Check for multiplication with zero
            if (num1 == 0 || num2 == 0)
            {
                printf("0");
                return 0;
            }
            // Same sign => positive result
            if ((sign1 == '+' && sign2 == '+') || (sign1 == '-' && sign2 == '-'))
            {
                if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                    print_list(&headR);
            }
            // Different signs => negative result
            else
            {
                if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                {
                    printf("-");
                    print_list(&headR);
                }
            }
            break;

        case '/':
            if (num1 == 0)
            {
                printf("0");
                return 0;
            }
            if (num2 == 0)
            {
                printf("Division not possible");
                return 0;
            }
            // Same sign => positive result
            if ((sign1 == '+' && sign2 == '+') || (sign1 == '-' && sign2 == '-'))
            {
                if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                    print_list(&headR);
            }
            // Different signs => negative result
            else
            {
                if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                {
                    printf("-");
                    print_list(&headR);
                }
            }
            break;

        default:
            printf("Invalid Input:-( Try again...\n");
    }

    return 0;
}