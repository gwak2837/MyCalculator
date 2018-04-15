#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyCalculator.h"

int main()
{
	double result;
	char* equation = (char*)malloc(EQUATION_SIZE);
	Stack* stack = (Stack*)calloc(1, sizeof(Stack)); // Allocates memory and initializes stack information
	
	fputs("Input infix equation : ", stdout);
	fgets(equation, EQUATION_SIZE, stdin);
	clearInputBuffer(equation, EQUATION_SIZE);
	deleteSpace(equation);
	equation = (char*)realloc(equation, strlen(equation) + 1);

	charToStack(equation, stack);
	infixToPostfix(stack);
	result = calculatePostfix(stack);

	printf("\nResult : %f\n", result);
	system("pause");
	return 0;
}
