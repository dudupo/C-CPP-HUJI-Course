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


 // -------------------------- const definitions -------------------------

#define UPPER_BOUND_FIELD_SIZE 40
#define UPPER_BOUND_INPUT_LINES 5000

 // informative massage
 const char * ENTER_STUDENT =  "Enter student info. To exit press q, then enter";


static unsigned long long  ids  [ UPPER_BOUND_INPUT_LINES ];
static int ages                 [ UPPER_BOUND_INPUT_LINES ];
static int grades               [ UPPER_BOUND_INPUT_LINES ];
static char names               [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ];
static char countrys            [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ];
static char citys               [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ];
static int students = 0;

static int order [UPPER_BOUND_INPUT_LINES];

// -------------------------- functions definitions -------------------------

int initilaizeStudent();
char peekStdin();

void popSpaces();
int isLetter(char c);
int isSpace(char c);
void parseNameWithSpaces(int student);


void initilaizeStudentsList();

double studentFactor( int student );
int bastStudent();

void swap(int i, int j);
void initilaizeSort();
void quicksort();
void mergesort(int start, int end);
void merge(int start, int end, int start2 , int end2);
