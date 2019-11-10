/**
 * @file manageStudents.c
 * @author  david ponarovsky
 * @version 1.0
 * @date 5 Nov 2019
 *
 * @brief System to keep track of the cooking times.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @secton DESCRIPTION
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
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
void popSpaces()
{
	while( isSpace( peekStdin() ) )
	{
		getchar();
	}
}

/**
 * @brief isDigit checking if the charter is digit.
 * @return 1 if the charter is digit else 0
 */
int isDigit( char c )
{
    return ( c <= '9' && c >= '0');
}

/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int isLetter(char c)
{
	return (c == '-') || ( (c >= 'A') && (c <='z') );
}
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int isSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}
/**
 * @brief parsing the names of the student, dealing with naems which contains-
 *  			-a spaces. store the name in the last empty cell inside the global-
 *				-static names array.
 * @return nothing.
 */
void parseNameWithSpaces(int student)
{
	// position of the charter in the string which will represent the name
	int position = 0;
	while(  isSpace( peekStdin() ) || isLetter( peekStdin() ) )
	{
		// get rid of the spaces.
		popSpaces();
		// check that the first charter is letter, otherwise ( forexample in case-
		// -that the the next charter is digit ) the function will abort.
		if ( isLetter( peekStdin() ) )
		{
			// looked position which greater than one implays that the name contains-
			// -multiple words, in that case the function will seprate the words by-
			// -space.
			if ( position > 0 )
			{
				names[student][position++]= ' ';
			}
			// appends the next charters untill the next one isn't letter.
			while( isLetter( peekStdin() ))
			{
				names[student][position++]= getchar();
			}
		}
		else
		{
		    printf( "%s" , ERRORNAME);
			return;
		}
	}
	// todo : handle

}


int checkScan( int scan_feedback, char * errorMsg  )
{
    if ( scan_feedback != *ferror && scan_feedback != *feof )
    {
        printf( "%s\n", errorMsg );
        return 0;
    }
    return  1;
}

int checkStr( int scan_feedback, char * str , char * errorMsg  )
{
    if ( !checkScan(scan_feedback, errorMsg))
    {
        return 0;
    }
    else
    {
        char pointer = str;
        for ( ; str ; str++ )
        {
            if ( ! isLetter( *str ) )
            {
                printf( "%s\n", errorMsg );
                return 0;
            }
        }
    }
    popSpaces();
    return 1;
}

int checkInt( int scan_feedback, int val, int lower, int upper, char * errorMsg)
{
    if ( !checkScan(scan_feedback, errorMsg))
    {
        return 0;
    }
    else
    {
        if ( ( val >= lower ) && ( val <= upper ))
        {
            popSpaces();
            return 1;
        }
        printf( "%s\n", errorMsg );
        return 0;
    }
}


/**
 * @brief initilaize the students by asking for the parameters from the user-
 * -and store them into the static arrays.
 * @return 0 if the user press 'q' otherwise returns 1.
 */
int initilaizeStudent() {
	// requesting for input student.
	 printf("%s\n", ENTER_STUDENT);
	// gettig rid of spaces.
	popSpaces();
	// check if the user press 'q'.
	if ( peekStdin() == 'q' )
	{
		// poping 'q' from the stdin stream.
		getchar();
		// than return 0, which will stops input loop.
		return 0;
	}
	popSpaces();

	if (peekStdin() == '0')
    {
	    printf( "%s\n", ERRORIDES );
	    return 0;
    }
	// parsing the student's id, and store in the id's.
    int scan_feedback = scanf("%lu", &ids[students] );
    if ( !checkScan(scan_feedback, ERRORIDES))
    {
        return 0;
    }
	// parsing and storing the student's name.
	parseNameWithSpaces(students);
	// parding and stroing the rest of the parameters.


    scan_feedback = scanf("%d", &grades[students]);
    if (!checkInt(scan_feedback, grades[students], 0 ,100, ERRORGRADES))
    {
        return 0;
    }
    scan_feedback = scanf("%s", &countrys[students] );
    if ( ! checkStr( scan_feedback, countrys[students], ERRORCOUNTRYNAME) )
    {
        return 0;
    }
    scan_feedback = scanf("%s", &citys[students] );
    if ( ! checkStr( scan_feedback, citys[students] , ERRORCITYNAME ) )
    {
        return 0;
    }
	// increasing the student counter by one.
	students++;
	return 1;
}
/**
 * @brief initilaizes studens untill the 'initilaizeStudent' function return '0'
 * -which occuer when the user pressing 'q' - the signal which indecate exit-
 * -operation.
 * @return nothing.
 */
void initilaizeStudentsList()
{
	while( initilaizeStudent() )
	{

	}
}
/**
 * @brief calculate and return the ration of the student grade relative to his-
 * -age.
 * @return the ration of the student grade relative to his age.
 */
double studentFactor( int student )
{
	return ((double)grades[student] / ages[student]);
}
/**
 * @brief comparing studens by their grades.
 * @return ture if the first student grade is lower or equal than the other.
 */
int compareGrades(int student1, int student2)
{
	return grades[student1] <= grades[student2];
}
/**
 * @brief comparing studens by their names ( abc order ).
 * @return ture if the first student name is preceding the other.
 */
int compareNames(int student1,  int student2)
{
	return strcmp(names[student2] , names[student1]) > 0;
}

/**
 * @brief returns the best student by the ratio of the grade
 *  relative to the age.
 * @return the index of the best student.
 */
int bestStudent() {
	// first define the first student as the best one.
	// todo : handle empty array ...
	double max = studentFactor(0);
	int beststudent = 0;
	// iterating over the rest of the students.
	for ( int i = 1 ; i < students ; i++ )
	{
		// if found batter student than exchange him with the best one.
		if ( studentFactor(i) > max )
		{
			max = studentFactor(i);
			beststudent = i;
		}
	}
	return beststudent;
}
/**
 * @brief initilaize the order array which will storing (after the sorting)
 *  the position of i' student in sorted order.
 * @return nothing.
 */
void initilaizeSort()
{
	for (int i = 0; i < students; i++)
	{
		order[i] = i;
	}
}
/**
 * @brief the merge function, which mearge two sorted segments by given-
 *  -comparing function. in the first phase the function will store the sorted-
 *  -elements into the 'worktype' which is a spair static array at length 5000-
 *  -(UPPER_BOUND_INPUT_LINES). than in the second phase the function will copy-
 *  -the content beck to order array. the worktype is anloged to a temp-
 *  -variable which defined when executing swapping between two variables.
 * @return nothing.
 */
void merge(int start_1, int end_1, int start_2, int end_2, function compareFunction)
{
	// defining the cursor which will be running on the segments.
	int cursor_1 = start_1, cursor_2 = start_2;
	// the cursor_merged will be used to store in worktype.
	int cursor_merged = start_1;
	// while there is a cursor which have not reach yet to the end of hi's
	// -segment.
	while ( cursor_1 <= end_1 && cursor_2 <= end_2  )
	{
		// storing the lower than the two students which are being examined.
		// and increasing the cursor of the chosen segment.
		if ( compareFunction(order[cursor_1], order[cursor_2]) )
			worktype[cursor_merged++] = order[cursor_1++];
		else
			worktype[cursor_merged++] = order[cursor_2++];
	}
	// if the first cursor not reach to the end of his segment than push-
	// the rest of the elements to the end of the worktype.
	while( cursor_1 <= end_1 )
	{
		worktype[cursor_merged++] = order[cursor_1++];
	}
	// repet on the above to the second cursor.
	while( cursor_2 <= end_2 )
	{
		worktype[cursor_merged++] = order[cursor_2++];
	}
	// copying back the elements from the worktype into the order array.
	for ( int position = start_1 ; position <= end_2  ; position++)
	{
		order[position] = worktype[position];
		worktype[position] = 0;
	}
}
/**
 * @brief implemetion of the merge sort.
 * @return nothing.
 */
void mergesort(int start, int end, function compareFunction)
{
	// stopping condition for the reqursive calls.
	if (start == end)
	{
		return;
	}
	// parting the segment to two equals segments. and than sorting each of them.
	int middle = (start + end) / 2;
	mergesort(start, middle, compareFunction);
	mergesort(middle+1, end, compareFunction);
	// merging the sorted segments.
	merge(start, middle, middle+1, end, compareFunction);

}
/**
 * @brief The main function. parsing the command line arguments and executing
 * the requested command of the user.
 * @return 0 if the program have been run suecssfully.
 */
int main(int argc, char const *argv[])
{
	initilaizeStudentsList();
	if (argc == 2)
	{

		if ( strcmp(argv[1], "best") == 0 )
		{
			int beststudent = bestStudent();
			printf("%s\n", names[beststudent] );
		}
		else if ( strcmp(argv[1], "merge") == 0  )
		{
				initilaizeSort();
				mergesort(0 , students-1, &compareGrades);

				for ( int k = 0; k < students; k++ )
				{
					printf("%s -> %d \n", names[order[k]] , grades[order[k]] );
				}
		}
		else if ( strcmp(argv[1], "quick") == 0  )
		{
				initilaizeSort();
				mergesort(0 , students-1, &compareNames);

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
