#include <string.h>
#include <stdlib.h>
#include "RBTree.h"
#include "Structs.h"

#define LE -1
#define EQ 0
#define GE 1
#define NOT_NULL_CASE 2
int const SUCCES_CONCATENATE = 1;
int const FAIL_CONCATENATE = 0;
int const FAIL_COPY_IF_NORM = 0;
int const SUCCES_COPY_IF_NORM = 1;
int const ZERO = 0;
char const NEW_LINE = '\n';
char * const NEW_LINE_P = "\n";
/**
 * handling the case when one of the object is null
 */
int compareNULLcase(const void *a, const void *b)
{
        if ( a == NULL && b == NULL )
        {
                return EQ;
        }
        if ( a == NULL )
        {
                return LE;
        }
        if ( b == NULL )
        {
                return GE;
        }

        return NOT_NULL_CASE;


}

/**
 * CompFunc for strings (assumes strings end with "\0")
 * @param a - char* pointer
 * @param b - char* pointer
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a. (lexicographic
 * order)
 */
int stringCompare(const void *a, const void *b)
{
        int null_case = compareNULLcase(a, b);
        if ( null_case != NOT_NULL_CASE )
        {
                return null_case;
        }
        return strcmp( ( const char *) a, ( const char *) b );
}

/**
 * ForEach function that concatenates the given word to pConcatenated. pConcatenated is already allocated with
 * enough space.
 * @param word - char* to add to pConcatenated
 * @param pConcatenated - char*
 * @return 0 on failure, other on success
 */
int concatenate(const void *word, void *pConcatenated)
{

        pConcatenated = ( void * )
                        strcat( (char *) pConcatenated, (const char * ) word);
        pConcatenated = ( void * )
            strcat( (char *) pConcatenated, NEW_LINE_P);

        if ( pConcatenated != NULL)
        {
                return SUCCES_CONCATENATE;
        }
        else
        {
                return FAIL_CONCATENATE;
        }
} // implement it in Structs.c

/**
 * FreeFunc for strings
 */
void freeString(void *s)
{
        free((char *) s);
}

/**
 * compering two doubles.
 */
int compare_doubles( const double *x, const double *y)
{
        return ( *x > *y ) - ( *x < *y );
}

/**
 * CompFunc for Vectors, compares element by element, the vector that has the first larger
 * element is considered larger. If vectors are of different lengths and identify for the length
 * of the shorter vector, the shorter vector is considered smaller.
 * @param a - first vector
 * @param b - second vector
 * @return equal to 0 iff a == b. lower than 0 if a < b. Greater than 0 iff b < a.
 */
int vectorCompare1By1(const void *a, const void *b)
{
        int null_case = compareNULLcase(a, b);
        if ( null_case != NOT_NULL_CASE )
        {
                return null_case;
        }

        const Vector * iterator_a = ( const Vector *)  a;
        const Vector * iterator_b = ( const Vector *)  b;


        int len_a = iterator_a->len;
        int len_b = iterator_b->len;
        int len_cmp = ( len_a > len_b ) - ( len_a < len_b );

        if ( len_cmp != EQ )
        {
                return len_cmp;
        }
        int cmp = EQ;
        for ( int i = 0; i < len_a && (cmp == EQ); i++ )
        {
                cmp = compare_doubles( &iterator_a->vector[i],
                                       &iterator_b->vector[i] );
        }
        return cmp;
}

/**
 * FreeFunc for vectors
 */
void freeVector(void *pVector)
{

        //if ( (( Vector *) pVector)->vector != NULL)
        free( (( Vector *) pVector)->vector );
        free( pVector );
}

/**
 * calculate the square norm of the vector.
 */
double calcSqureNorm(const Vector * vector )
{
        double ret = 0.f;

        for ( int i = ZERO; i < vector->len; i++ )
        {
                ret += ( vector->vector[i] * vector->vector[i]);
        }
        return ret;
}


/**
 * copy pVector to pMaxVector if : 1. The norm of pVector is greater then the norm of pMaxVector.
 *                            2. pMaxVector == NULL.
 * @param pVector pointer to Vector
 * @param pMaxVector pointer to Vector
 * @return 1 on success, 0 on failure (if pVector == NULL: failure).
 */
int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
{
        int copy = (pMaxVector == NULL);

        if ( ! copy )
        {

            int null_case = compareNULLcase(pVector, pMaxVector);
            if (null_case != NOT_NULL_CASE)
            {
                return FAIL_COPY_IF_NORM;
            }

            double norm_pVector = calcSqureNorm(((const Vector *) pVector));
            double norm_pMaxVector = calcSqureNorm((( Vector *) pMaxVector));

            copy = copy || ( norm_pMaxVector < norm_pVector  );

        }
        else
        {
            pMaxVector =  malloc ( sizeof(Vector) );
        }


        if ( copy )
        {
            if ( ((Vector *) pMaxVector)->vector != NULL )
            {
                free(((Vector *) pMaxVector)->vector);
            }

            ((Vector *) pMaxVector)->vector = (double *)
                    malloc( sizeof(double) *  ( (Vector *) pVector)->len );


            ( (Vector *) pMaxVector)->vector = (double *) memcpy(
                    ((Vector *) pMaxVector)->vector, ((Vector *) pVector)->vector,
                    sizeof(double) *  ( (const Vector *) pVector)->len )  ;
            ( (Vector *) pMaxVector)->len = (( const Vector *) pVector)->len;
        }
        return SUCCES_COPY_IF_NORM;
}

/**
 * @param tree a pointer to a tree of Vectors
 * @return pointer to a *copy* of the vector that has the largest norm (L2 Norm).
 */
Vector *findMaxNormVectorInTree(RBTree *tree)
{
        if ( tree != NULL && tree->root->data != NULL )
        {
                Vector * pMaxVector =  (Vector * ) malloc( sizeof(Vector) );
                pMaxVector->vector  =  (double *) malloc(
                        sizeof(double) *  ( (Vector *) tree->root->data)->len );

                pMaxVector->vector = (double *) memcpy(
                    pMaxVector->vector, (( Vector *) tree->root->data)->vector,
                    sizeof(double) *  ( (Vector *) tree->root->data)->len ) ;

                pMaxVector->len  = ((Vector * ) tree->root->data)->len;
                forEachRBTree(tree, copyIfNormIsLarger, (void *) pMaxVector );
                return pMaxVector;
        }
        else {
                return NULL;
        }
}
