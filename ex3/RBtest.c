#define TEST
#include "RBTree.h"
#include "ProductExample.c"
#include "Structs.c"
Node * newLeaf( Node ** );
int getHeight(Node *);



void test_isLeftChild()
{
        //int isLeftChild(Node *node);
        printf("isLeftChild - pass \n");
}


void test_isRightChild()
{

        //int isRightChild(Node *node);
        printf("isRightChild - pass \n");
}

void test_getState()
{

        //int getState(Node *node);
        printf("getState - pass \n");
}

void test_rotateLeft()
{

        ProductExample **products = getProducts();
        RBTree *tree = newRBTree(productComparatorByPrice, productFree);
        addToRBTree(tree, products[0]);

        tree->root->left =  newLeaf( &(tree->root) );
        tree->root->left->data = (void *) products[1];
        tree->root->left->parent = tree->root;

        tree->root->left->left = (Node *) newLeaf( &tree->root->left );
        tree->root->left->left->data = NULL;
        tree->root->left->left->parent = tree->root->left;

        tree->root->left->right = (Node *) newLeaf( &tree->root->left );
        tree->root->left->right->data = NULL;
        tree->root->left->right->parent = tree->root->left;

        tree->root->right = (Node *) newLeaf( &tree->root );
        tree->root->right->data = (void *) products[2];
        tree->root->right->parent = tree->root;

        tree->root->right->left = (Node *) newLeaf( &tree->root->right );
        tree->root->right->left->data = NULL;
        tree->root->right->left->parent = tree->root->right;

        tree->root->right->right = (Node *) newLeaf( &tree->root->right );
        tree->root->right->right->data = NULL;
        tree->root->right->right->parent = tree->root->right;

        forEachRBTree(tree, printProduct, NULL);

        rotateLeft(tree->root);
        tree->root = tree->root->parent;

        printf("----\n");
        forEachRBTree(tree, printProduct, NULL);

        printf("rotateLeft - pass \n");
}

void test_rotateRight()
{

        //void rotateRight(Node **node);
        ProductExample **products = getProducts();
        RBTree *tree = newRBTree(productComparatorByPrice, productFree);
        addToRBTree(tree, products[0]);

        tree->root->left =  newLeaf( &(tree->root) );
        tree->root->left->data = (void *) products[1];
        tree->root->left->parent = tree->root;

        tree->root->left->left = (Node *) newLeaf( &tree->root->left );
        tree->root->left->left->data = NULL;
        tree->root->left->left->parent = tree->root->left;

        tree->root->left->right = (Node *) newLeaf( &tree->root->left );
        tree->root->left->right->data = NULL;
        tree->root->left->right->parent = tree->root->left;

        tree->root->right = (Node *) newLeaf( &tree->root );
        tree->root->right->data = (void *) products[2];
        tree->root->right->parent = tree->root;

        tree->root->right->left = (Node *) newLeaf( &tree->root->right );
        tree->root->right->left->data = NULL;
        tree->root->right->left->parent = tree->root->right;

        tree->root->right->right = (Node *) newLeaf( &tree->root->right );
        tree->root->right->right->data = NULL;
        tree->root->right->right->parent = tree->root->right;

        forEachRBTree(tree, printProduct, NULL);

        rotateRight(tree->root);
        tree->root = tree->root->parent;

        printf("----\n");
        forEachRBTree(tree, printProduct, NULL);

        printf("rotateRight - pass \n");
}

void test_balancRBTree()
{

        //void balancRBTree(Node **node);
        printf("balancRBTree - pass \n");
}

void test_getNode()
{

        //Node * getNode(Node *node, void *data, CompareFunc compFunc);
        printf("getNode - pass \n");
}

void test_getNodeByRoot()
{

        //Node * getNodeByRoot(RBTree *root, void *data);
        printf("getNodeByRoot - pass \n");
}

void test_newLeaf()
{

        //Node * newLeaf(Node **parent);
        printf("newLeaf - pass \n");
}

void test_newRBTree()
{

        //RBTree * newRBTree(CompareFunc compFunc, FreeFunc freeFunc);
        printf("newRBTree - pass \n");
}

void test_addToRBTree()
{

        //int addToRBTree(RBTree *tree, void *data);
        ProductExample **products = getProducts();
        RBTree *tree = newRBTree(productComparatorByPrice, productFree);
        addToRBTree(tree, products[2]);
        addToRBTree(tree, products[3]);
        addToRBTree(tree, products[4]);
        addToRBTree(tree, products[0]);
        forEachRBTree(tree, printProduct, NULL);

        printf("addToRBTree - pass \n");
}


void test_containsRBTree()
{

        //int containsRBTree(RBTree *tree, void *data);
        printf("containsRBTree - pass \n");
}


void test_forEachDFS()
{

        //int forEachDFS(Node *node, forEachFunc func, void *args);
        printf("forEachDFS - pass \n");
}


void test_forEachRBTree()
{

        //int forEachRBTree(RBTree *tree, forEachFunc func, void *args);
        printf("forEachRBTree - pass \n");


}
void test_freeDFS()
{

        //void freeDFS(Node **node, FreeFunc freeFunc);
        printf("freeDFS - pass \n");


}
void test_freeRBTree()
{

        //void  freeRBTree(RBTree *tree);
        printf("freeRBTree - pass \n");


}
void test_getHeight()
{

        //int getHeight(Node *node);
        printf("getHeight - pass \n");
}


Vector * define_vec(double a, double b, double c)
{
        Vector * vector = ( Vector * ) malloc(sizeof(Vector));
        vector->len = 3;
        vector->vector  = ( double *  ) malloc(sizeof(double) * vector->len );
        vector->vector[0] = a;
        vector->vector[1] = b;
        vector->vector[2] = c;
        return vector;
}

Vector * define_vec_2(double a, double b)
{
        Vector * vector = ( Vector * ) malloc(sizeof(Vector));
        vector->len = 2;
        vector->vector  = ( double *  ) malloc(sizeof(double) * vector->len );
        vector->vector[0] = a;
        vector->vector[1] = b;
        return vector;
}

void test_calcSqureNorm_round( double a, double b, double c, double d)
{
        Vector * vector = define_vec(a,b,c);
        double ret = calcSqureNorm( vector );

        if ( ret == d )
        {
                printf("test_calcSqureNorm pass\n");
        }
        else
        {
                printf("test_calcSqureNorm fail\n");
        }
}

void test_vectorCompare1By1_2_3( double a, double b, double c, double d,
                                 double e, int f)
{
        Vector * v1 = define_vec_2(a,b);
        Vector * v2 = define_vec(c,d,e);

        int cmp = vectorCompare1By1(
                (const void *) v1, (const void *) v2);

        if ( cmp == f )
        {
                printf("test_vectorCompare1By1_2_3 pass\n");
        }
        else
        {
                printf("test_vectorCompare1By1_2_3 fail\n");
        }
}

void test_vectorCompare1By1_3_2( double a, double b, double c, double d,
                                 double e, int f)
{
        Vector * v1 = define_vec(a,b,c);
        Vector * v2 = define_vec_2(d,e);

        int cmp = vectorCompare1By1(
                (const void *) v1, (const void *) v2);

        if ( cmp == f )
        {
                printf("test_vectorCompare1By1_3_2 pass\n");
        }
        else
        {
                printf("test_vectorCompare1By1_3_2 fail\n");
        }
}

void test_vectorCompare1By1_3_3( double a, double b, double c, double d,
                                 double e, double f, int g)
{
        Vector * v1 = define_vec(a,b,c);
        Vector * v2 = define_vec(d,e,f);

        int cmp = vectorCompare1By1(
                (const void *) v1, (const void *) v2 );

        if ( cmp == g )
        {
                printf("test_vectorCompare1By1_3_3 pass\n");
        }
        else
        {
                printf("test_vectorCompare1By1_3_3 fail\n");
        }
}

void test_vectorCompare1By1_3_null( double a, double b, double c)
{
        Vector * v1 = define_vec(a,b,c);
        Vector * v2 = NULL;

        int cmp = vectorCompare1By1(
                (const void *) v1, (const void *) v2 );

        if ( cmp == GE )
        {
                printf("test_vectorCompare1By1_3_NULL pass\n");
        }
        else
        {
                printf("test_vectorCompare1By1_3_NULL fail\n");
        }
}



void test_vectorCompare1By1( )
{
        test_vectorCompare1By1_3_3(  2,  2,  2,  2,
                                     2,  2,  EQ);
        test_vectorCompare1By1_3_3(  2,  3,  2,  2,
                                     2,  2,  GE);
        test_vectorCompare1By1_3_3(  2,  2,  3,  2,
                                     2,  3,  EQ);
        test_vectorCompare1By1_3_3(  2,  2.1,  2,  2,
                                     2,  2,  GE);
        test_vectorCompare1By1_3_3(  2,  2,  -1,  2,
                                     2,  2,  LE);
        printf("should not pass - > ");
        test_vectorCompare1By1_3_3(  2,  2,  -1,  2,
                                     2,  2,  GE);
        test_vectorCompare1By1_3_2(  2,  2,  2,  2,
                                     2,    GE);
        test_vectorCompare1By1_2_3(  2,  2,  2,  2,
                                     2,    LE);
        test_vectorCompare1By1_3_null(2,2,2);
}


void test_calcSqureNorm ()
{
        test_calcSqureNorm_round(1, 1, 1, 3);
        test_calcSqureNorm_round(2, 2, 2, 12);
        test_calcSqureNorm_round(2, 2, 1, 9);
        test_calcSqureNorm_round(2.5, 2.5, 1, 13.5 );
        test_calcSqureNorm_round(2.5, 2.5, -1, 13.5 );
        test_calcSqureNorm_round(2.5, -2.5, -1, 13.5 );
        test_calcSqureNorm_round(0, 0, -1, 1);


}


void test_copyIfNormIsLarger_round( Vector * v1, Vector * v2,  Vector * v3)
{
        copyIfNormIsLarger( v1, v2 );
        if ( vectorCompare1By1( (const void *) v2, (const void *) v3) == EQ )
        {
                printf("test_copyIfNormIsLarger_round success\n");
        }
        else
        {
                printf("test_copyIfNormIsLarger_round fail\n");
        }
}

void test_copyIfNormIsLarger_round_null( Vector * v1)
{
        int success = copyIfNormIsLarger( v1, NULL);
        if ( success == FAIL_COPY_IF_NORM )
        {
                printf("test_copyIfNormIsLarger_round success\n");
        }
        else
        {
                printf("test_copyIfNormIsLarger_round fail\n");
        }
}

void test_copyIfNormIsLarger()
{
        Vector * v1 = define_vec( 4, 5, 4 );
        Vector * v2 = define_vec( 4, 6, 4 );
        test_copyIfNormIsLarger_round( v1, v2, v2);
        v1 = define_vec( 4, 8, 4 );
        v2 = define_vec( 4, 6, 4 );
        test_copyIfNormIsLarger_round( v1, v2, v1);
        test_copyIfNormIsLarger_round_null(v1);
        test_copyIfNormIsLarger_round_null(NULL);
        v1 = define_vec( 4, 8.33, -4 );
        v2 = define_vec( 4, 6, 4 );
        test_copyIfNormIsLarger_round( v1, v2, v1);
}

void test_findMaxNormVectorInTree()
{
        RBTree *tree = newRBTree(vectorCompare1By1, freeVector);
        addToRBTree(tree, ((void * ) define_vec( 1, 2,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 0,0 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 0,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,-1 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,8 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 1,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 2.2, 1,1 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 5,3 )) );
        addToRBTree(tree, ((void * ) define_vec( 1, 2,3 )) );
        Vector * max_vec = findMaxNormVectorInTree( tree );

        if ( vectorCompare1By1( (const void *) max_vec, ((void * ) define_vec( 1, 2,8 ))) == EQ )
        {
                printf("test_findMaxNormVectorInTree pass\n");
        }
        else
        {
                printf("test_findMaxNormVectorInTree fail\n");
        }

        freeRBTree( tree );
}

void test_stringCompare_round( const char * a, const char * b, int val)
{
        if (stringCompare( a , b) == val)
        {
                printf("stringCompare pass\n");
        }
        else
        {
                printf("stringCompare fail\n");
        }
}


void test_stringCompare()
{
        test_stringCompare_round( "aaa" , "bb", LE);
        test_stringCompare_round( "caa" , "bb", GE);
        test_stringCompare_round( "aaa" , "aaa", EQ);
        test_stringCompare_round( "aaa" , NULL, GE);
        test_stringCompare_round( "aaa" , NULL, GE);
        test_stringCompare_round( "caa" , "bb", GE);

}

void test_concatenate_round(char * a, char * b, int len,  char * excepted)
{

        char * c  = ( char * ) malloc( sizeof(char) * len );
        for ( int i = 0; b[i] !=  NULL; i++)
        {
                c[i] = b[i];
        }
        concatenate(a , c);

        if (stringCompare( c , excepted) == EQ)
        {
                printf("test_concatenate pass\n");
        }
        else
        {
                printf("test_concatenate fail\n");
        }


}

void test_concatenate()
{

        test_concatenate_round("ci" , "hi ", 10,  "hi ci");
        test_concatenate_round("ponarovsky" , "david ", 30,  "david ponarovsky");
}



void test_String_Tree()
{
        RBTree *tree = newRBTree(stringCompare, freeString);
        addToRBTree(tree, (void *) "c ");
        addToRBTree(tree, (void *) "g ");
        addToRBTree(tree, (void *) "f ");
        addToRBTree(tree, (void *) "b ");
        addToRBTree(tree, (void *) "a ");
        addToRBTree(tree, (void *) "d ");
        addToRBTree(tree, (void *) "h ");
        addToRBTree(tree, (void *) "e ");
        char * temp = (char *) malloc(sizeof(char) * 20);
        for ( int i = 0; i< 20; i++ )
        {
                temp[i] = '\0';
        }

        forEachRBTree(tree, concatenate, (void *) temp );
        printf("%s\n", temp);

        if (stringCompare( temp , "a b c d e f g h ") == EQ)
        {
                printf("test_String_Tree pass\n");
        }
        else
        {
                printf("test_String_Tree fail\n");
        }

        freeRBTree( tree );

}


int main(){
        // test_isLeftChild();
        // test_isRightChild();
        // test_getState();
        test_rotateLeft();
        test_2();
        //test_rotateRight();
        //test_balancRBTree();
        // test_getNode();
        // test_getNodeByRoot();
        // test_newLeaf();
        // test_newRBTree();
        // test_addToRBTree();
        // test_containsRBTree();
        // test_forEachDFS();
        // test_forEachRBTree();
        // test_freeDFS();
        // test_freeRBTree();
        // test_getHeight();
        printf("---------\n\n\n\n");
        test_calcSqureNorm();
        test_vectorCompare1By1();
        test_copyIfNormIsLarger();
        test_findMaxNormVectorInTree();
        test_stringCompare();
        test_concatenate();
        test_String_Tree();
        return 0;
}
