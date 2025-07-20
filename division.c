#include "apc.h"

/*
 * Function: multiply_by_digit
 * ---------------------------
 * Multiplies a large number represented by a doubly linked list with a single digit (0–9).
 * It performs the multiplication digit-by-digit from the least significant digit and
 * handles carry over properly.
 *
 * Parameters:
 *   head, tail    - Pointers to the number's head and tail (doubly linked list)
 *   d             - Single digit multiplier (0–9)
 *   headR, tailR  - Pointers to the head and tail of the result list
 */
void multiply_by_digit(Dlist *head, Dlist *tail, int d, Dlist **headR, Dlist **tailR)
{
    int carry = 0;

    // Traverse from tail (least significant digit) to head (most significant)
    for (Dlist *p = tail; p; p = p->prev) {
        int prod = p->data * d + carry;     // Multiply digit and add carry
        insert_at_first(headR, tailR, prod % 10); // Store the unit digit
        carry = prod / 10;                  // Update carry for next iteration
    }

    // If there's any remaining carry, add it as new digit(s)
    while (carry) {
        insert_at_first(headR, tailR, carry % 10);
        carry /= 10;
    }
}



/*
 * Function: division
 * ------------------
 * Performs long division (digit-by-digit) of two large numbers represented as doubly linked lists.
 *
 * Parameters:
 *   head1, tail1  - Dividend (linked list form)
 *   head2, tail2  - Divisor (linked list form)
 *   headQ, tailQ  - Pointers to hold the quotient (result)
 *
 * Returns:
 *   SUCCESS if division completed properly, FAILURE otherwise.
 *
 * Key Steps:
 *   1. Bring down one digit at a time to form partial dividend.
 *   2. Remove leading zeros from partial dividend.
 *   3. Use binary search (0–9) to find best quotient digit such that (divisor * digit) ≤ partial dividend.
 *   4. Subtract the product from partial dividend.
 *   5. Append the found digit to the quotient list.
 */
data_t division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,Dlist **headQ, Dlist **tailQ)
{
// Return FAILURE if either number is NULL
    if (!*head1 || !*head2)
        return FAILURE;

    // Return FAILURE if divisor is zero
    if (!(*head2)->next && (*head2)->data == 0)
        return FAILURE;

    Dlist *rem = NULL, *remT = NULL;  // Remainder list
    Dlist *p = *head1;                // Pointer to traverse dividend

    // Process each digit in dividend one-by-one
    while (p) {
        // Step 1: Bring down next digit from dividend
        insert_at_last(&rem, &remT, p->data);

        // Step 2: Strip leading zeros in remainder
        while (rem && rem->data == 0 && rem->next) {
            Dlist *z = rem;
            rem = rem->next;
            rem->prev = NULL;
            free(z);  // Free unused leading 0 node
        }

        // Step 3: Binary search for best quotient digit [0–9]
        int lo = 0, hi = 9, best = 0;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;  // Midpoint of current search
            Dlist *prod = NULL, *prodT = NULL;

            // Multiply divisor with mid and store in prod
            multiply_by_digit(*head2, *tail2, mid, &prod, &prodT);

            // Compare product with current remainder
            int cmp = compareList(prod, rem);

            free_list(&prod);  // Free the product list after comparison

            if (cmp <= 0) {
                best = mid;    // Valid digit; try higher
                lo = mid + 1;
            } else {
                hi = mid - 1;  // Too large; try smaller
            }
        }

        // Step 4: Subtract best × divisor from remainder
        if (best) {
            Dlist *prod = NULL, *prodT = NULL;
            multiply_by_digit(*head2, *tail2, best, &prod, &prodT);

            Dlist *newR = NULL, *newT = NULL;

            // Subtract product from current remainder
            sub_for_div(&rem, &remT, &prod, &prodT, &newR, &newT);

            free_list(&rem);  // Free old remainder
            rem  = newR;      // Set updated remainder
            remT = newT;

            free_list(&prod); // Free used product list
        }

        // Step 5: Append determined quotient digit to result list
        insert_at_last(headQ, tailQ, best);

        p = p->next;  // Move to next digit in dividend
    }

    // Final Step: Strip leading zeros from the quotient
    while (*headQ && (*headQ)->data == 0 && (*headQ)->next) {
        Dlist *z = *headQ;
        *headQ = (*headQ)->next;
        (*headQ)->prev = NULL;
        free(z);  // Remove leading 0 from quotient
    }

    return SUCCESS;
}
