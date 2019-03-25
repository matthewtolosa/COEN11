#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main(void) {
	srand((int)time(NULL));
	int dividend = 0;
	int totalScore = 0; 
	int enteredNumber;
	for (int i = 0; i <= 10; i++) {
		int divisor = rand()%12+1;
		int quotient = rand()%13;
		dividend = divisor * quotient;
		printf("Enter the answer to: %d/%d\n " , dividend, divisor);
		scanf("%d", &enteredNumber);
		if (enteredNumber == quotient) {
			printf("Correct\n ");
			totalScore++;
		} else {
			printf("Wrong\n ");
			printf("The Correct Answer is: %d\n ", quotient);
		}
	}
	printf("Total Score is: %d\n ", totalScore);
	return 0;
}





