#ifndef RBTREE_RBTREE_H
#include "RBTree.h"
#endif

#include <stdlib.h>
#define LE -1
#define EQ 0
#define GE 1
#define CASE1_ROOT 0
#define CASE2_PARENT_BLACK  1
#define CASE3_PARENT_AND_UNCLE_RED  2
#define CASE4_PARENT_RED  3
void* const LEAF = NULL;
int const SUCCES_ADD = 1;
int const FAIL_ADD = 0;
int const IS_RIGHT_CHILD = 1;
int const IS_LEFT_CHILD = 1;
int const SUCCES_FOR_EACH = 1;
int const FAIL_FOR_EACH = 0;
int const EMPTY_TREE_SIZE = 0;
int const ADD_ELEMENT = 1;





/**
 *  return 1 if the node is the left children of his
 *  parent.
 *  @param firstNode, secondNonde : given nodes
 */
int isLeftChild( Node * node )
{

        if (node == NULL || node->parent == NULL)
        {
                return !IS_LEFT_CHILD;
        }
        if (node->parent->left == node)
        {
                return IS_LEFT_CHILD;
        }
        return !IS_LEFT_CHILD;
}
/**
 *  return 1 if the node is the right children of his
 *  parent.
 *  @param firstNode, secondNonde : given nodes
 */
int isRightChild( Node * node)
{
        if( node == NULL || node->parent == NULL)
        {
                return !IS_RIGHT_CHILD;
        }
        if (node->parent->right == node)
        {
                return IS_RIGHT_CHILD;
        }
        return !IS_RIGHT_CHILD;
}

/**
 *  return the state of relashionship, between the node
 *  and his ancestors. numberd by the exercise defintion.
 *  the state will detrminate which rotate should be done.
 *  @param firstNode, secondNonde : given nodes
 *  @return the number of the state.
 */
int getState (Node * node)
{
        if ( node->parent == NULL )
        {
                return CASE1_ROOT;
        }
        if ( node->parent->color == BLACK  )
        {
                return CASE2_PARENT_BLACK;
        }
        if ( node->parent && node->parent->parent &&
             node->parent->parent->right->color == RED &&
             node->parent->parent->left->color == RED)
        {
                return CASE3_PARENT_AND_UNCLE_RED;
        }
        return CASE4_PARENT_RED;
}


/**
 *  rotate left the given node
 *  @param tree: the current node
 */
void rotateLeft( Node * node )
{
        Node * rightchild = node->right;
        rightchild->parent = node->parent;

        if (isLeftChild(node) == IS_LEFT_CHILD)
        {
                printf("i was here l\n");
                rightchild->parent->left = rightchild;
        }
        else if(isRightChild(node) == IS_RIGHT_CHILD)
        {
                printf("i was here r\n");
                rightchild->parent->right = rightchild;
        }

        node->right = rightchild->left;
        rightchild->left = node;
        node->parent = rightchild;

        return node;
}


Node * deepcopy( Node * node )
{
        Node * copy = (Node *) malloc(sizeof(Node));
        #define COPY(field) \
                if ( node->field != NULL ) \
                { \
                        copy->field = node->field; \
                } \
                else \
                { \
                        copy->field = NULL; \
                }
        COPY(parent)
        COPY(left)
        COPY(right)
        copy->data = node->data;
        return copy;
}

/**
 *  rotate right the given node
 *  @param tree: the current node
 */
Node * rotateRight( Node * node )
{
        Node * leftchild= node->left;

        leftchild->parent = node->parent;

        if (isLeftChild(node) == IS_LEFT_CHILD)
        {
                printf("i was here l\n");
                leftchild->parent->left = leftchild;
        }
        else if(isRightChild(node) == IS_RIGHT_CHILD)
        {
                printf("i was here r\n");
                leftchild->parent->right = leftchild;
        }

        node->left = leftchild->right;
        leftchild->right = node;
        node->parent = leftchild;

        return node;

}

/**
 *  balances RBTree, assuming that the subtree of given node is
 *  allrady balanced.
 *  @param tree: the current node
 */
void balancRBTree( Node * node )
{
        if ( node )
        {
                Node * ancestor;
                Node * parent;
                switch ( getState(node) )
                {
                case CASE1_ROOT:
                        node->color = BLACK;
                        return;
                case CASE2_PARENT_BLACK:
                        return;
                case CASE3_PARENT_AND_UNCLE_RED:
                        ancestor = node->parent->parent;
                        parent = node->parent;
                        ancestor->left->color = BLACK;
                        ancestor->right->color = BLACK;
                        ancestor->color = RED;
                        balancRBTree(ancestor);
                        return;
                case CASE4_PARENT_RED:
                        printf("i was in case 4\n");
                        ancestor = node->parent->parent;
                        parent = node->parent;
                        if ( isLeftChild(node) == IS_LEFT_CHILD &&
                             isRightChild(parent) == IS_RIGHT_CHILD)
                        {
                                rotateLeft(ancestor);
                        }
                        else if ( isRightChild(node) == IS_RIGHT_CHILD &&
                             isLeftChild(parent) == IS_LEFT_CHILD )

                        {
                                rotateRight(ancestor);
                        }
                        else if ( isLeftChild(node) == IS_LEFT_CHILD &&
                             isLeftChild(parent) == IS_LEFT_CHILD)
                        {
                                rotateRight(ancestor);
                        }
                        else if ( isRightChild(node) == IS_RIGHT_CHILD &&
                             isRightChild(parent) == IS_RIGHT_CHILD)
                        {
                                rotateLeft(ancestor);
                        }

                        parent->color = BLACK;
                        ancestor->color = RED;
                        balancRBTree(ancestor);
                        return;
                }
        }

}


/**
 * searching a node that holdes the given value
 * @param tree, the current node.
 * @param data, which we search.
 */
Node *getNode( Node *node, void *data, CompareFunc compFunc )
{

        if ( node->data == LEAF )
        {
                return node;
        }

        switch (compFunc(data, node->data) )
        {
        case LE:
                return getNode( node->left, data, compFunc );
        case EQ:
                return node;
        case GE:
                return getNode( node->right, data, compFunc );
        }
        return NULL;
}

/**
 * searching a node that holdes the given value from the root
 * of the tree
 * @param tree, the current node.
 * @param data, which we search.
 */
Node *getNodeByRoot( RBTree *root, void *data )
{
        return getNode(root->root, data, root->compFunc);
}

/**
 * constructs a new Node and settig his parent
 * and his color.
 * @param parent: the parent of the leaf.
 */
Node * newLeaf(Node ** parent)
{
        Node * ret = (Node * )malloc( sizeof(Node) );
        ret->data = LEAF;
        ret->parent = *parent;
        ret->left =NULL;
        ret->right=NULL;
        ret->color=BLACK;
        return ret;
}

/**
 * constructs a new RBTree with the given CompareFunc.
 * comp: a function two compare two variables.
 */
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
        RBTree * ret = (RBTree * ) malloc( sizeof(RBTree) );
        ret->root = newLeaf(&(ret->root));
        ret->root->parent = NULL;
        ret->compFunc = compFunc;
        ret->freeFunc = freeFunc;
        ret->size = EMPTY_TREE_SIZE;
        return ret;
}

/**
 * add an item to the tree
 * @param tree: the tree to add an item to.
 * @param data: item to add to the tree.
 * @return: 0 on failure, other on success. (if the item is already in the tree - failure).
 */
int addToRBTree(RBTree *tree, void *data)
{
        Node * position = getNodeByRoot(tree, data);
        if ( position->data == LEAF)
        {
                position->data = data;
                position->left = newLeaf(&position);
                position->right = newLeaf(&position);
                position->color = RED;
                balancRBTree(position);
                tree->size += ADD_ELEMENT;

                while( tree->root->parent != NULL )
                {
                        tree->root = tree->root->parent;
                }

                return SUCCES_ADD;
        }
        return FAIL_ADD;
}

/**
 * check whether the tree contains this item.
 * @param tree: the tree to add an item to.
 * @param data: item to check.
 * @return: 0 if the item is not in the tree, other if it is.
 */
int containsRBTree(RBTree *tree, void *data)
{
        return tree == NULL || (getNodeByRoot(tree, data)->data != LEAF);
}




/**
 * Activate a function on each item of the tree. the order is an ascending order. if one of the activations of the
 * function returns 0, the process stops.
 * @param מםגק: the current node.
 * @param func: the function to activate on all items.
 * @param args: more optional arguments to the function (may be null if the given function support it).
 * @return: 0 on failure, other on success.
 */
int forEachDFS(Node *node, forEachFunc func, void *args)
{
        if ( node->data == LEAF )
        {
                return SUCCES_FOR_EACH;
        }
        int ret =
                (forEachDFS(node->left, func, args) == SUCCES_FOR_EACH) &&
                (func( node->data, args ) == SUCCES_FOR_EACH) &&
                (forEachDFS(node->right, func, args) == SUCCES_FOR_EACH);
        return ret;
}


/**
 * Activate a function on each item of the tree. the order is an ascending order. if one of the activations of the
 * function returns 0, the process stops.
 * @param tree: the tree with all the items.
 * @param func: the function to activate on all items.
 * @param args: more optional arguments to the function (may be null if the given function support it).
 * @return: 0 on failure, other on success.
 */
int forEachRBTree(RBTree *tree, forEachFunc func, void *args)
{
        return forEachDFS(tree->root, func, args);
}


/**
 * free all memory in the subtree of node
 * @param tree: the current node.
 */
void freeDFS(Node ** node, FreeFunc freeFunc)
{
        if ( (*node)->data == LEAF )
        {
                free((*node));
        }
        else
        {
                freeDFS(&(*node)->left, freeFunc);
                freeDFS(&(*node)->right, freeFunc);
                free((*node));
        }
}

/**
 * free all memory of the data structure.
 * @param tree: the tree to free.
 */
void freeRBTree(RBTree *tree)
{
        freeDFS(&tree->root, tree->freeFunc);
        free(tree);
}


int getHeight(Node * node)
{
        if ( node->data == LEAF )
        {
                return 0;
        }

        int leftheight =  getHeight(node->left);
        int righttheight = getHeight(node->right);
        int ret = leftheight;
        if( leftheight < righttheight )
                ret = righttheight;

        printf("i was here : %d\n", ret);
        return 1 + ret;
}
