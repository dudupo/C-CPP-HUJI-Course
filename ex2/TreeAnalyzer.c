/**
 * @file TreeAnalyzer.c
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
#include <unistd.h>
// -------------------------- const definitions -------------------------

#define REQUIREDPATHTOSTORE 3
const char * ERROR                  = "Invalid input\n";
const char * USAGE                  = "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n";
const char * MSGMAXHEIGHT           = "Length of Maximal Branch: %d\n";
const char * MSGMINHEIGHT           = "Length of Minimal Branch: %d\n";
const char * MSGNUMBEROFVERTAX      = "Vertices Count: %d\n";
const char * MSGNUMBEROFEDGES       = "Edges Count: %d\n";
const char * MSGDIAMETERTREE        = "Diameter Length: %d\n";
const char * MSGDROOTKEY            = "Root Vertex: %d\n";
const char * MSGSHORTEST            = "Shortest Path Between %d and %d:";
const char * STRINGFORMAT = "%s";
const char * DECFORMAT = "%d";
const char * FORMATNODEINPATH = " %d";
const char * FILEREADFORMAT = "r";
const char UPSCORE = '-';
const char ZERODIGIT = '0';
const char ONEDIGIT  = '1';
const char NINEDIGIT = '9';
const char SPACE = ' ';
const char TAB = '\t';
const char NEWLINE = '\n';
const int ISNUMBER = 1;
const int ISNOTNUMBER = 0;
const int ZERO = 0;
const int RED = 1;
const int EMPTYPATH = 0;
const int LEAFHEIGT = 1;
const int EDGELENGTH = 1;
const int PREPROCESSINGITEMS = 2;
const int FIRSTITEM = 0;
const int LONGESTPATH = 0;
const int SECONDPATH = 1;
const int TEMPPATH = 2;
const int FIRSTARG = 1;
const int SECONDARG = 2;
const int TREETHARG = 3;
const int NUMBEROFARGS = 4;
const int FAILTOOPEN = -1;
const int SUCCEED = 0;
const int ARBITRARYNODE = 0;
const int HISTTONEXTCHARTER = 1;
const int ENDOFSEG = 1;

// -------------------------- const definitions -------------------------

typedef struct node_list_t NodeList;
typedef struct node_list_t List;
typedef struct node_t Node;
/**
 * @brief define a vertex in the graph.
 */
typedef struct node_t
{
        int key;
        List * edges;
        Node * perent;

} Node;

static Node** graph = NULL;
/**
 * @brief define a linked list.
 */
typedef struct node_list_t
{
        NodeList * next;
        Node * node;
} NodeList;
typedef int (*compare_func)(int x, int y);

List * allocList();
Node * allocNode(int key);
Node * getRoot(Node * node);
Node ** parsingFile(FILE *, int);
void connectEdge(Node * perent, Node * children);
// void listPush (List * list_obj, Node * item);
void freeList( List * lstptr);
void printPath(Node *u, Node *v, int n);
void freeGraph( Node** nodes_array  );
int maxHeight(Node * root);
int minHeight(Node * root);
int getHeightbyfun(Node * root, compare_func compare);
int getNodes(Node * root);
int getDiameter(Node *root);
int checkIfDigit( char charter );
int checkIfNumber( char const * str );

// ------------------------------ functions -----------------------------

/**
 * @brief free the address of given nodes array.
 * @return nothing.
 */
void freeGraph( Node** nodes_array  )
{
        if ( nodes_array != NULL )
        {
                Node ** ptr_nodes = nodes_array;
                for (; *ptr_nodes != NULL; ptr_nodes++)
                {
                        freeList((*ptr_nodes)->edges);
                        free((*ptr_nodes));
                }
        }
        free(nodes_array);
}
/**
 * @brief clean the graph and exit if the flag given flag turned on.
 * @return nothing.
 */
void exitFailure( int flag )
{
        if ( flag )
        {
                freeGraph( graph );
                fprintf( stderr, STRINGFORMAT, ERROR);
                exit(EXIT_FAILURE);
        }
}
/**
 * @brief allocate a node, indexed by the given kay.
 * @return poiter to the initialized node.
 */
Node * allocNode(int key)
{
        Node * _node = malloc(sizeof(Node));
        _node->edges = allocList();
        _node->key = key;
        _node->perent = NULL;
        return _node;
}
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
List * allocList()
{
        List * first = malloc(sizeof(List));
        first->node = NULL;
        first->next = NULL;
        return first;
}
/**
 * @brief fre the address of given list.
 * @return nothing.
 */
void freeList( List * lstptr)
{
        if ( lstptr->next )
        {
                freeList(lstptr->next);
        }
        free(lstptr);
}
/**
 * @brief define a fater-son relashionship between two vertex.
 * @return nothing.
 */
void connectEdge(Node * perent, Node * children)
{
        List * ptr = perent->edges;
        while(ptr->node != NULL)
        {
                exitFailure( ptr->node->key == children->key );
                ptr = ptr->next;
        }
        ptr->next = allocList();
        ptr->node = children;
        children->perent = perent;
}
/**
 * @brief extracting the root of the tree.
 * @return pointer to the root.
 */
Node * getRoot(Node * node)
{
        Node * ptr = node;
        while (ptr && ptr->perent)
        {
                ptr = ptr->perent;
        }
        return ptr;
}
/**
 * @brief reading the first charter and pushing it back for the stream.
 * @return the heading charther.
 */
char peekFile(FILE *fp)
{
        char ret = getc(fp);
        ungetc(ret, fp);
        return ret;
}
/**
 * @brief connectable - checking if we can connect the given pair.
 * @return 1 if the vertex in range (1,n) and not equal to each other.
 */
int connectable(int perent, int children, int n)
{
        return children < n && children >= ZERO && children != perent;
}

/**
 * @brief popSpaces - popping spaces from the stream stream.
 * @return nothing.
 */
void popSpaces(FILE *fp)
{
        while( peekFile(fp) == SPACE || peekFile(fp) == TAB )
        {
                getc(fp);
        }
}
/**
 * @brief getNextNumber - return the next number from the stream.
 * @return nothing but storing the number in the given address.
 */
void getNextNumber(FILE *fp, int * variable)
{
        popSpaces(fp);
        char worktype [64];
        fscanf (fp, STRINGFORMAT, worktype);
        exitFailure( !checkIfNumber( worktype ) );
        sscanf(worktype, DECFORMAT, variable);
}

/**
 * @brief extractingGraphSize - storing the number of the nodes.
 * @return nothing.
 */
void extractingGraphSize(FILE * fp, int * nodescount)
{
        exitFailure ( peekFile(fp) == EOF );
        getNextNumber(fp, nodescount);
        exitFailure ( *nodescount == ZERO );
}
/**
 * @brief parsingFile - generating the graph by reading a given file path
 * @return array of Nodes pointers.
 */
Node ** parsingFile(FILE * file_object, int graph_size)
{
        // allocate array to store the nodes.
        Node ** nodes = calloc( sizeof(Node *),  graph_size + ENDOFSEG  );
        for (int node_index = ZERO; node_index < graph_size; node_index++)
        {
                nodes[node_index] = allocNode(node_index);
        }
        // define the last element as NULL for stopping condition in the
        // iteration.
        nodes[graph_size]  = NULL;
        // popping spaces
        popSpaces(file_object);

        // get rid of '\n' charter
        exitFailure (peekFile(file_object) != NEWLINE);
        getc(file_object);
        // initialize the perent, the node which the line discribe.
        int perent = ZERO, children;
        // iterate over the lines.
        while(peekFile(file_object) != EOF)
        {
                // exit in case there are too many lines
                exitFailure ( perent < graph_size );
                popSpaces(file_object);
                // exit in case of empty line
                exitFailure (peekFile(file_object) == NEWLINE);
                // define the nmbers in the line as the childrens of the node
                // which indexed as the line number.
                while(peekFile(file_object) != EOF &&
                      peekFile(file_object) != NEWLINE && peekFile(file_object) != UPSCORE)
                {
                        getNextNumber(file_object, &children);
                        exitFailure(!connectable( perent, children, graph_size));
                        // connect the perent to the child.
                        connectEdge(nodes[perent], nodes[children]);
                        popSpaces(file_object);
                }
                // handle the case when the line include only '-'.
                if (peekFile(file_object) == UPSCORE)
                {
                        getc(file_object);
                }
                popSpaces(file_object);

                // get rid of '\n' charter
                getc(file_object);

                // increasing the perent to the follwing line.
                perent++;


        }

        exitFailure ( graph_size != perent );
        fclose (file_object);
        return nodes;
}
/**
 * @brief printPath printing the shortest path between u and v.
 * @return nothing.
 */
void printPath(Node *u, Node *v, int nodes)
{
        // the 'rightpart' will store the path from thr root to v.
        List * rightpart =  allocList();
        int * color = calloc( nodes, sizeof(int) );

        printf( MSGSHORTEST, u->key, v->key );
        // first we find the lca(u,v) the last common ancestor of the nodes
        // so, we colring in red all the nodes in the path from v to the
        // root.
        for (Node * ptr = v; ptr != NULL; ptr = ptr->perent)
        {
                List * temp = allocList();
                rightpart->node = ptr;
                temp->next = rightpart;
                rightpart = temp;
                color[ptr->key] = RED;
        }

        // wil be used to free the list.
        List * entrypoint = rightpart;


        rightpart = rightpart->next;
        Node * intersection;
        // than we climb up from u to the root, untill we encounter the
        // lca, ( the first red node. )
        for (intersection = u;
             intersection != NULL && (color[intersection->key] != RED);
             intersection = intersection->perent)
        {
                // while climbing we printingt the nodes. ( the left part )
                printf(FORMATNODEINPATH, intersection->key);
        }
        List * right_ptr;
        // the 'right part' contains the nodes on the path from the root to u
        // so now, we will getting dawn in the tree, unill we get the lca.
        for (right_ptr = rightpart; right_ptr != NULL &&
             right_ptr->node != intersection; right_ptr = right_ptr->next)
        {

        }
        // than we, get dawn to v from the lca, while printing the 'right part'
        // of the path between u to v.
        for (; right_ptr != NULL; right_ptr = right_ptr->next)
        {
                printf(FORMATNODEINPATH, right_ptr->node->key);
        }
        // cleaning.
        freeList(entrypoint);
        free(color);
        // free(entrypoint);
        // free(rightpart);
        // free(intersection);
        printf("\n");


}
/**
 * @brief getHeightbyfun- getting the maximal or minimal height from the
 * given node, depending on the 'compare_func' - the choosing method.
 * @return the height of the tree.
 */
int getHeightbyfun(Node * root, compare_func compare)
{
        int ret, height;

        // if the node is a leaf than return 0
        if ( root->edges->node == NULL )
        {
                return LEAFHEIGT;
        }
        // define a pointer which will be used to iterate over the edges.
        List * ptr_node = root->edges;
        // call reqursivly on the fist child.
        ret = getHeightbyfun(ptr_node->node, compare);
        // iterate over the other children, and calculate their height.
        for (ptr_node = ptr_node->next; ptr_node->node != NULL;
             ptr_node = ptr_node->next)
        {
                // calculate the height of the current child.
                height = getHeightbyfun(ptr_node->node, compare);
                // than, choose which height to store by the given comparing function.
                ret = compare(ret, height);
        }
        // adding the contrbutie of the current node to the height.
        return EDGELENGTH + ret;
}
/**
 * @brief max - return the maximum of two variables.
 * @return return the maximum of two variables.
 */
int max(int x, int y)
{
        return x > y ? x : y;
}
/**
 * @brief min - return the minimum of two variables.
 * @return return the minimum of two variables.
 */
int min(int x, int y)
{
        return x > y ? y : x;
}
/**
 * @brief sum - return the summation of two variables.
 * @return the summation of two variables.
 */
int sum(int x, int y)
{
        return x + y;
}
/**
 * @brief return the maximum length from the root to leaf
 * @return the maximum length from the root to leaf
 */
int maxHeight(Node * root)
{
        return getHeightbyfun(root, &max) - EDGELENGTH;
}
/**
 * @brief return the minimum length from the root to leaf
 * @return the minimum length from the root to leaf
 */
int minHeight(Node * root)
{
        return getHeightbyfun(root, &min) - EDGELENGTH;
}

/**
 * @brief count the total number of children of given node.
 * @return the number of children of given node.
 */
int getNodes(Node * root)
{
        return getHeightbyfun(root, &sum);
}
/**
 * @brief swap the positions of two elements in the array in case they don`t
 * ordered in sorted order.
 * @return nothing.
 */
void swap(int * _max, int i, int j)
{
        if (_max[i] > _max[j])
        {
                int temp = _max[i];
                _max[i] = _max[j];
                _max[j] = temp;
        }
}
/**
 * @brief sorting array of
 * @return 0, to tell the system the execution ended without errors.
 */
void sort(int * _max)
{
        swap(_max, TEMPPATH, SECONDPATH);
        swap(_max, SECONDPATH, LONGESTPATH);
        swap(_max, TEMPPATH, SECONDPATH);
}
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int getDiameter(Node *root)
{
        // init ret, the variable which will store the longest of the paths-
        // -wich have been examined.
        int ret = ZERO;
        // we need to store 3 paths each time, the two lonest and onother
        // temp path which will be use to examine alternative diameter.
        int _max[REQUIREDPATHTOSTORE] = {ZERO, ZERO, ZERO};

        if ( root->edges->node == NULL )
        {
                return EMPTYPATH;
        }
        // initialize pointer which will iterate over the childrens of the node.
        List * ptr_node = root->edges;
        int index;
        // fill the fitst and the second positions of _max. _max[0] will store
        // the longest path, _max[1] will store the second path in length.
        for (index = ZERO; index < TEMPPATH && ptr_node != NULL &&
             ptr_node->node != NULL; index++)
        {
                // calculating the longest path of the children and add to it
                // the length of the edge which connecting the perent to
                // the children.
                _max[index] = maxHeight(ptr_node->node) + EDGELENGTH;
                ptr_node = ptr_node->next;
        }
        if ( index == SECONDPATH)
        {
                // in case that the node has only one child.
                ret =  _max[LONGESTPATH];
        }
        else if ( index > SECONDPATH )
        {
                // search for alternative to the longest and the second path.
                for (; ptr_node->node != NULL;
                     ptr_node = ptr_node->next)
                {

                        _max[TEMPPATH] = maxHeight(ptr_node->node) + EDGELENGTH;
                        // srot the _max array, make sure that the longest will
                        // be stored in the first position, and the seconed
                        // right after him.
                        sort(_max);
                }
                // calculate the diameter that passes through the node.
                ret =  _max[LONGESTPATH] + _max[SECONDPATH];
        }
        // iterate in reqursivly over the sub trees, and looking for diameters
        // that doesn't pass through the node.
        for (ptr_node = root->edges; ptr_node->node != NULL;
             ptr_node = ptr_node->next)
        {
                ret = max(ret, getDiameter(ptr_node->node));
        }
        return ret;

}
/**
 * @brief return 1 if the given charter is digit
 * @return return 1 if the given charter is digit.
 */
int checkIfDigit( char charter )
{
        return charter >= ZERODIGIT && charter <= NINEDIGIT;
}
/**
 * @brief return 1 if the given string is intger.
 * @return return 1 if the given string is intger.
 */
int checkIfNumber( char const * str )
{
        char const * ptr = str;
        // check an endcase, str = '0'
        if ( *ptr == ZERODIGIT && (!*( ptr + HISTTONEXTCHARTER )) )
        {
                return ISNUMBER;
        }
        // check that the first charter inside the range '1'-'9'
        if ( *ptr < ONEDIGIT || *ptr > NINEDIGIT   )
        {
                return ISNOTNUMBER;
        }
        // iterate over the string
        for (; *ptr; ptr++)
        {
                // if the charter isn't digit.
                if (!checkIfDigit(*ptr))
                {
                        return ISNOTNUMBER;
                }
        }
        return ISNUMBER;
}
/**
 * @brief The main function.
 * @return 0, to tell the system the execution ended without errors.
 */
int main(int argc, char const *argv[])
{

        // check the args
        if ( argc == NUMBEROFARGS )
        {
                // checking that the given nodes u, and v are integers.
                exitFailure(!checkIfNumber(argv[SECONDARG]));
                exitFailure(!checkIfNumber(argv[TREETHARG]));
                // check the file path.
                exitFailure( access( argv[FIRSTARG], F_OK ) == FAILTOOPEN );
                FILE *file_object;
                file_object = fopen(argv[FIRSTARG], FILEREADFORMAT);
                int graph_size;
                extractingGraphSize(file_object, &graph_size);
                // generate the Graph
                graph = parsingFile( file_object, graph_size );
                Node * root = getRoot(graph[ARBITRARYNODE]);

                int u, v;
                // the scanning is safe becuse the argv[2] and argv[3]
                // alraedy confered as integers.
                sscanf(argv[SECONDARG], DECFORMAT, &u);
                sscanf(argv[TREETHARG], DECFORMAT, &v);
                // extracting the graph size.

                exitFailure ( u >= graph_size || v >= graph_size
                              || u < ZERO || v < ZERO );
                // execute and print all the missions.
                printf(MSGDROOTKEY, root->key);
                printf(MSGNUMBEROFVERTAX, graph_size);
                printf(MSGNUMBEROFEDGES, graph_size - EDGELENGTH);
                printf(MSGMINHEIGHT, minHeight(root));
                printf(MSGMAXHEIGHT, maxHeight(root));
                printf(MSGDIAMETERTREE, getDiameter(root));
                printPath(graph[u], graph[v], graph_size);

                freeGraph(graph);

        }
        else
        {
                fprintf(stderr, STRINGFORMAT, USAGE );
                return EXIT_FAILURE;
        }

        return SUCCEED;
}
