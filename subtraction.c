#include "apc.h"
#include <stdlib.h>

/*
 * Function: subtraction
 * ---------------------
 * Subtracts the second number (head2-tail2) from the first number (head1-tail1),
 * both represented as doubly linked lists where each node contains a single digit.
 *
 * Parameters:
 *   head1, tail1 - pointers to the head and tail of the first number list
 *   head2, tail2 - pointers to the head and tail of the second number list
 *   headR, tailR - pointers to store the head and tail of the result list
 *
 * Returns:
 *   SUCCESS if subtraction is performed correctly
 *
 * Note:
 *   - Assumes first number is greater than or equal to the second number.
 *   - Implements the elementary school subtraction logic with borrowing.
 */
data_t subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    data_t borrow = 0;  // Holds borrow from previous digit subtraction
    int a, b, diff;

    // Loop through each digit of the first number (from LSB to MSB)
    while ((*tail1) != NULL)
    {
        // Get current digit of first number minus any borrow
        a = (*tail1)->data - borrow;

        // If second number still has digits, take it; otherwise assume zero
        if ((*tail2) != NULL)
            b = (*tail2)->data;
        else
            b = 0;

        // If current digit of first number is smaller than second number's digit, borrow 10
        if (a < b)
        {
            a += 10;
            borrow = 1;  // Set borrow for next iteration
        }
        else
        {
            borrow = 0;
        }

        // Subtract current digits
        diff = a - b;

        // Insert result at the head of the result list (MSB builds at the end)
        insert_at_first(headR, tailR, diff);

        // Move to next higher digit in both numbers
        *tail1 = (*tail1)->prev;
        if (*tail2 != NULL)
            *tail2 = (*tail2)->prev;
    }

    return SUCCESS;
}




/*
 * Function: sub_for_div
 * ---------------------
 * Performs subtraction of two numbers like `subtraction` but tailored for use in division logic.
 * Uses simpler variable names and no nested pointer dereferencing.
 *
 * Parameters:
 *   head1, tail1 - pointers to the first number (dividend or partial remainder)
 *   head2, tail2 - pointers to the second number (divisor)
 *   headR, tailR - pointers to store the result of subtraction
 *
 * Returns:
 *   SUCCESS after subtraction
 *
 * Logic:
 *   - Traverses from the least significant digit (tail) backward.
 *   - Subtracts digit by digit while handling borrow.
 */
data_t sub_for_div(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	int borrow = 0;             // Borrow flag for subtraction
	Dlist *p = *tail1, *q = *tail2;  // Pointers to traverse both numbers from tail to head

	// Loop through each digit in the first number
	while (p)
	{
	int x = p->data - borrow;      // Subtract previous borrow
	int y = q ? q->data : 0;       // Take digit from second number if exists, else 0

	// Handle borrow if needed
	if (x < y)
	{
	x += 10;
	borrow = 1;
	}
	else
	{
	borrow = 0;
	}

	// Store result of subtraction in the result list
	insert_at_first(headR, tailR, x - y);

	// Move to next digits (leftward)
	p = p->prev;
	if (q) q = q->prev;
	}

	return SUCCESS;
}


