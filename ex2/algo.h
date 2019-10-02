void print_path(Node *u , Node *v, int n);
int maxHeight(Node * root);
int minHeight(Node * root);
typedef int (*compare_func)(int x, int y);
int getHeightbyfun(Node * root, compare_func compare);
int getNodes(Node * root);
int getDiameter(Node *root);
