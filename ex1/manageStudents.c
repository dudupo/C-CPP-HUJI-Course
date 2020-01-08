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
//#include "manageStudents.h"
// ... rest of includes from the system
// ... all my includes

// -------------------------- const definitions -------------------------

// -------------------------- const definitions -------------------------
#define UPPER_BOUND_LINE_SIZE 150
#define UPPER_BOUND_FIELD_SIZE 40
#define UPPER_BOUND_INPUT_LINES 5000

// informative massage
const char * ENTER_STUDENT =  "Enter student info. To exit press q, then enter";

const char * ERRORNAME              = "ERROR: name can only contain alphabetic characters or '-' and spaces";
const char * ERRORCITYNAME          = "ERROR: city can only contain alphabetic characters or '-'";
const char * ERRORCOUNTRYNAME       = "ERROR: country can only contain alphabetic characters or '-'";
const char * ERRORIDES              = "ERROR: id must contain ten digits and cannot start with zero";
const char * ERRORAGES              = "ERROR: age can only be integer between 18 to 80";
const char * ERRORGRADES            = "ERROR: grade can only be integer between 0 to 100";
const char * BESTSTUDENTOUT         = "best student info is: ";
const char * BESTOPT                = "best";
const char * MERGEOPT               = "merge";
const char * QUICKOPT               = "quick";
const char * USAGE									= "USAGE: ./manageStudents (best|quick|merge)";
const int CONTINUE      = 1;
const int STOP          = 0;
const int LOWERGRADE    = 0;
const int UPPERGRADE    = 100;
const int LOWERAGE      = 18;
const int UPPERAGE      = 80;
const char QUIT         = 'q';
const char ZERO         = '0';
const int DROPLINE      = 0;

static unsigned long ids   			[ UPPER_BOUND_INPUT_LINES ] = {0};
static int ages                 [ UPPER_BOUND_INPUT_LINES ] = {0};
static int grades               [ UPPER_BOUND_INPUT_LINES ] = {0};
static char names               [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ] = {0};
static char countrys            [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ] = {0};
static char citys               [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ] = {0};
static int students = 0;
static int lines = 0;
static int order [UPPER_BOUND_INPUT_LINES];
static int worktype [UPPER_BOUND_INPUT_LINES] = {0};
const int AGESPARAMTYPE         = 1;
const int GRADESPARAMTYPE       = 2;
const int NAMESPARAMTYPE        = 3;
const int COUNTRYSPARAMTYPE     = 4;
const int CITYSPARAMTYPE        = 5;
const int IDSPARAMTYPE          = 6;
typedef int (*function)(int, int);
typedef int (*scan_function) ( char param[] );
typedef int (*check_function) ( char param[] );


// -------------------------- functions definitions -------------------------

void resetStudent( );
int checkAges(  ) ;
int checkGrades(  ) ;
int checkNames(  ) ;
int checkCountrys(  ) ;
int initilaizeStudent();
char peekStdin();
void popSpaces();
int isLetter(char c);
int isSpace(char c);
int parseNameWithSpaces(int scan_feedback, char * str);
void initilaizeStudentsList();
double studentFactor( int student );
int bestStudent();
void initilaizeSort();
void mergesort(int start, int end, function compareFunction);
void quicksort(int start, int end, function compareFunction);
void merge(int start_1, int end_1, int start_2, int end_2, function compareFunction);
int compareGrades(int student1, int student2);
int compareNames(int student1,  int student2);

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
	return (c == '-') || ( (c >= 'A') && (c <= 'z') );
}
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int isSpace(char c)
{
	return c == SPACE || c == '\t' || c == '\n';
}
/**
 * @brief printing the error to stdout.
 */
void printError(const char * error)
{
	printf( "%s\nin line %d\n", error, lines);
}
/**
 * @brief checking that the input has entered in the type format.
 */
int checkScan( int scan_feedback)
{
  if ( scan_feedback != 1 )
  {

    return DROPLINE;
  }
  return CONTINUE;
}
/**
 * @brief checking that the input which entered is string.
 */
int checkStr( int scan_feedback, char * str)
{
  if ( !checkScan(scan_feedback))
  {
    return DROPLINE;
  }
  else
  {
    char * pointer = str;
    for ( ; *pointer ; pointer++ )
    {
      if ( ! isLetter( *pointer ) )
      {

        return DROPLINE;
      }
    }
  }
  return CONTINUE;
}

int checkStrContainDigits(char param [])
{
	char * pointer = param;
	for (; *pointer; pointer++ )
	{
		if ( !isDigit(*pointer) )
		{
			return DROPLINE;
		}
	}
	return CONTINUE;
}

/**
 * @brief checking that the input which entered is integer in given range.
 */
int checkInt( int scan_feedback, int val, int lower, int upper)
{
    if ( !checkScan(scan_feedback))
    {
        return DROPLINE;
    }
    else
    {
        if ( ( val >= lower ) && ( val <= upper ))
        {
            return CONTINUE;
        }
        return DROPLINE;
    }
}

/**
 * @brief parsing the names of the student, dealing with naems which contains-
 *  			-a spaces. store the name in the last empty cell inside the global-
 *				-static names array.
 * @return nothing.
 */
int parseNameWithSpaces(int scan_feedback, char * str)
{
  if ( !checkScan(scan_feedback))
  {
    return DROPLINE;
  }
  else
  {
    char * pointer = str;
    for ( ; *pointer ; pointer++ )
    {
      if ((*pointer != SPACE) && (!isLetter( *pointer )))
      {
        return DROPLINE;
      }
    }
  }
  return CONTINUE;

}
/**
 * @brief rest the student fields.
 */
void restStrField( char field [] )
{
	for ( int i = 0; i < UPPER_BOUND_FIELD_SIZE; i++ )
	{
		field[i] = 0;
	}
}
/**
 * @brief printing the student to stdot.
 */
void printStudent(int student)
{
	printf("%lu\t%s\t%d\t%d\t%s\t%s\t\n", ids[student], names[student],
	 grades[student], ages[student], countrys[student], citys[student]  );
}

/**
 * @brief rest the field of the given student.
 */
void resetStudent( )
{
	ids[students] 			= 0;
	grades[students] 		= 0;
	ages[students] 			= 0;
	restStrField(names[students]);
	restStrField(citys[students]);
	restStrField(countrys[students]);
	//scanf("%[^\n]");
	//char line [ UPPER_BOUND_LINE_SIZE ] = {0};
	//gets(line);
}


/**
 * @brief scanning word while using '\t' as dilameter.
 * @return the position of the end of the word inside the line.
 */
int scanWord(char line[], char param[], int start )
{
	int i = start;

	for (int k = 0; (line[i] != '\t') && (line[i] != '\n') ; i++ )
	{
		param[k++] = line[i];
	}
	return i + 1;
}

/**
 * @brief initilaize the students by asking for the parameters from the user-
 * -and store them into the static arrays.
 * @return 0 if the user press 'q' otherwise returns 1.
 */
int initilaizeStudent()
{
	// requesting for input student.
 	printf("%s\n", ENTER_STUDENT);
	// gettig rid of spaces.

	// check if the user press 'q'.
	if ( peekStdin() == QUIT )
	{
		// poping 'q' from the stdin stream.
		getchar();
		// than return 0, which will stops input loop.
		return STOP;
	}

	char line [ UPPER_BOUND_LINE_SIZE ] = {0};
	gets( line );

	char paramId [ UPPER_BOUND_FIELD_SIZE ] 			= {0};
	char paramName [ UPPER_BOUND_FIELD_SIZE ] 		= {0};
	char paramGrade [ UPPER_BOUND_FIELD_SIZE ] 		= {0};
	char paramAge [ UPPER_BOUND_FIELD_SIZE ] 			= {0};
	char paramCity [ UPPER_BOUND_FIELD_SIZE ] 		= {0};
	char paramCountry [ UPPER_BOUND_FIELD_SIZE ] 	= {0};

	int start = 0;
	start = scanWord(line, paramId, start );
	start = scanWord(line, paramName, start );
	start = scanWord(line, paramGrade, start );
	start = scanWord(line, paramAge, start );
	start = scanWord(line, paramCountry, start );
	start = scanWord(line, paramCity, start );

	if (paramId[0] == ZERO || (checkStrContainDigits(paramId) == DROPLINE) )
	{
		resetStudent();
  	printError( ERRORIDES );
  	return CONTINUE;
	}
	int digits_count = 0;
	for (digits_count = 0; paramId[digits_count]; digits_count++ )
	{

	}
	// parsing the student's id, and store in the id's.
	int scan_feedback = sscanf(paramId, "%lu", &ids[students] );
	if ( (digits_count != 10) || checkScan(scan_feedback) == DROPLINE)
	{
		printError( ERRORIDES );
		resetStudent();
		return CONTINUE;
	}
	scan_feedback = sscanf(paramName, "%[^\t]", names[students] );
	// parsing and storing the student's name.
	if (parseNameWithSpaces(scan_feedback, names[students]) == DROPLINE)
	{
		printError( ERRORNAME );
		resetStudent();
		return CONTINUE;
	}
	// parding and stroing the rest of the parameters.

	scan_feedback = sscanf(paramGrade, "%d", &grades[students]);
	if (checkInt(scan_feedback, grades[students], LOWERGRADE, UPPERGRADE)
        == DROPLINE || (checkStrContainDigits(paramGrade) ==
        DROPLINE))
	{
		printError( ERRORGRADES );
		resetStudent();
		return CONTINUE;
	}

	scan_feedback = sscanf(paramAge, "%d", &ages[students]);
	if (checkInt(scan_feedback, ages[students], LOWERAGE,
        UPPERAGE) == DROPLINE  || (checkStrContainDigits(paramAge) ==
        DROPLINE))
	{
		printError( ERRORAGES );
		resetStudent();
		return CONTINUE;
	}

	scan_feedback = sscanf(paramCountry, "%s", countrys[students] );
	if (checkStr( scan_feedback, countrys[students]) == DROPLINE )
	{
		printError( ERRORCOUNTRYNAME );
		resetStudent();
		return CONTINUE;
	}
	scan_feedback = sscanf(paramCity, "%s", citys[students] );
	if (checkStr( scan_feedback, citys[students]) == DROPLINE )
	{
		printError( ERRORCITYNAME );
		resetStudent();
		return CONTINUE;
	}
	// increasing the student counter by one.
	students++;
	return CONTINUE;
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
		lines++;
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
int bestStudent()
{
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
		{
			worktype[cursor_merged++] = order[cursor_1++];
		}
		else
		{
			worktype[cursor_merged++] = order[cursor_2++];
		}
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
	mergesort(middle + 1, end, compareFunction);
	// merging the sorted segments.
	merge(start, middle, middle + 1, end, compareFunction);

}

/**
 * @brief swapping two elements in the sorteted array.
 * @return nothing
 */
void swap(int i, int j)
{
	int temp = order[i];
	order[i] = order[j];
	order[j] = temp;
}

/**
 * @brief implemetion of the quicksort sort.
 * @return nothing.
 */
void quicksort(int start, int end, function compareFunction)
{

	if (  (start + 1) >= end )
	{
		return;
	}
	// chosing random parttion
	int segement = start +  (rand() % (end - start));
	// exchanging the loweres values which left to the parttion
	for (int i = start; i < segement; i++ )
	{
		if ( compareFunction(order[segement], order[i]) )
		{
			swap(segement, i);
		}
	}
	// exchanging the loweres values which right to the parttion
	for (int i = segement + 1; i < end; i++ )
	{
		if ( compareFunction(order[i], order[segement]) )
		{
			swap(segement, i);
		}
	}
	quicksort(start, segement, compareFunction);
	quicksort(segement + 1 , end, compareFunction);
}

/**
 * @brief printing the sorted array.
 * @return nothing
 */
void printStudentsSortedOrder()
{
	for ( int k = 0; k < students; k++ )
	{
		printStudent(order[k]);
	}
}

/**
 * @brief printing the USAGE format.
 * @return nothing
 */
void printUsage()
{
	printf("%s\n", USAGE);
}

/**
 * @brief The main function. parsing the command line arguments and executing
 * the requested command of the user.
 * @return 0 if the program have been run suecssfully.
 */
int main(int argc, char const *argv[])
{

	if (argc == 2)
	{

		if ( strcmp(argv[1], BESTOPT) == 0 )
		{
			initilaizeStudentsList();
			if ( students > 0)
			{
				int beststudent = bestStudent();
				printf("%s", BESTSTUDENTOUT);
				printStudent(beststudent);
			}
			else
			{
				return 1;
			}
		}
		else if ( strcmp(argv[1], MERGEOPT) == 0  )
		{
			initilaizeStudentsList();

			if ( students == 0 )
			{
				return 1;
			}

			initilaizeSort();
			mergesort(0 , students - 1, &compareGrades);
			printStudentsSortedOrder();
		}
		else if ( strcmp(argv[1], QUICKOPT) == 0  )
		{
			initilaizeStudentsList();

			if ( students == 0 )
			{
				return 1;
			}

			initilaizeSort();
			quicksort(0 , students, &compareNames);
			printStudentsSortedOrder();
		}
		else
		{
			printUsage();
			return 1;
		}
	}
	else
	{
		printUsage();
		return 1;
	}

	/* code */
	return 0;
}
