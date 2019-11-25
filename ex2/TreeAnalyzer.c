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


const char * ERROR                  = "Invalid input\n";
const char * USAGE                  = "Usage:  TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n";
const char * MSGMAXHEIGHT           = "Length of Maximal Branch: %d\n";
const char * MSGMINHEIGHT           = "Length of Minimal Branch: %d\n";
const char * MSGNUMBEROFVERTAX      = "Vertices Count: %d\n";
const char * MSGNUMBEROFEDGES       = "Edges Count: %d\n";
const char * MSGDIAMETERTREE        = "Diameter Length: %d\n";
const char * MSGDROOTKEY            = "Root Vertex: %d\n";
const char * MSGSHORTEST            = "Shortest Path Between %d and %d:";
const char ZERODIGIT ='0';
const char ONEDIGIT  ='1';
const char NINEDIGIT ='9';



// -------------------------- const definitions -------------------------

typedef struct node_list_t NodeList;
typedef struct node_list_t List;
typedef struct node_t Node;

typedef struct node_t
{
        int key;
        List * edges;
        Node * perent;

} Node;

static Node** graph;

typedef struct node_list_t
{
        NodeList * next;
        Node * node;
} NodeList;
typedef int (*compare_func)(int x, int y);

List * allocList();
Node * allocNode(int key);
Node * getRoot(Node * node);
Node ** parsing_file(const char * path);
void connectEdge(Node * perent, Node * children);
void listpush (List * list_obj, Node * item);
void freeList( List * lstptr);
void print_path(Node *u, Node *v, int n);
void freegraph( Node** nodes_array  );
int maxHeight(Node * root);
int minHeight(Node * root);
int getHeightbyfun(Node * root, compare_func compare);
int getNodes(Node * root);
int getDiameter(Node *root);
int check_if_digit( char charter );
int check_if_number( char const * str );

/**
 * @brief free the address of given nodes array.
 * @return nothing.
 */
void freegraph( Node** nodes_array  )
{
        for (Node ** ptr_nodes = nodes_array; *ptr_nodes; ptr_nodes++)
        {
                freeList((*ptr_nodes)->edges);
        }
        free(nodes_array);
}
/**
 * @brief clean the graph and exit if the flag given flag turned on.
 * @return nothing.
 */
void exit_failure( int flag )
{
        if ( flag )
        {
                //freegraph( graph );
                fprintf( stderr, "%s", ERROR);
                exit(EXIT_FAILURE);
        }
}

// ------------------------------ functions -----------------------------

/**
 * @brief pushing element to the end of the lsit.
 * @return nothing.
 */
void listpush (List * list_obj, Node * item)
{
        List * ptr = list_obj;
        // getting the last element.
        while(ptr->next != NULL)
        {
                ptr = ptr->next;
        }
        ptr->next = allocList();
        ptr->next->node = item;
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

                exit_failure( ptr->node->key == children->key );
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
char peek_file(FILE *fp)
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
        return children < n && children >= 0 && children != perent;
}

/**
 * @brief pop_spaces - popping spaces from the stream stream.
 * @return nothing.
 */
void pop_spaces(FILE *fp)
{
        while( peek_file(fp) == ' ' || peek_file(fp) == '\t' )
        {
                getc(fp);
        }
}
/**
 * @brief get_next_number - return the next number from the stream.
 * @return nothing but storing the number in the given address.
 */
void get_next_number(FILE *fp, int * variable)
{
        pop_spaces(fp);
        char worktype [64];
        fscanf (fp, "%s", worktype);
        exit_failure( !check_if_number( worktype ) );
        sscanf(worktype, "%d", variable);
        //
}

/**
 * @brief parsing_file - generating the graph by reading a given file path
 * @return array of Nodes pointers.
 */
Node ** parsing_file(const char * path)
{
        FILE *fp;
        fp = fopen(path, "r");
        int n;

        exit_failure ( peek_file(fp) == EOF );
        get_next_number(fp, &n);
        exit_failure ( n == 0 );

        Node ** nodes = malloc( sizeof(Node *) * n );
        for (int i = 0; i < n; i++) {
                nodes[i] = allocNode(i);
        }

        pop_spaces(fp);
        getc(fp);
        int perent = 0, children;
        while(peek_file(fp) != EOF)
        {
                pop_spaces(fp);
                while(peek_file(fp) != EOF && peek_file(fp) != '\n' && peek_file(fp) != '-')
                {
                        get_next_number(fp, &children);
                        exit_failure(!connectable( perent, children, n));
                        connectEdge(nodes[perent], nodes[children]);
                        pop_spaces(fp);
                }
                if (peek_file(fp) == '-')
                {
                        getc(fp);
                }
                pop_spaces(fp);
                getc(fp);
                perent++;
        }

        exit_failure ( n != perent );


        fclose (fp);
        return nodes;
}
/**
 * @brief print_path printing the shortest path between u and v.
 * @return nothing.
 */
void print_path(Node *u, Node *v, int nodes)
{

        // List * leftpart =   allocList();
        List * rightpart =  allocList();

        int * color = calloc( nodes, sizeof(int) );

        printf( MSGSHORTEST, u->key, v->key );

        for (Node * ptr = v; ptr != NULL; ptr=ptr->perent)
        {
                List * temp = allocList();
                rightpart->node = ptr;
                temp->next = rightpart;
                rightpart = temp;
                color[ptr->key] = 1;
        }
        rightpart = rightpart->next;

        Node * intersection;
        for (intersection = u; intersection != NULL && (!color[intersection->key]);
             intersection=intersection->perent)
        {
                printf(" %i",intersection->key);
        }

        List * right_ptr;
        for (right_ptr = rightpart; right_ptr != NULL &&
             right_ptr->node != intersection; right_ptr = right_ptr->next)
        {

        }
        for (; right_ptr != NULL; right_ptr = right_ptr->next)
        {
                printf(" %i",right_ptr->node->key);
        }

        freeList(rightpart);
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
                return 1;
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
        return 1 + ret;
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
        return getHeightbyfun(root, &max) - 1;
}
/**
 * @brief return the minimum length from the root to leaf
 * @return the minimum length from the root to leaf
 */
int minHeight(Node * root)
{
        return getHeightbyfun(root, &min) - 1;
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
        swap(_max, 2, 1);
        swap(_max, 1, 0);
        swap(_max, 2, 1);
}
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int getDiameter(Node *root){
        int ret = 0;
        int _max[3] = {0, 0,0};

        if ( root->edges->node == NULL )
        {
                return 0;
        }

        List * ptr_node = root->edges;
        int i;

        for (i = 0; i < 2 && ptr_node != NULL && ptr_node->node != NULL; i++)
        {
                _max[i] = maxHeight(ptr_node->node);
                ptr_node = ptr_node->next;
        }
        if ( i == 1)
        {
                ret =  _max[0] + 1;
        }
        else if ( i > 1 )
        {
                for (; ptr_node->node != NULL;
                     ptr_node = ptr_node->next)
                {

                        _max[2] = maxHeight(ptr_node->node);
                        sort(_max);
                }

                ret =  _max[0] + _max[1] + 2;
        }

        for (ptr_node = root->edges; ptr_node->node != NULL;
             ptr_node = ptr_node->next) {

                ret = max(ret, getDiameter(ptr_node->node));

        }
        return ret;

}
/**
 * @brief return 1 if the given charter is digit
 * @return return 1 if the given charter is digit.
 */
int check_if_digit( char charter )
{
        return charter >= '0' && charter <= '9';
}
/**
 * @brief return 1 if the given string is intger.
 * @return return 1 if the given string is intger.
 */
int check_if_number( char const * str )
{
        char const * ptr = str;
        if ( *ptr == '0' && (!*( ptr + 1 )) )
        {
                return 1;
        }
        if ( *ptr < '1' || *ptr >'9'   )
        {
                return 0;
        }
        for (; *ptr; ptr++)
        {
                if (!check_if_digit(*ptr))
                {
                        return 0;
                }
        }
        return 1;
}
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int main(int argc, char const *argv[])
{


        if ( argc == 4 && check_if_number(argv[2]) && check_if_number(argv[3]) )
        {

                exit_failure( access( argv[1], F_OK ) == -1  );

                graph = parsing_file( argv[1] );
                Node * root = getRoot(graph[0]);

                int u, v;

                sscanf(argv[2], "%d", &u);
                sscanf(argv[3], "%d", &v);

                int graph_size = getNodes(root);
                exit_failure ( u >= graph_size || v >= graph_size
                               || u < 0 || v < 0 );

                printf(MSGDROOTKEY, root->key);
                printf(MSGNUMBEROFVERTAX, graph_size);
                printf(MSGNUMBEROFEDGES, graph_size - 1);
                printf(MSGMINHEIGHT, minHeight(root));
                printf(MSGMAXHEIGHT, maxHeight(root));
                printf(MSGDIAMETERTREE, getDiameter(root));
                print_path(graph[u], graph[v], graph_size);

        }
        else
        {
                fprintf(stderr,"%s", USAGE );
                return EXIT_FAILURE;
        }

        return 0;
}
