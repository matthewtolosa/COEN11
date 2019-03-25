#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define VALIDDEPT(X) ((X)>=0 && (X)<=6)

pthread_mutex_t lock;
typedef union hospitalInformation
{
float fever;
char pain[20];
int daysSick;
}UNION;

typedef struct node 
{
struct node *next;
int departmentNumber;
char name[20] ;
UNION details;
}NODE;

struct head_tail
{
NODE * head;
NODE * tail;
};

struct head_tail lists[4] = {{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};



void
show_dept(int enteredNumber)
{
       
	if(!VALIDDEPT(enteredNumber))
	{
		return;
	}
	NODE * current = lists[enteredNumber - 1].head;

	while(current != NULL)
	{
		printf("%s\n", current->name);
		current = current->next;
	}
}

void 
removePatient(int enteredNumber) 
{

	pthread_mutex_lock(&lock);
	NODE *current;
	current = lists[enteredNumber].head;
	

	while(current!= NULL) 
	{
		lists[enteredNumber -1].head = lists[enteredNumber -1].head->next;
		free(current);		
		break;
	}
	current = current->next;
	pthread_mutex_unlock(&lock);
}

int
check_duplicate(char nameOne[])
{ 
	int i;
	NODE* current;
	for (i = 0; i < 4; i++)
	{
		current = lists[i].head;
		while (current != NULL)
		{
			if (strcmp(current->name, nameOne) == 0)
			{
				printf("Sorry, this name has already been entered in our system \n");
				return 1;
			}
		current = current->next;
		}
	}
	return 0;
}


void 
insert (char *nameOne, int tempDepartment, UNION tempUnion) 
{

	if(!VALIDDEPT(tempDepartment))
	{
		return;
	}
	pthread_mutex_lock(&lock);
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	
	strcpy(temp-> name, nameOne);
	temp->next = NULL;
	temp->departmentNumber = tempDepartment;
	if (check_duplicate(nameOne) == 0)
	{
		if (tempDepartment == 1)
		{
			temp->details.fever = tempUnion.fever; 
		}
		else if (tempDepartment == 2)
		{
			strcpy(temp ->details.pain, tempUnion.pain);
		}
		else if (tempDepartment == 3 || tempDepartment == 4)
		{
			temp->details.daysSick = tempUnion.daysSick;
		}	
		if (temp == NULL)
		{
			pthread_mutex_unlock(&lock);
			return;
		}
		if (lists[tempDepartment -1].head == NULL && lists[tempDepartment -1].tail == NULL)
		{
			lists[tempDepartment -1].head  = temp;
			lists[tempDepartment -1].tail = temp;
		}
		else
		{
		lists[tempDepartment -1].tail->next = temp;
		lists[tempDepartment -1].tail = temp;
		}
	}
	pthread_mutex_unlock(&lock);
}
 

void
list()
{
	NODE * current;
	printf("Name\tDepartment\tPatient Info\n");
	int i;
	for (i = 0; i < 4; i++)
	{
		current = lists[i].head;	
		while(current != NULL) 
		{
			printf("%s\t%d\t\t", current->name, current-> departmentNumber);
			if (current-> departmentNumber == 1)
			{
				 printf("%f\n", current-> details.fever);
                	}
                	else if (current-> departmentNumber == 2)
                	{
                        	 printf ("%s\n", current-> details.pain);
                	}
                	else if (current-> departmentNumber == 3 || current-> departmentNumber == 4)
                	{
                        	 printf ("%d\n", current-> details.daysSick);
                	} 
		current = current->next;
		}
	}

}

void 
displayPatientDetails(char nameGiven[])
{
	NODE * current;
	int i;
	for (i=0; i<4; i++)
	{
		current = lists[i].head;
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
		current = current->next;
		return;
		}
	}
	//printf("Sorry that patient cannot be found");
	printf("Reaches the end of displayPatientDetails");
	return;
} 

void
readFromFile(char*fname)
{
	NODE current;
	FILE * fp;
	//checks to see if file is valid
	fp = fopen(fname, "rb");
	if (fp == NULL)
	{
		printf("Error with file (Doesnt Read)\n");
		return;
	}
	//initialize the pointer fp point to file 
		while (fread(&current,sizeof(NODE),1,fp)==1)
		{
			insert(current.name, current.departmentNumber, current.details);
		}
	fclose(fp);
} 

void
readFromTextFile(char*fname, int key)
{       
        //temp vars for the name and dept #
        char givenName[10];
        int givenDepartmentNumber;
        
        FILE * fp;
	int j;
	char line[200];
        //checks to see if file is valid
        fp = fopen(fname, "r");
        if (fp == NULL)
        {       
                printf("Error with file (Doesnt Read)\n");
                return;
        }
        //initialize the pointer fp point to file
        fseek(fp,28,SEEK_SET);
               // while (fscanf(fp, "%s%d",givenName,&givenDepartmentNumber)==2)
               	while(fgets(line, 200, fp)!=NULL)
		{       
			j =0;
			while(line[j] != '\n')
			{
				line[j] = line[j]^key;
				j++;
			}
			sscanf(line,"%s\t%d\t",givenName, &givenDepartmentNumber);
                        UNION tempUnion;
                        if(givenDepartmentNumber == 1)
                        {       
				sscanf(line,"%s\t%d\t%f",givenName, &givenDepartmentNumber,&tempUnion.fever);
                                insert(givenName,givenDepartmentNumber,tempUnion);
                        }
                        else if (givenDepartmentNumber == 2)
                        {       
                                
				sscanf(line,"%s\t%d\t%s",givenName, &givenDepartmentNumber,tempUnion.pain);
                                insert(givenName,givenDepartmentNumber,tempUnion);
                        }
                        else if (givenDepartmentNumber == 3 || givenDepartmentNumber == 4)
                        {       
                                
				sscanf(line,"%s\t%d\t%d",givenName, &givenDepartmentNumber,&tempUnion.daysSick);
                                insert(givenName,givenDepartmentNumber,tempUnion);
                        } 
		}
		
		
}

void
saveToTextFile(char*fname,int key)
{
        FILE * fp;
        int i;
	char line[200];
	int j;
        fp = fopen(fname,"w");
        if (fp==NULL)
        {
                printf("Error with file");
                return;
        }
        fprintf(fp,"Name\tDepartment\tPatientInfo\t\n");
        for (i=0; i < 4; i++)
        {
                NODE * current = lists[i].head;
                while (current != NULL)
                {
                        if (current->departmentNumber == 1)
                        {
                                sprintf(line,"%s\t%d\t%f\t\n",current->name,current->departmentNumber,current ->details.fever);
                        }
                        else if (current->departmentNumber ==2)
                        {
                                sprintf(line,"%s\t%d\t%s\t\n",current->name,current->departmentNumber,current ->details.pain);
                        }
                        else if (current->departmentNumber ==3 || current->departmentNumber==4)
                        {
                                sprintf(line,"%s\t%d\t%d\t\n",current->name,current->departmentNumber,current ->details.daysSick);
                        }
                        current = current ->next;
                
			j = 0;
			while(line[j]!='\n')
			{
				line[j] = line[j]^key;
				j++;
			}
			fprintf(fp, "%s", line);
		}	
	}

        fclose(fp);
        return;
}

void
*auto_save(void*arg)
{       
        
        FILE*fp;
	while(1)
        {      
        	int i;
        	fp = fopen((char*)arg, "w+");
        	if (fp == NULL)
        	{       
                	printf("Error with file\n");
                	return NULL;
       	 	}
        	NODE *current;
		 
               
                pthread_mutex_lock(&lock);
                for (i=0; i < 4; i++)
                {       
                        current = lists[i].head;
                        while (current != NULL)
                        {       
				fwrite(current, sizeof(struct node), 1, fp);
				current = current -> next;
                        }
                
		}
                pthread_mutex_unlock(&lock);
		fclose(fp);
		sleep(15);
		printf("auto saving...\n");
        }
	return NULL;
		
}

void
read_auto_saved(char*fname)
{
	NODE temp;
        FILE*fp;
	pthread_mutex_lock(&lock);
        fp = fopen(fname, "rb");
        if (fp == NULL)
        {
		pthread_mutex_unlock(&lock);
                return;
        }
        while (fread(&temp, sizeof(NODE),1, fp)>0)
        {
		printf("%s\t%d\t\t",temp.name, temp.departmentNumber);
		if (temp.departmentNumber == 1)
		{
			printf("%f\n",temp.details.fever);
		}
		else if(temp.departmentNumber == 2)
		{
			printf("%s\n", temp.details.pain);
		}
		else if(temp.departmentNumber ==3 || temp.departmentNumber==4)
		{
			printf("%d\n", temp.details.daysSick); 
		}
        }
        fclose(fp);
	pthread_mutex_unlock(&lock);
	return;
}


	


int main(int argc, char *argv[]) 
{
	int tempDepartment;
	char tempArray[20];
	int enteredNumber;
	char enteredName[20];
	

	if (argc==1)
	{
		printf("No file exists \n");
		return 1;
	}
	
	int key = atoi(argv[3]);
	pthread_t myPthread;
        pthread_mutex_init(&lock, NULL);
        pthread_create(&myPthread, NULL,auto_save,(void*)argv[2]); 
	readFromTextFile(argv[1],key);
	
	while(1) 
	{
		printf("Enter '1' in Order to Add Your Name and Department\nEnter '2' In Order to View the List of Patients\nEnter '3' in order to remove a patient\nEnter '4 in order to view patients in a department\nEnter '5' In order to view the details of a Patient\nEnter '6' in order to display the auto saved file\nEnter '0' In Order to Quit the Program\n");
		scanf("%d", &enteredNumber);
	 	if(enteredNumber < 0 || enteredNumber > 6)
		{
			printf("Not valid command\n");
			continue;
		}
			if (enteredNumber == 1) 
			{
				printf("Enter the name of the patient:\n\n");
				scanf("%s", tempArray);
				printf("Enter the department of the patient(1-4)\n\n");
				scanf("%d", &tempDepartment);
				UNION tempUnion; 
				if (tempDepartment == 1)
				{
					printf("Enter the temperature of the patient \n");
					scanf("%f",&tempUnion.fever);
				}
				else if (tempDepartment == 2)
				{
					printf ("Enter the type of pain the patient has: \n");
					scanf("%s",tempUnion.pain);
				}
				else if (tempDepartment == 3 || tempDepartment == 4)
				{
					printf("Enter the number of days that the patient has been in the hospital \n");
					scanf("%d",&tempUnion.daysSick);
				}	
				insert(tempArray,tempDepartment,tempUnion);
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
			else if (enteredNumber == 0)
			{
				saveToTextFile(argv[1],key);
				pthread_cancel(myPthread);
				return 0;
			}
			else if (enteredNumber == 6)
			{
				read_auto_saved(argv[2]);
			}
	}
}

	







