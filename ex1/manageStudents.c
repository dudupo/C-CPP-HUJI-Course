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
#include <string.h>
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
	return ((double)grades[student] / ages[student]);
}

int getStudentGrade(int student1, int student2)
{
	return grades[student1] <= grades[student2];
}
int getStudentName(int student1,  int student2)
{
	return strcmp(names[student2] , names[student1]) > 0;
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

void merge(int start_1, int end_1, int start_2, int end_2, function compareFunction)
{
	printf("%d - %d - %d - %d\n",  start_1,  start_2,  end_1,  end_2 );
	int cursor_1 = start_1, cursor_2 = start_2;
	int cursor_merged = start_1;

	while ( cursor_1 <= end_1 && cursor_2 <= end_2  )
	{
		if ( compareFunction(order[cursor_1], order[cursor_2]) )
			worktype[cursor_merged++] = order[cursor_1++];
		else
			worktype[cursor_merged++] = order[cursor_2++];
	}
	while( cursor_1 <= end_1 )
		worktype[cursor_merged++] = order[cursor_1++];

	while( cursor_2 <= end_2 )
		worktype[cursor_merged++] = order[cursor_2++];

	for ( int position = start_1 ; position <= end_2  ; position++)
	{
		order[position] = worktype[position];
		worktype[position] = 0;
	}
}

void mergesort(int start, int end, function compareFunction)
{
	if (start == end)
	{
		return;
	}

	int middle = (start + end) / 2;
	mergesort(start, middle, compareFunction);
	mergesort(middle+1, end, compareFunction);
	merge(start, middle, middle+1, end, compareFunction);

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

		if ( strcmp(argv[1], "bast") == 0 )
		{
			int baststudent = bastStudent();
			printf("%s\n", names[baststudent] );
		}
		else if ( strcmp(argv[1], "merge") == 0  )
		{
				initilaizeSort();
				mergesort(0 , students-1, &getStudentGrade);

				for ( int k = 0; k < students; k++ )
				{
					printf("%s -> %d \n", names[order[k]] , grades[order[k]] );
				}
		}
		else if ( strcmp(argv[1], "quick") == 0  )
		{
				initilaizeSort();
				mergesort(0 , students-1, &getStudentName);

				for ( int k = 0; k < students; k++ )
				{
					printf("%s -> %d \n", names[order[k]] , grades[order[k]] );
				}
		}
	}
	else
	{
		// handle ERROR ...
	}

	/* code */
	return 0;
}
