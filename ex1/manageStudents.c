/**
 * @file manageStudents.c
 * @author  david ponarovsky
 * @version 1.0
 * @date 9 Sep 2014
 *
 * @brief System to keep track of the cooking times.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The system keeps track of the cooking times.
 * Input  : Times to be measured.
 * Process: Summing times if needed, waiting for the correct time and
 *          notifying the user.
 * Output : Notification.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "manageStudents.h"
// ... rest of includes from the system
// ... all my includes

// -------------------------- const definitions -------------------------



// ------------------------------ functions -----------------------------

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
char peekStdin()
{
	char temp = getchar();
	ungetc(temp, stdin);
	return temp;
}

void popSpaces()
{
	while( isSpace( peekStdin() ) )
	{
		getchar();
	}
}

int isLetter(char c)
{
	return (c >= 'A') && (c <='z');
}
int isSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

// there is assumption that next object to parse is a number.
void parseNameWithSpaces(int student)
{
	int i = 0;

	while(  isSpace( peekStdin() ) || isLetter( peekStdin() ) )
	{
		popSpaces();

		if ( isLetter( peekStdin() ) )
		{

			if ( i > 0 )
			{
				names[student][i++]= ' ';
			}

			while( isLetter( peekStdin() ))
			{
				names[student][i++]= getchar();
			}
		}
		else
		{
			return;
		}
	}
	// todo : handle

}


/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int initilaizeStudent() {

	printf("%s\n", ENTER_STUDENT);
	popSpaces();
	if ( peekStdin() == 'q' )
	{
		getchar();
		return 0;
	}

	scanf("%d", &ids[students] );
	parseNameWithSpaces(students);
	scanf("%d\t%d\t%s\t%s", &grades[students], &ages[students],
	 countrys[students], citys[students]);

	students++;
	return 1;
}

void initilaizeStudentsList() {

	while( initilaizeStudent() )
	{

	}
}

double studentFactor( int student )
{
	return grades[student] / ages[student];
}

int bastStudent() {
	double max = studentFactor(0);
	int bastStudent = 0;

	for ( int i = 1 ; i < students ; i++ )
	{
		if ( studentFactor(i) > max )
		{
			max = studentFactor(i);
			bastStudent = i;
		}
	}
	return bastStudent;
}

void swap(int i, int j)
{
	int temp = order[j];
	order[j] = order[i];
	order[i] = temp;
}
void initilaizeSort()
{
	for (int i = 0; i < students; i++)
	{
		order[i] = i;
	}
}
void quicksort()
{

}

void merge(int i, int j, int end)
{

}

void mergesort(int start, int end)
{
	if (start == end)
	{
		return;
	}

	int middle = (start + end) / 2;
	mergesort(start, middle);
	mergesort(middle, end);
	merge(start, middle, middle, end);

}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */

int main(int argc, char const *argv[])
{
	initilaizeStudentsList();
	if (argc == 2)
	{

		// for (int i = 0; i < students; i++)
		// {
		// 	printf("id : %d\n", ids[i] );
		// 	printf("age : %d\n", ages[i] );
		// 	printf("name : %s\n", names[i] );
		// 	printf("country : %s\n", countrys[i]);
		// }

		int baststudent = bastStudent();
		printf("%s\n", names[baststudent] );
	}
	else
	{
		// handle ERROR ...
	}

	/* code */
	return 0;
}
