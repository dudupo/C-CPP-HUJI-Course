#include ".h"



/**
 *  rotate left the given node
 *  @param tree: the current node
 */
void rotateLeft( RBTree * tree )
{

}

/**
 *  rotate right the given node
 *  @param tree: the current node
 */
void rotateRight( RBTree * tree )
{

}

/**
 *  balances RBTree, assuming that the subtree of given node is
 *  allrady balanced.
 *  @param tree: the current node
 */
void balancRBTree( RBTree * tree )
{
        if ( tree )
        {
                if ( trees->perent &&
                     trees->perent->Color == RED )
                {
                        balancRBTree(trees->perent);
                }
        }
}


/**
 * searching a node that holdes the given value
 * @param tree, the current node.
 * @param data, which we search.
 */
RBTree *getNode(RBTree *tree, void *data)
{
        if ( !tree )
        {
                return tree;
        }

        RBTree * ret;
        return ret;
}


/**
 * constructs a new RBTree with the given CompareFunc.
 * comp: a function two compare two variables.
 */
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
        RBTree * ret;
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
        return 0;
}

/**
 * check whether the tree contains this item.
 * @param tree: the tree to add an item to.
 * @param data: item to check.
 * @return: 0 if the item is not in the tree, other if it is.
 */
int containsRBTree(RBTree *tree, void *data)
{
        return 0;
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
        return 0;
}

/**
 * free all memory of the data structure.
 * @param tree: the tree to free.
 */
void freeRBTree(RBTree *tree)
{

}
