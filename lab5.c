#include <stdio.h>
#include <string.h>
#include <stdlib.h>

union hospitalInformation
{
float fever;
char pain[20];
int daysSick;
};

typedef struct node 
{
struct node *next;
int departmentNumber;
char name[20] ;
union hospitalInformation details;
}NODE;

NODE * head = NULL;
NODE * tail = NULL;

void
show_dept(int enteredNumber)
{
       

	NODE * current = head;

	while(current != NULL)
	{
		if (enteredNumber == current -> departmentNumber)
		{
			printf("%s\n", current->name);
		}
	current = current->next;
	}
}

void 
removePatient(int enteredNumber) 
{

	NODE *current, *previous;
	current = previous = head;
	

	while(current!= NULL) 
	{
		if (current -> departmentNumber == enteredNumber) //moves each name and department number up in the array  
		{
			if (current == head) 
			{
				head = head->next;
				free(current);		
			}
			else if (current== tail)
			{
				tail = previous;
				previous-> next = NULL;
				free(current);
			}
			else 
			{
				previous->next = current->next;
				free(current);
			}	
		break;
		}
		previous = current;
		current = current->next;
	}
}

int
check_duplicate(char nameOne[])
{ 
	NODE * current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, nameOne) == 0)
		{
			printf("Sorry, this name has already been entered in our system \n");
			return 1;
		}
		current = current ->next;

	}
	return 0;
}


void 
insert (char *nameOne, int tempDepartment) 
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	
	strcpy(temp-> name, nameOne);
	temp->next = NULL;
	temp->departmentNumber = tempDepartment;
	if (temp == NULL)
	{
		return;
	}
	if (head == NULL)
	{
		head = tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}

	if (tempDepartment == 1)
	{
		printf("Enter the fever temperature of the patient: \n\n ");
		scanf("%f",&temp ->details.fever);
	}
	else if (tempDepartment ==2)
	{
		printf("Enter the type of pain the patient has: \n\n");
		scanf("%s",temp->details.pain);
	}
	else if (tempDepartment == 3 || tempDepartment == 4)
	{
		printf("Enter the number of days that the patient has been sick: \n\n");
		scanf("%d",&temp->details.daysSick);
	}
}
 

void
list()
{
	NODE * current = head;
	
	printf("Name| \t\t Department| \t\t Patient Info|\n");
	while(current != NULL) 
	{
		printf("%s\t\t %d \t\t \t", current->name, current-> departmentNumber);
		if (current-> departmentNumber == 1)
		{
			 printf("Fever:%f\n", current-> details.fever);
                }
                else if (current-> departmentNumber == 2)
                {
                         printf ("Type of pain:%s\n", current-> details.pain);
                }
                else if (current-> departmentNumber == 3 || current-> departmentNumber == 4)
                {
                         printf ("Days Sick:%d\n", current-> details.daysSick);
                } 
	current = current->next;
	}

}

void 
displayPatientDetails(char nameGiven[])
{
	NODE * current = head;
	while(current != NULL)
	{
		if (strcmp(current-> name, nameGiven) == 0)
		{ 
			if (current-> departmentNumber == 1)
			{
				printf("%s temperature is: %f \n", current-> name, current-> details.fever);
			}
			else if (current-> departmentNumber == 2)
			{
				printf ("%s has: %s \n", current-> name, current-> details.pain);
			}
			else if (current-> departmentNumber == 3 || current-> departmentNumber == 4)
			{
				printf ("%s has been in the hospital for %d days \n", current-> name, current-> details.daysSick);
			}
		}
		else
		{
		printf("Sorry that patient cannot be found");
		}
		current = current->next;
	}
	return;
} 	


int main() 
{
	int tempDepartment;
	char tempArray[20];
	int enteredNumber;
	char enteredName[20];
	while(1) 
	{
		printf(" Enter '1' in Order to Add Your Name and Department\n\n Enter '2' In Order to View the List of Patients\n\n Enter '3' in order to remove a patient\n\n Enter '4 in order to view patients in a department \n\n Enter '0' In Order to Quit the Program\n\n ");
		scanf("%d", &enteredNumber);
	
		if (enteredNumber < 1 || enteredNumber > 5)
		{
			return 0;
		}
		else 
		{
	 		if (enteredNumber == 1) 
			{
				printf("Enter the name of the patient:\n\n");
				scanf("%s", tempArray);
				printf("Enter the department of the patient(1-4)\n\n");
				scanf("%d", &tempDepartment);
				insert(tempArray,tempDepartment);
			}
			else if (enteredNumber == 2) 
			{
				list();
			}
			else if (enteredNumber == 3)
			{
				printf("Enter the department in which you want to remove the patient that has been there the longest\n\n");
				scanf("%d", &enteredNumber);
				removePatient(enteredNumber);
			}
			else if (enteredNumber == 4) 
			{
				printf("Enter the department number in which you want to view all the patients in that department\n\n");
				scanf("%d", &enteredNumber); 
				show_dept(enteredNumber);
			}
			else if (enteredNumber == 5)
			{
				printf("Enter the name of the patient that you want to know their condition\n\n");
				scanf("%s",enteredName);
				displayPatientDetails(enteredName); 
			}
		}
	}
	
}











