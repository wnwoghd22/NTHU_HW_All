#include "stdio.h"
#include "symboltable.h"

int main()
{
	Parameter* temp = (Parameter*)malloc(sizeof(Parameter));
	temp->type = 1;
	strcpy_s(temp->name, 2, "a");
	temp->next = NULL;
	parameter = temp;

	PrintParameter(parameter);
	
	return 0;
}