#pragma once
#ifndef __MYCALCULATOR_H__
#define __MYCALCULATOR_H__
#define EQUATION_SIZE 512

typedef double Data;

typedef enum
{
	FALSE,
	TRUE
} Boolean;

typedef enum
{
	plus = 1,
	minus,
	times,
	dividedBy,
	open,
	close
} Operator;

typedef struct _node
{
	Data data;
	Operator oper;
	struct _node* next;
} Node;

typedef struct _StackInfo
{
	int numberOfElement;
	Node* head;
} Stack;

int sIsEmpty(Stack* pstack);
void pushSD(Stack* pstack, Data data);
void pushSO(Stack* pstack, Operator oper);
Data popSD(Stack* pstack);
Operator popSO(Stack* pstack);
Operator peepSO(Stack* pstack);

void clearInputBuffer(char* string, int sizeOfAlloc);
void deleteSpace(char* equation);
void charToStack(char* equation, Stack* pstack);
void infixToPostfix(Stack* pstack);
Data calculatePostfix(Stack* pstack);

Data operation(Data d, Data f, Operator oper);
int getOperationPriority(Operator oper);
int whoPreceedOperator(Operator oper1, Operator oper2);
Operator charToOperator(char oper);

#endif
