#include <stdio.h>
#include <string.h>


union hospitalInformation
{
float fever;
char pain[20];
int daysSick;
};

struct info 
{
int departmentNumber;
char name[20] ;
union hospitalInformation details;
};

struct info patientInfo[10];


int enteredNumber;

int counter = 0;



void
show_dept(enteredNumber)
{


	struct info * a = patientInfo;
	int i;
	for (i = 0; i < counter; i++, a++)
	{
		if (enteredNumber == a -> departmentNumber)
		{
			printf("%s\n", a->name);
		}
	}
}

void 
removePatient(int enteredNumber) 
{

	struct info * a = patientInfo;
	int i;
	for (i = 0; i < counter; i++, a++) 
	{
		if (a -> departmentNumber == enteredNumber) //moves each name and department number up in the array  
		{
			int j;
			struct info *b = a + 1;
			for (j = i; j < counter - 1 ; j++, a++, b++) 
			{
				*a = *b;		
			}
			counter -= 1;
			return;	
		}

	}
}

int
check_duplicate(char nameOne[])
{
	int i; 
	struct info * a = patientInfo;
	for (i = 0; i < 20; i++,a++)
	{
		if (strcmp(a -> name, nameOne) == 0)
		{
			printf("Sorry, this name has already been entered in our system \n");
			return 1;
		}

	}
	return 0;
}


void 
insert (char *nameOne, int tempDepartment) 
{
	if (check_duplicate(nameOne) == 0 && counter < 10)

	{					
		strcpy(patientInfo[counter].name, nameOne);
		patientInfo[counter].departmentNumber = tempDepartment;
		if (tempDepartment == 1)
		{
			scanf("%f",&patientInfo[counter].details.fever);
		}
		else if (tempDepartment ==2)
		{
			printf("Enter the type of pain the patient has: \n");
			scanf("%s",&patientInfo[counter].details.pain);
		}
		else if (tempDepartment == 3 || tempDepartment == 4)
		{
			printf("Enter the number of days that the patient has been sick: \n");
			scanf("%d",&patientInfo[counter].details.daysSick);
		}
		counter++;					
	}
	else 
	{
		printf("I'm sorry but we are currently full\n");
	}

}


void
list()
{
	struct info * a = patientInfo;
	int i;
	for (i = 0; i <counter; i++, a++) 
	{
		printf("Name: %s \t Department:%d \t ",a -> name, a -> departmentNumber);
		if (a -> departmentNumber == 1)
		 {
			 printf("fever:  %f\n ", a -> details.fever);
                 }
                 else if (a -> departmentNumber == 2)
                 {
                         printf ("Type of pain: %s\n", a -> details.pain);
                 }
                 else if (a -> departmentNumber == 3 || a -> departmentNumber == 4)
                 {
                          printf ("%d days \n", a -> details.daysSick);
                 } 
	}
}

void 
displayPatientDetails(char nameGiven[])
{
	struct info * a = patientInfo;
	int i;
	for (i = 0; i < counter; i++, a++)
	{
		if (strcmp(a -> name, nameGiven) == 0)
		{ 
			if (a -> departmentNumber == 1)
			{
				printf("%s temperature is: %f \n", a -> name, a -> details.fever);
			}
			else if (a -> departmentNumber == 2)
			{
				printf ("%s has: %s \n", a -> name, a -> details.pain);
			}
			else if (a -> departmentNumber == 3 || a -> departmentNumber == 4)
			{
				printf ("%s has been in the hospital for %d days \n", a -> name, a -> details.daysSick);
			}
		}
		else
		{
		printf("Sorry that patient cannot be found");
		}
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
		printf("Enter '1' in Order to Add Your Name and Department\n Enter '2' In Order to View the List of Patients\n Enter '3' in order to remove a patient \n Enter '4 in order to view patients in a department \n Enter '0' In Order to Quit the Program\n ");
		scanf("%d", &enteredNumber);
	
		if (enteredNumber < 1 || enteredNumber > 5)
		{
			return 0;
		}
		else 
		{
	 		if (enteredNumber == 1) 
			{
				printf("Enter the name of the patient:\n");
				scanf("%s", tempArray);
				printf("Enter the department of the patient(1-4)\n");
				scanf("%d", &tempDepartment);
				insert(tempArray,tempDepartment);
			}
			else if (enteredNumber == 2) 
			{
				list();
			}
			else if (enteredNumber == 3)
			{
				printf("Enter the department in which you want to remove the patient that has been there the longest\n");
				scanf("%d", &enteredNumber);
				removePatient(enteredNumber);
			}
			else if (enteredNumber == 4) 
			{
				printf("Enter the department number in which you want to view all the patients in that department\n");
				scanf("%d", &enteredNumber); 
				show_dept(enteredNumber);
			}
			else if (enteredNumber == 5)
			{
				printf("Enter the name of the patient that you want to know their condition\n");
				scanf("%s",enteredName);
				displayPatientDetails(enteredName); 
			}
		}
	}
	
}











