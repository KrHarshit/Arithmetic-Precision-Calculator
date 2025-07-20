#include "apc.h"
/*
 * Function: addition
 * ------------------
 * Adds two numbers represented as doubly linked lists. Each node contains a single digit.
 * The digits are stored in reverse order, meaning the least significant digit is at the tail.
 *
 * Parameters:
 *   head1, tail1 - Pointers to the head and tail of the first number's digit list.
 *   head2, tail2 - Pointers to the head and tail of the second number's digit list.
 *   headR, tailR - Pointers to store the head and tail of the resulting sum list.
 *
 * Returns:
 *   SUCCESS - when addition is completed successfully.
 *
 * Logic:
 *   - Start from the least significant digit (tail) of both numbers.
 *   - Add corresponding digits with carry.
 *   - Store the result (mod 10) in the result list and carry over the quotient (div 10).
 *   - If carry remains after finishing all digits, insert it into the result.
 */

data_t addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	data_t carry = 0;                  // Carry for addition, initialized to 0
	Dlist *temp1 = *tail1;             // Pointer to traverse the first number from tail
	Dlist *temp2 = *tail2;             // Pointer to traverse the second number from tail

	// Loop through both numbers from least significant digit to most
	while (temp1 != NULL || temp2 != NULL)
	{
		data_t sum = carry;            // Start sum with the current carry

		// If there is a digit left in the first number, add it to sum
		if (temp1 != NULL)
		{
		sum += temp1->data;
		temp1 = temp1->prev;       // Move to the next digit (toward head)
		}

		// If there is a digit left in the second number, add it to sum
		if (temp2 != NULL)
		{
		sum += temp2->data;
		temp2 = temp2->prev;       // Move to the next digit (toward head)
		}

		carry = sum / 10;              // Calculate carry for next iteration
		insert_at_first(headR, tailR, sum % 10);  // Insert the digit (sum mod 10) at the front of result list
	}

	// If carry is still left after loop, insert it at the front
	if (carry > 0)
	insert_at_first(headR, tailR, carry);

	return SUCCESS;
}

