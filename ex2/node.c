#ifndef HEADERS
#include "headers.h"
#endif

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
    return _node;
}

List * allocList() {
    List * first = malloc(sizeof(List));
    first->node = NULL;
    return first;

}

void connectEdge(Node * perent, Node * children) {
    listpush(perent->edges, children);
    //listpush(children->edges, perent);
    children->perent = perent;
}

Node * getRoot(Node * node) {
    Node * ptr = node;
    while (ptr->perent)
        ptr = ptr->perent;
    return ptr;
}
