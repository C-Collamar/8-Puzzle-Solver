extern unsigned int nodesGenerated; //declared from main.c

/**
 * DESCRIPTION: Defines the node structure used to create a search tree
**/
typedef struct Node Node;
struct Node {
    unsigned int depth; //depth of the node from the root. For A* search,
                        //this will also represent the node's path cost
    unsigned int hCost; //heuristic cost of the node
    State *state;       //state designated to a node
    Node *parent;       //parent node
    NodeList *children; //list of child nodes
};

/**
 * DESCRIPTION:
 *    This function creates a node, initializes it with the
 *    following parameters, and sets its children to NULL.
 * PARAMETERS:
 *    d - depth of the node
 *    h - heuristic value of the node
 *    s - state assignated to the node
 *    p - parent node
 * RETURN:
 *    Returns a `Node` pointer to the dynamically allocated node,
 *    or NULL on failure.
**/
Node* createNode(unsigned int d, unsigned int h, State *s, Node *p) {
    Node *newNode = malloc(sizeof(Node));
    if(newNode) {
        newNode->depth = d;
        newNode->hCost = h;
        newNode->state = s;
        newNode->parent = p;
        newNode->children = NULL;
        ++nodesGenerated; //update counter
    }
    return newNode;
}

/**
 * DESCRIPTION:
 *    This function is used to deallocate all nodes in a tree, including
 *    the root node.
 * PARAMETER:
 *    node - the root node of the tree to deallocate
**/
void destroyTree(Node *node) {
    if(node->children == NULL) {
        free(node->state);
        free(node);
        return;
    }

    ListNode *listNode = node->children->head;
    ListNode *nextNode;

    while(listNode) {
        nextNode = listNode->nextNode;
        destroyTree(listNode->currNode);
        listNode = nextNode;
    }

    //free(node->state);
    free(node->children);
    free(node);
}

/**
 * DESCRIPTION:
 *    This function 'expands' the node, links it to its children, and updates the
 *    expansion counter.
 * PARAMETER:
 *    parent    - the node to expand and search children for
 *    goalState - pointer to the goal state where heuristic values of each child will
 *                be based on
 * RETURN:
 *    Returns a pointer to `NodeList` on success, NULL on failure.
**/
NodeList* getChildren(Node *parent, State *goalState) {
    NodeList *childrenPtr = NULL;
    State *testState = NULL;
    Node *child = NULL;

    //attempt to create states for each moves, and add to the list of children if true
    if(parent->state->action != DOWN && (testState = createState(parent->state, UP))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }
    if(parent->state->action != UP && (testState = createState(parent->state, DOWN))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }
    if(parent->state->action != RIGHT && (testState = createState(parent->state, LEFT))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }
    if(parent->state->action != LEFT && (testState = createState(parent->state, RIGHT))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }

    return childrenPtr;
}

/**
 * DESCRIPTION:
 *    This simply evaluates the node's total cost, i.e. path cost + heuristic value.
 *    Created to abstract the proccess and reduce code cluttering. Note that
 *    a node's path cost in a tree depends purely on the node's depth, so the node's
 *    depth will be representing the path cost (to save space).
 * PARAMETER:
      node - the node to get its total cost
 * RETURN:
 *    Retuns the integer sum of the node's path cost and heuristic value
**/
int totalCost(Node * const node) {
    return node->depth + node->hCost;
}
