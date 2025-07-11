/*
Name:
Student ID:
Assignment 2, Question 2
*/

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Pushes a new value onto the stack.
 *
 * @param stack Pointer to the pointer of the stack's head.
 * @param value The value to be added to the stack.
 */
void push(Operand **stack, double value)
{
    Operand *newNode = malloc(sizeof(Operand));
    if (!newNode)
    {
        printf("Memory allocation failed \n");
        return;
    }
    newNode->value = value;
    newNode->next = *stack;
    *stack = newNode;
}

/**
 * Pops the top value from the stack and returns it.
 *
 * @param stack Pointer to the pointer of the stack's head.
 * @return The value that was at the top of the stack.
 */
double pop(Operand **stack)
{
    if (*stack == NULL)
    {
        printf("Stack is empty \n");
        return 0;
    }
    Operand *node = *stack;
    double value = node->value;
    *stack = (*stack)->next;
    free(node);
    return value;
}

/**
 * Prints all values in the stack.
 *
 * @param stack Pointer to the stack's head.
 */
void print(Operand *stack)
{
    Operand *temp = stack;
    while (temp == NULL)
    {
        printf("%lf -> ", temp->value);
        temp = temp->next;
    }
}