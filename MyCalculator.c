#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyCalculator.h"

//stack is empty
int sIsEmpty(Stack* pstack)
{
	if (pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

//push stack data
void pushSD(Stack* pstack, Data data)
{
	Node* newnode = (Node*)calloc(1, sizeof(Node));

	newnode->data = data;
	newnode->next = pstack->head;

	pstack->head = newnode;
	(pstack->numberOfElement)++;
}

//pop stack data
Data popSD(Stack* pstack)
{
	Data data = pstack->head->data;
	Node* node = pstack->head;

	if (sIsEmpty(pstack))
	{
		puts("Stack is already empty.");
		exit(1);
	}

	pstack->head = pstack->head->next;
	free(node);

	(pstack->numberOfElement)--;
	return data;
}

//push stack operator
void pushSO(Stack* pstack, Operator oper)
{
	Node* newnode = (Node*)calloc(1, sizeof(Node));

	newnode->oper = oper;
	newnode->next = pstack->head;

	pstack->head = newnode;
	(pstack->numberOfElement)++;
}

//pop stack operator
Operator popSO(Stack* pstack)
{
	Operator oper = pstack->head->oper;
	Node* node = pstack->head;

	if (sIsEmpty(pstack))
	{
		puts("Stack is already empty.");
		exit(1);
	}

	pstack->head = pstack->head->next;
	free(node);

	(pstack->numberOfElement)--;
	return oper;
}

//peep stack operator
Operator peepSO(Stack* pstack)
{
	if (sIsEmpty(pstack))
	{
		puts("Stack is already empty.");
		exit(1);
	}

	return pstack->head->oper;
}

void clearInputBuffer(char* string, int sizeOfAlloc)
{
	int length = strlen(string);
	if (length + 1 < sizeOfAlloc)
		string[length - 1] = '\0';
	else if(string[sizeOfAlloc - 2] == '\n')
		string[length - 1] = '\0';
	else
		while (getchar() != '\n');
}

void deleteSpace(char* string)
{
	int index = 0;
	int numOfSpace = -1;
	int length = strlen(string);

	while (string[index] != ' ')
		index++;

	for (; index < length; index++)
	{
		if (string[index] == ' ')
			numOfSpace++;
		string[index - numOfSpace] = string[index + 1];
	}
}

void charToStack(char* equation, Stack* pstack)
{
	int i;
	for (i = strlen(equation) - 1; i > -1; i--)
	{
		if (equation[i] >= '0' && equation[i] <= '9' || equation[i] == '.')
		{
			while (i > -1 && equation[i] != '+' && equation[i] != '-' && equation[i] != '*' && equation[i] != '/' && equation[i] != '(')
				i--;
			i++;
			pushSD(pstack, atof(equation + i));
		}
		else
			pushSO(pstack, charToOperator(equation[i]));
	}
}

void infixToPostfix(Stack* pstack)
{
	Stack* operStack = (Stack*)calloc(1, sizeof(Stack));
	int equationLength = pstack->numberOfElement;
	Stack* tempStack = (Stack*)calloc(1, sizeof(Stack));

	int i, index = 0;
	Operator token, popOper;

	for (i = 0; i < equationLength; i++)
	{
		if (pstack->head->oper == 0)
			pushSD(tempStack, popSD(pstack));
		else
		{
			switch (token = popSO(pstack))
			{
			case open:
				pushSO(operStack, token);
				break;
			case close:
				while (1)
				{
					popOper = popSO(operStack);
					if (popOper == open)
						break;
					pushSO(tempStack, popOper);
				}
				break;
			case plus: case minus:
			case times: case dividedBy:
				while (!sIsEmpty(operStack) && whoPreceedOperator(peepSO(operStack), token) >= 0)
					pushSO(tempStack, popSO(operStack));
				pushSO(operStack, token);
				break;
			}
		}
	}

	while (!sIsEmpty(operStack))
		pushSO(tempStack, popSO(operStack));

	int length = tempStack->numberOfElement;
	for (int i = 0; i < length; i++)
	{
		if (tempStack->head->oper == 0)
			pushSD(pstack, popSD(tempStack));
		else
			pushSO(pstack, popSO(tempStack));
	}
	free(tempStack);
}

Data calculatePostfix(Stack* pstack)
{
	Stack* temp = (Stack*)calloc(1, sizeof(Stack)); // Allocates memory and initializes stack information
	Data first, second;
	int length = pstack->numberOfElement;
	for (int i = 0; i < length; i++)
	{
		if (pstack->head->oper == 0) // 숫자면
			pushSD(temp, popSD(pstack));
		else                         // 연산자면
		{
			second = popSD(temp);
			first = popSD(temp);
			pushSD(temp, operation(first, second, popSO(pstack)));
		}
	}
	return popSD(temp);
}

Data operation(Data operand1, Data operand2, Operator oper)
{
	switch (oper)
	{
	case plus:
		return operand1 + operand2;
	case minus:
		return operand1 - operand2;
	case times:
		return operand1 * operand2;
	case dividedBy:
		return operand1 / operand2;
	default:
		puts("\nThe unvalid four fundamental arithmetic operations. Exit program...\n");
		system("pause");
		exit(3);
	}
}

int getOperationPriority(Operator oper)
{
	switch (oper)
	{
	case times:
	case dividedBy:
		return 10;
	case plus:
	case minus:
		return 5;
	case open:
		return 1;
	}

	return -1;
}

int whoPreceedOperator(Operator oper1, Operator oper2)
{
	int oper1Priority = getOperationPriority(oper1);
	int oper2Priority = getOperationPriority(oper2);

	if (oper1Priority > oper2Priority)
		return 1;
	else if (oper1Priority < oper2Priority)
		return -1;
	else
		return 0;
}


Operator charToOperator(char op)
{
	switch (op)
	{
	case '+':
		return plus;
	case '-':
		return minus;
	case '*':
		return times;
	case '/':
		return dividedBy;
	case '(':
		return open;
	case ')':
		return close;
	default:
		printf("\nUnvalid operator in equation. Exit program...\n");
		system("pause");
		exit(2);
	}
}
