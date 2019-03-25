#include <stdio.h>
#include <string.h>


void list();
void insert();
void removePatient(int);
void show_dept(int);
int check_duplicate();

struct info 
{
int departmentNumber;
char name[20] ;
};

struct info patientInfo[10];


int enteredNumber;
int flag = 0;
int counter = 0;


int main() 
{
	int tempDepartment;
	char tempArray[20];
	int enteredNumber;

	while(1) 
	{
		printf("Enter '1' in Order to Add Your Name and Department\n Enter '2' In Order to View the List of Patients\n Enter '3' in order to remove a patient \n Enter '4 in order to view patients in a department \n Enter '0' In Order to Quit the Program\n ");
		scanf("%d", &enteredNumber);
	
i		if (enteredNumber < 1 || enteredNumber > 4)
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
		}
	}
	
}

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


void 
insert (char nameOne[], int tempDepartment) 
{
	check_duplicate(nameOne);
	
	struct info * a = patientInfo;
	
	if (counter < 10 && flag != 1 ) //Checks to see the list isnt full and that no name repeats 
	{					
		strcpy(a -> name, nameOne);
		a -> departmentNumber = tempDepartment;
		counter++;			
		flag = 0;		
	}
	else 
	{
		printf("I'm sorry but we are currently full\n");
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
			flag = 1;
			printf("Sorry, this name has already been entered in our system \n");
		}
	}
	return flag;
}


void
list()
{
	struct info * a = patientInfo;
	for (int i = 0; i <counter; i++, a++) 
	{
		printf("Name:%s Department:%d \n",a -> name, a -> departmentNumber);
	}
}
