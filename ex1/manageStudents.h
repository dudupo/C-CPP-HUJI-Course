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
const char * BESTSTUDENTOUT         = "best student info is:\t";
const char * BESTOPT                = "best";
const char * MERGEOPT               = "merge";
const char * QUICKOPT               = "quick";
const int CONTINUE      = 1;
const int STOP          = 0;
const int LOWERGRADE    = 0;
const int UPPERGRADE    = 100;
const int LOWERAGE      = 0;
const int UPPERAGE      = 100;
const char QUIT         = 'q';
const char ZERO         = '0';
const int DROPLINE      = 0;

static unsigned long long  ids  [ UPPER_BOUND_INPUT_LINES ] = {0};
static int ages                 [ UPPER_BOUND_INPUT_LINES ] = {0};
static int grades               [ UPPER_BOUND_INPUT_LINES ] = {0};
static char names               [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ] = {0};
static char countrys            [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ] = {0};
static char citys               [ UPPER_BOUND_INPUT_LINES ][ UPPER_BOUND_FIELD_SIZE ] = {0};
static int students = 0;
static int lines = 1;
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
int parseNameWithSpaces(int scan_feedback, char * str);
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

/**
 * @brief returns the best student by the ratio of the grade
 *  relative to the age.
 * @return the index of the best student.
 */
int bestStudent();
/**
 * @brief initilaize the order array which will storing (after the sorting)
 *  the position of i' student in sorted order.
 * @return nothing.
 */
void initilaizeSort();
/**
 * @brief implemetion of the merge sort.
 * @return nothing.
 */
void mergesort(int start, int end, function compareFunction);
/**
 * @brief implemetion of the quicksort sort.
 * @return nothing.
 */
void quicksort(int start, int end, function compareFunction);
/**
* @brief the merge function, which mearge two sorted segments by given-
*  -comparing function. in the first phase the function will store the sorted-
*  -elements into the 'worktype' which is a spair static array at length 5000-
*  -(UPPER_BOUND_INPUT_LINES). than in the second phase the function will copy-
*  -the content beck to order array. the worktype is anloged to a temp-
*  -variable which defined when executing swapping between two variables.
* @return nothing.
*/
void merge(int start_1, int end_1, int start_2, int end_2, function compareFunction);
/**
 * @brief comparing studens by their grades.
 * @return ture if the first student grade is lower or equal than the other.
 */
int compareGrades(int student1, int student2);
/**
 * @brief comparing studens by their names ( abc order ).
 * @return ture if the first student name is preceding the other.
 */
int compareNames(int student1,  int student2);
