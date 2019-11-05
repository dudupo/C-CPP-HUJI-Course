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
static int worktype [UPPER_BOUND_INPUT_LINES] = {0};

typedef int (*function)(int, int);
// -------------------------- functions definitions -------------------------
/**
 * @brief initilaize the students by asking for the parameters from the user-
 * -and store them into the static arrays.
 * @return 0 if the user press 'q' otherwise returns 1.
 */
int initilaizeStudent();
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
char peekStdin();
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
void popSpaces();
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int isLetter(char c);
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int isSpace(char c);
/**
 * @brief parsing the names of the student, dealing with naems which contains-
 *  			-a spaces. store the name in the last empty cell inside the global-
 *				-static names array.
 * @return nothing.
 */
void parseNameWithSpaces(int student);
 /**
  * @brief initilaizes studens untill the 'initilaizeStudent' function return '0'
  * -which occuer when the user pressing 'q' - the signal which indecate exit-
  * -operation.
  * @return nothing.
  */
void initilaizeStudentsList();
/**
 * @brief calculate and return the ration of the student grade relative to his-
 * -age.
 * @return the ration of the student grade relative to his age.
 */
double studentFactor( int student );
int bestStudent();
void initilaizeSort();
void mergesort(int start, int end, function compareFunction);
void merge(int start_1, int end_1, int start_2, int end_2, function compareFunction);
int compareGrades(int student1, int student2);
int compareNames(int student1,  int student2);
