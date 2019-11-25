#include <stdio.h>
#include <stdlib.h>

typedef struct node_list_t NodeList;
typedef struct node_list_t List;
typedef struct node_t Node;

typedef struct node_t
{
    int key;
    List * edges;
    Node * perent;

} Node;

typedef struct node_list_t
{
    NodeList * next;
    Node * node;
} NodeList;

// typedef struct graph_t
// {
//     Node * root;
//     int size;
// } Graph;




void connectEdge(Node * perent, Node * children);
void listpush (List * list_obj, Node * item);
Node * allocNode(int key);
List * allocList();
Node * getRoot(Node * node);

// typedef Node ** Graph;
Node ** parsing_file(const char * path);

void print_path(Node *u , Node *v, int n);
int maxHeight(Node * root);
int minHeight(Node * root);
typedef int (*compare_func)(int x, int y);
int getHeightbyfun(Node * root, compare_func compare);
int getNodes(Node * root);
int getDiameter(Node *root);


void listpush (List * list_obj, Node * item) {
  // malloc(sizeof(Queue))
    List * ptr = list_obj;
    while(ptr->node != NULL)
        ptr = ptr->next;
    ptr->node = item;
    ptr->next = allocList();
}

Node * allocNode(int key) {
    Node * _node = malloc(sizeof(Node));
    _node->edges = allocList();
    _node->key = key;
    _node->perent = NULL;
    return _node;
}

List * allocList() {
    List * first = malloc(sizeof(List));
    first->node = NULL;
    first->next = NULL;
    return first;
}

void connectEdge(Node * perent, Node * children) {
    listpush(perent->edges, children);
    //listpush(children->edges, perent);
    children->perent = perent;
}

Node * getRoot(Node * node) {
    Node * ptr = node;
    while (ptr && ptr->perent)
    {
      ptr = ptr->perent;
    }
    return ptr;
}

char peek_file(FILE *fp) {
		char ret = getc(fp);
		ungetc(ret, fp);
		return ret;
}

int connectable(int perent, int children, int n){
	return children < n && children >= 0 && children != perent;
}


Node ** parsing_file(const char * path) {
   FILE *fp;
   fp = fopen(path, "r");
   int n;
   fscanf (fp, "%i", &n);
   Node ** nodes = malloc( sizeof(Node *) * n );
   for (int i = 0 ; i < n; i++) {
      nodes[i] = allocNode(i);
   }
	getc(fp);
	int perent = 0 , children;
	while(peek_file(fp) != EOF)
	{
		while(peek_file(fp) != '\n' && peek_file(fp) != '-')
		{
			fscanf (fp, "%i", &children);
			if (connectable( perent, children, n))
			{
				connectEdge(nodes[perent], nodes[children]);
			}
		}
		if (peek_file(fp) == '-')
		{
			getc(fp);
		}
		getc(fp);
		perent++;
   }

   fclose (fp);
	return nodes;
}

void print_path(Node *u , Node *v, int n) {

    List * leftpart =   allocList();
    List * rightpart =  allocList();

    int * color = calloc( n, sizeof(int) );


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

        leftpart->node = intersection;
        leftpart->next = allocList();
        printf("%i ",intersection->key);

    }

	List * right_ptr;
    for (right_ptr = rightpart;
		 right_ptr != NULL && right_ptr->node != intersection;
		  right_ptr = right_ptr->next)
   {

	}
   for (; right_ptr != NULL; right_ptr = right_ptr->next) {
		printf("%i ",right_ptr->node->key);
	}
	printf("\n");
}

int getHeightbyfun(Node * root, compare_func compare) {
	int ret, height;

	if ( root->edges->node == NULL )
		return 1;

	List * ptr_node = root->edges;
	ret = getHeightbyfun(ptr_node->node, compare);

	for (ptr_node = ptr_node->next;
		 ptr_node->node != NULL;
		  ptr_node = ptr_node->next) {

		height = getHeightbyfun(ptr_node->node, compare);
		ret = compare(ret, height);
	}
	return 1 + ret;
}

int max(int x, int y){
	return x > y ? x : y;
}
int min(int x, int y){
	return x > y ? y : x;
}
int sum(int x, int y){
	return x + y;
}
// (compare_func)
int maxHeight(Node * root) {
	return getHeightbyfun(root, &max);

}
int minHeight(Node * root) {
	return getHeightbyfun(root, &min);
}

int getNodes(Node * root) {
	return getHeightbyfun(root, &sum);
}


void swap(int * _max, int i , int j) {
	if (_max[i] > _max[j]) {
		int temp = _max[i];
		_max[i] = _max[j];
		_max[j] = temp;
	}
}

void sort(int * _max) {
	swap(_max, 2, 1);
	swap(_max, 1, 0);
}


int getDiameter(Node *root){
	int ret = 0;
	int _max[3] = {0, 0 ,0};

	if ( root->edges->node == NULL )
		return 0;

	List * ptr_node = root->edges;
	int i;

	for (i = 0; i < 2 && ptr_node->node != NULL; i++)
		_max[i] = maxHeight(ptr_node->node);

	sort(_max);

	for (ptr_node = ptr_node->next;
		 ptr_node->node != NULL;
		  ptr_node = ptr_node->next) {

		_max[3] = maxHeight(ptr_node->node);
		sort(_max);
	}

	ret =  _max[0] + _max[1] - 2;

	for (ptr_node = root->edges;
		 ptr_node->node != NULL;
		  ptr_node = ptr_node->next) {

		ret = max(ret, getDiameter(ptr_node->node));

	}
	return ret;

}
int main(int argc, char const *argv[]) {


  if ( argc > 1 ) {

     Node** graph = parsing_file( argv[1] );
     Node * root = getRoot(graph[0]);
     printf("root-key : %d\n", root->key);
     int u , v;
     sscanf(argv[2], "%d", &u);
     sscanf(argv[3], "%d", &v);
     print_path(graph[u], graph[v], (int) sizeof(graph));
     printf("max height -> %i \n", maxHeight(root));
     printf("min height -> %i \n", minHeight(root));
     printf("number of vertax -> %i\n", getNodes(root));
     printf("number of edges -> %i\n", getNodes(root) - 1);
     printf("diameter of the tree -> %i\n", getDiameter(root));
  }

  return 0;
}
