#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Please enter a valid expression!");
    return 0;
  }

  // Pointer to the stack
  int i = 0;
  Operand *stack = NULL;

  // Loop through the second command line arguement, containing the operands and the numbers
  for (i = 0; i < strlen(argv[1]); ++i)
  {
    char temp = argv[1][i];
    printf("%s", argv[1]);
    printf("%c", temp);
    if (isdigit(temp))
    {
      push(&stack, temp - '0');
    }
    else if (temp == '+' || temp == '*' || temp == '/' || temp == '-')
    {
      double operand2 = pop(&stack);
      double operand1 = pop(&stack);
      double result;
      switch (temp)
      {
      case '+':
        result = operand1 + operand2;
        break;

      case '-':
        result = operand1 - operand2;
        break;

      case '*':
        result = operand1 * operand2;
        break;

      case '/':
        if (operand2 == 0)
        {
          printf("A number cannot be divided by 0.");
          return 0;
        }
        result = operand1 / operand2;
        break;

      default:
        printf("Invalid operator\n");
        return 0;
      }
      push(&stack, result);
    }
    else
    {
      printf("Invalid character\n");
      return 0;
    }
  }

  if (stack != NULL && stack->next == NULL)
  {
    double finalResult = pop(&stack);
    printf("Result: %.2lf\n", finalResult);
  }
  else
  {
    printf("Invalid\n");
    return 0;
  }

  return 0;
}