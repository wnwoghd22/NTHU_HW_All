#ifndef __SYMBOLTABLE__
#define __SYMBOLTABLE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200
#define MAXTOKENLEN 50

#define TRUE 1
#define FALSE 0

#define INT_TYPE 0
#define DOUBLE_TYPE 1
#define CHAR_TYPE 2 
#define FLOAT_TYPE 3

typedef char* string;

typedef struct _Node
{
	char name[MAXTOKENLEN];
	int type;
	int offset;

	int intVal;
	double doubleVal;
	char charVal;

	struct _Node* next;
} Node;

typedef struct _TreeNode
{
	char value[MAXTOKENLEN];
	int intVal;
	int Expr;
	int Print;
	
	struct _TreeNode* right;
	struct _TreeNode* left;
} TreeNode;

static TreeNode* Expression;

void PrintTag(TreeNode* _node)
{
	if(_node->Expr == TRUE)
		printf("<expr>");
	if(_node->value[0] == '[')
		printf("[");
	if(_node->value[0] == '(')
		printf("(");

	if(_node->left != NULL)
		PrintTag(_node->left);

	{
		if(_node->Print == 1)
			printf("%s", _node->value);
		else if(_node->Print == 2)
			printf("%d", _node->intVal);
	}

	if(_node->value[0] == '[')
		printf("]");

	if(_node->right != NULL)
		PrintTag(_node->right);

	if(_node->value[0] == '(')
		printf(")");
	
	if(_node->Expr == TRUE)
		printf("</expr>");

	free(_node);
}

static Node* Table;

void Insert(int type, string name, int lineNo)
{
	Node* temp;
	temp = Table;
	int index = 0;
	while (temp->next != NULL)
	{
		if (strcmp(name, temp->next->name) == 0)
		{
			perror("redefine!");
			return;
		}
		temp = temp->next;
		index++;
	}
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->type = type;
	newNode->offset = index;
	newNode->next = NULL;
	temp->next = newNode;
}

Node* GetNode(string name)
{
	Node* temp = Table->next;
	while ((strcmp(name, temp->name) != 0))
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
	}
	return temp;
}

//return value of symbol(name)
int GetValue(string name)
{
	Node* temp = Table->next;

	while ((strcmp(name, temp->name) != 0))
	{
		temp = temp->next;
		if (temp == NULL)
			return -1;
	}
	
	return temp->intVal;
}
//set value(v) of symbol(name)
int SetValue(string name, int v)
{
	Node* temp = Table->next;

	while ((strcmp(name, temp->name) != 0))
	{
		temp = temp->next;
		if(temp == NULL)
			return -1;
	}
	
	temp->intVal = v;
	return 0;
}

void PrintType(int _type)
{
	switch(_type)
	{
		case INT_TYPE:
			printf("int");
			break;
		case DOUBLE_TYPE:
			printf("double");
			break;
		case FLOAT_TYPE:
			printf("float");
			break;
		case CHAR_TYPE:
			printf("char");
			break;
		default:
			break;
	}
}
//get data type
int GetType(string name)
{
	Node* temp = Table->next;

	while ((strcmp(name, temp->name) != 0))
	{
		temp = temp->next;
		if (temp == NULL)
			return -1;
	}

	return temp->type;
}
//set data type(t)
int SetType(string name, int t)
{
	Node* temp = Table->next;

	while ((strcmp(name, temp->name) != 0))
	{
		temp = temp->next;
		if (temp == NULL)
			return -1;
	}

	temp->type = t;
	return 0;
}

typedef struct _parameter
{
	int type;
	char name[MAXTOKENLEN];
	struct _parameter* next;
} Parameter;

void PrintParameter(Parameter* _par)
{
	Parameter* temp = _par;
	while(temp != NULL)
	{
		PrintType(temp->type);
		printf("%s", temp->name);

		temp = temp->next;
		if(temp != NULL)
			printf(",");
	}
}

static Parameter* parameter;

#endif
