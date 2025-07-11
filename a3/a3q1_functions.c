#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

Variable variables[10];
int varCount = 0;

// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node *createNode(char *data)
{
    Node *new = malloc(sizeof(Node));
    strncpy(new->data, data, 10);
    new->left = NULL;
    new->right = NULL;
    return new;
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node *parseExpression(char *expr)
{
    static int index = 0; // Static variable to keep track of the current position in the expression string
    Node *node = NULL;

    // Skip initial '(' if present
    if (expr[index] == '(')
    {
        index++;
    }

    // Parse the left operand (number, variable, or subexpression)
    if (isdigit(expr[index]) || expr[index] == '.')
    {
        char num[10];
        int j = 0;
        while (isdigit(expr[index]) || expr[index] == '.')
        {
            num[j++] = expr[index++];
        }
        num[j] = '\0';
        node = createNode(num); // Create a node for the number
    }
    else if (isalpha(expr[index]))
    {
        char var[10];
        int j = 0;
        while (isdigit(expr[index]) || isalpha(expr[index]))
        {
            var[j++] = expr[index++];
        }
        var[j] = '\0';
        node = createNode(var); // Create a node for the variable
    }
    else if (expr[index] == '(')
    {
        node = parseExpression(expr); // Parse nested expression
    }

    // Skip whitespace if present
    while (expr[index] == ' ')
    {
        index++;
    }

    // Parse the operator and create an operator node if applicable
    if (expr[index] == '+' || expr[index] == '-' || expr[index] == '*' || expr[index] == '/')
    {
        char op[2] = {expr[index], '\0'};
        Node *opNode = createNode(op); // Create node for the operator
        opNode->left = node;           // Attach the current subtree as the left child
        index++;                       // Move past the operator

        // Recursively parse the right operand
        opNode->right = parseExpression(expr);
        node = opNode; // Update node to be the operator node
    }

    // Skip closing ')' if present
    if (expr[index] == ')')
    {
        index++;
    }

    return node;
}

// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root)
{
    if (root)
    {
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root)
{
    if (root)
    {
        if (root->left)
        {
            printf("(");
        }
        inorder(root->left);
        printf("%s ", root->data);
        inorder(root->right);
        if (root->right)
        {
            printf(")");
        }
    }
}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->data);
    }
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root)
{
    if (root != NULL)
    {
        if (isalpha(root->data[0]))
        { // Check if it's a variable
            int found = 0;
            for (int i = 0; i < varCount; i++)
            {
                if (strcmp(root->data, variables[i].varName) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                printf("Enter value for variable %s: ", root->data);
                scanf("%f", &variables[varCount].value);
                strncpy(variables[varCount].varName, root->data, 10);
                varCount++;
            }
        }
        promptVariables(root->left);
        promptVariables(root->right);
    }
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root)
{
    double result = 0.0;
    if (root == NULL)
        return result;

    // If the node is a number, convert and return its value
    if (isdigit(root->data[0]) || (root->data[0] == '-' && isdigit(root->data[1])))
    {
        return atof(root->data);
    }

    // If the node is a variable, look up its value
    if (isalpha(root->data[0]))
    {
        for (int i = 0; i < varCount; i++)
        {
            if (strcmp(root->data, variables[i].varName) == 0)
            {
                return variables[i].value;
            }
        }
        printf("Error: Variable %s not found. Using default value 0.0.\n", root->data);
        return 0.0; // Assume 0 if variable is not found
    }

    // Recursively calculate the left and right subtree values
    float leftVal = calculate(root->left);
    float rightVal = calculate(root->right);

    // Evaluate based on the operator at the current node
    if (strcmp(root->data, "+") == 0)
    {
        result += leftVal + rightVal;
        return result;
    }
    else if (strcmp(root->data, "-") == 0)
    {
        result += leftVal - rightVal;
        return result;
    }
    else if (strcmp(root->data, "*") == 0)
    {
        result += leftVal * rightVal;
        return result;
    }
    else if (strcmp(root->data, "/") == 0)
    {
        if (rightVal == 0.0)
        {
            printf("Error: Division by zero.\n");
            return 0.0;
        }
        result += leftVal / rightVal;
        return result;
    }

    printf("Error: Unrecognized operator %s.\n", root->data);
    return 0.0; // Return 0.0 for any unexpected cases
}
