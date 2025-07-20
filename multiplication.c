#include "apc.h"

/*
 * Function: multiplication
 * ------------------------
 * Multiplies two large numbers represented as doubly linked lists.
 *
 * Parameters:
 *   head1, tail1 - pointers to the head and tail of the first number list
 *   head2, tail2 - pointers to the head and tail of the second number list
 *   headR, tailR - pointers to store the head and tail of the result list
 *
 * Returns:
 *   SUCCESS if multiplication is performed correctly
 *
 * Logic:
 *   This function mimics the manual long multiplication process:
 *   - For each digit in the second number (from LSB to MSB),
 *     multiply it with the entire first number.
 *   - Shift the result based on its digit position (adding trailing zeroes).
 *   - Accumulate all intermediate results using addition.
 */
data_t multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    data_t count = 0;  // Keeps track of position to add trailing zeros for place value

    // temp2 will accumulate the final multiplication result
    Dlist *temp2 = NULL, *temp_tail2 = NULL;

    // Loop through each digit of the second number (starting from LSB)
    while ((*tail2) != NULL)
    {
        // temp1 holds the result of multiplication with current digit of second number
        Dlist *temp1 = NULL, *temp_tail1 = NULL;

        // Add 'count' number of trailing zeros to shift result according to digit place
        for (data_t i = 1; i <= count; i++)
        {
            insert_at_first(&temp1, &temp_tail1, 0);
        }

        data_t prod = 1;    // Holds product of digits
        data_t carry = 0;   // Holds carry-over during multiplication

        Dlist *temp = *tail1;  // Start from LSB of first number

        // Multiply current digit of second number with all digits of first number
        while ((temp) != NULL)
        {
            prod = (*tail2)->data * (temp)->data + carry;  // Single digit multiplication + carry
            carry = prod / 10;                             // Carry for next step
            insert_at_first(&temp1, &temp_tail1, prod % 10); // Store unit digit of result
            temp = temp->prev;                             // Move to next higher digit of first number
        }

        // If any carry remains after inner loop, add it to the result
        if (carry > 0)
        {
            insert_at_first(&temp1, &temp_tail1, carry);
        }

        // temp_sum will store the result of adding temp1 with accumulated result temp2
        Dlist *temp_sum = NULL, *temp_tail_sum = NULL;

        // Add the current intermediate result to previously accumulated result
        addition(&temp1, &temp_tail1, &temp2, &temp_tail2, &temp_sum, &temp_tail_sum);

        // Update accumulated result pointers
        temp2 = temp_sum;
        temp_tail2 = temp_tail_sum;

        // Move to the next digit in second number (next higher digit)
        *tail2 = (*tail2)->prev;
        count++;  // Increase position count for trailing zeros
    }

    // Set final result pointers
    *headR = temp2;
    *tailR = temp_tail2;

    return SUCCESS;
}
