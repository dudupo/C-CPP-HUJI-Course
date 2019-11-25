#ifndef HEADERS
#include "headers.h"
#endif

void print_path(Node *u , Node *v, int n) {

    List * leftpart =   allocList();
    List * rightpart =  allocList();
    int * color = calloc( n, sizeof(int) );


    for (Node * ptr = v;
         ptr != NULL;
          ptr=ptr->perent) {

        List * temp = allocList();
        rightpart->node = ptr;
        temp->next = rightpart;
        rightpart = temp;
        color[ptr->key] = 1;
    }

	rightpart = rightpart->next;

	Node * intersection;
    for (intersection = u;
         intersection != NULL && (!color[intersection->key]);
          intersection=intersection->perent) {

        leftpart->node = intersection;
        leftpart->next = allocList();

        printf("%i ",intersection->key);

    }


	List * right_ptr;
    for (right_ptr = rightpart;
		 right_ptr != NULL && right_ptr->node != intersection;
		  right_ptr = right_ptr->next) {
	}

    for (;
		 right_ptr != NULL;
		  right_ptr = right_ptr->next) {
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
