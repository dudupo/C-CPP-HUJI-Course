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

void connectEdge(Node * perent, Node * children);
void listpush (List * list_obj, Node * item);
Node * allocNode(int key);
List * allocList();
Node * getRoot(Node * node);
