#include "shell.h"

/**
* _or - handles logical operator OR
* @head: pointer to head of a linked list
* Return: void
*/
void _or(Node **head, int *status, pid_t *pid)
{
	/*creates ref to the head of linked list*/
	Node *list = *head;
	char *temp[50];
	int i = 0, j = 0;
	
	/*assigns -1 to status for the first command to be executed*/
	*status = -1;
	
	/*itaretes linked list till there are no more nodes*/
	while (list != NULL)
	{
		/*if command in the current node is not "||" the command is duplicated to temp[]*/
		if (strcmp(list->cmd, "||") != 0)
		{
			temp[i++] = strdup(list->cmd);
			temp[i] = NULL;
		}
		/*if command in the current node is "||" OR current node is the last node, commands in temp[] are executed */
		if (strcmp(list->cmd, "||") == 0 || list->next == NULL)
		{
			/*checks if status is not 0 (previous child proces was not successful)*/
			if (*status != 0)
			{
				/*executes commands in temp assigning its exit status to status*/
				*status = myexecve(temp, pid);
				
				/*frees each item in temp[] which is not null and sets it to null*/
				for (j = 0; j < i; j++)
				{
					if (temp[j] != NULL)
					{
						free(temp[j]);
						temp[j] = NULL;
					}
				}
				/*sets i to 0 so that next population(next iteration) of temp[] will start from 0*/
				i = 0;
			}
		}
		/*current node points to next*/
		list = list->next;
	}
	/*frees each item in temp[] which is not null and sets it to null*/
	for (j = 0; j < i; j++)
	{
		if (temp[j] != NULL)
		{
			free(temp[j]);
			temp[j] = NULL;
		}
	}
	
}


/**
* _and - handles logical operator AND
* @head: pointer to head of a linked list
* Return: void
*/
void _and(Node **head, int *status, pid_t *pid)
{
	/*creates ref to the head of linked list*/
	Node *list = *head;
	char *temp[50];
	int i = 0, j = 0;
	
	/*assigns 0 to status for the first command to be executed*/
	*status = 0;
	
	/*itaretes linked list till there are no more nodes*/
	while (list != NULL)
	{
		/*if command in the current node is not "&&", the command is duplicated to temp[]*/
		if (strcmp(list->cmd, "&&") != 0)
		{
			temp[i++] = strdup(list->cmd);
			temp[i] = NULL;
		}
		/*if command in the current node is "&&" OR current node is the last node, commands in temp[] are executed */
		if (strcmp(list->cmd, "&&") == 0 || list->next == NULL)
		{
			/*checks if status is 0 (previous child proces was successful)*/
			if (*status == 0)
			{
				/*executes commands in temp assigning its exit status to status*/
				*status = myexecve(temp, pid);
				
				/*frees each item in temp[] which is not null and sets it to null*/
				for (j = 0; j < i; j++)
				{
					if (temp[j] != NULL)
					{
						free(temp[j]);
						temp[j] = NULL;
					}
				}
				/*sets i to 0 so that next population(next iteration) of temp[] will start from 0*/
				i = 0;
			}
		}
		/*current node points to next*/
		list = list->next;
	}
	
	/*frees each item in temp[] which is not null and sets it to null*/
	for (j = 0; j < i; j++)
	{
		if (temp[j] != NULL)
		{
			free(temp[j]);
			temp[j] = NULL;
		}
	}
	
}



/**
* var_replace - handles variable replacement
* @head: pointer to head of linked list containing commands
* Return: nothing
*/
void var_replace(Node **head, int *status, pid_t *pid)
{
	/*creates reference to second node of the linked list*/
	Node *list = (*head)->next;
	char *str = NULL, *temp = NULL, *path = NULL;
	
	/*checks if command in second node is "$$" and prints pid*/
	if (strcmp(list->cmd, "$$") == 0)
	{
		printf("%d\n", *pid);
	}
	/*checks if command in second node is "$?" and prints status*/
	else if (strcmp(list->cmd, "$?") == 0)
	{
		printf("%d\n", *status);
	} 
	/*prints content of cmd in second node followed by  a new line*/
	else
	{
		temp = strdup(list->cmd);
		str = strndup(temp+1, strlen(temp)-1);
		path = _getenv(str);
		write(STDOUT_FILENO, path, strlen(path));
		write(STDOUT_FILENO, "\n", 1);

	}
	/*checks if temp is not null and frees it*/
	if (temp != NULL)
	{
		free(temp);
		temp = NULL;
	}
	/*checks if str is not null and frees it*/
	if (str != NULL)
	{
		free(str);
		temp = NULL;
	}
}























	
