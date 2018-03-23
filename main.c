/**
 * Authors:
 *  - Angelo Dina
 *  - Christian Collamar
**/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "state.h"
#include "list.h"
#include "node.h"
#include "io.h"

unsigned int nodesExpanded;  //number of expanded nodes
unsigned int nodesGenerated; //number of generated nodes
unsigned int solutionLength; //number of moves in solution
double runtime;              //elapsed time (in milliseconds)

SolutionPath* BFS_search(State *, State *);
SolutionPath* AStar_search(State *, State *);

int main(void) {
    welcomeUser();           //display welcome message
    printInstructions();     //display instructions

    State initial;           //initial board state
    State goalState;         //goal board configuration
    
    //solution path of each search method
    SolutionPath *bfs;
    SolutionPath *aStar;

    //input initial board state
    printf("INITIAL STATE:\n");
    inputState(&initial);

    //input the goal state
    printf("\nGOAL STATE:\n");
    inputState(&goalState);

    printf("INITIAL BOARD STATE:\n");
    printBoard(initial.board);

    printf("GOAL BOARD STATE:\n");
    printBoard(goalState.board);

    //perform A* search
    aStar = AStar_search(&initial, &goalState);
    printf("\n-------------------------- USING A* ALGORITHM --------------------------\n");
    printSolution(aStar);

    //reset the counters
    nodesExpanded = 0;
    nodesGenerated = 0;
    solutionLength = 0;
    runtime = 0;

    //perform breadth-first search
    bfs = BFS_search(&initial, &goalState);
    printf("\n------------------------- USING BFS ALGORITHM --------------------------\n");
    printSolution(bfs);

    //free resources
    destroySolution(&bfs);
    destroySolution(&aStar);

    return 0;
}

/**
 * DESCRIPTION:
 *    Our breadth-first search implemetation.
 * PARAMETERS:
 *    initial - address to the initial state
 *    goal    - address to the goal state
 * RETURN:
 *    Returns the solution in a linked list; NULL if the solution is not found.
**/
SolutionPath* BFS_search(State *initial, State *goal) {
    NodeList *queue = NULL;
    NodeList *children = NULL;
    Node *node = NULL;

    //start timer
    clock_t start = clock();

    //initialize the queue with the root node of the search tree
    pushNode(createNode(0, manhattanDist(initial, goal), initial, NULL), &queue);
    Node *root = queue->head->currNode; //for deallocating the generated tree

    //while there is a node in the queue to expand
    while(queue->nodeCount > 0) {
        //pop the last node (tail) of the queue
        node = popNode(&queue);

        //if the state of the node is the goal state
        if(statesMatch(node->state, goal))
            break;

        //else, expand the node and update the expanded-nodes counter
        children = getChildren(node, goal);
        ++nodesExpanded;

        //add the node's children to the queue
        pushList(&children, queue);
    }

    //determine the time elapsed
    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;

    //get solution path in order from the root, if it exists
    SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

    while(node) {
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->state->action;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        //update the solution length and move on the next node
        ++solutionLength;
        node = node->parent;
    }

    --solutionLength; //uncount the root node

    //deallocate the generated tree
    destroyTree(root);

    return pathHead;
}

/**
 * DESCRIPTION:
 *    Our A* implemetation.
 * PARAMETERS:
 *    initial - address to the initial state
 *    goal    - address to the goal state
 * RETURN:
 *    Returns the solution in a linked list; NULL if the solution is not found.
**/
SolutionPath* AStar_search(State *initial, State *goal) {
    NodeList *queue = NULL;
    NodeList *children = NULL;
    Node *node = NULL;

    //start timer
    clock_t start = clock();

    //initialize the queue with the root node of the search tree
    pushNode(createNode(0, manhattanDist(initial, goal), initial, NULL), &queue);
    Node *root = queue->head->currNode; //for deallocating generated tree

    //while there is a node in the queue to expand
    while(queue->nodeCount > 0) {
        //pop the last node (tail) of the queue
        node = popNode(&queue);

        //if the state of the node is the goal state
        if(statesMatch(node->state, goal))
            break;

        //else, expand the node and update the expanded-nodes counter
        children = getChildren(node, goal);
        ++nodesExpanded;

        //add the node's children to the queue
        pushListInOrder(&children, queue);
    }

    //determine the time elapsed
    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;

    //get solution path in order from the root, if it exists
    SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

    while(node) {
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->state->action;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        //update the solution length and move on the next node
        ++solutionLength;
        node = node->parent;
    }

    --solutionLength; //uncount the root node

    //deallocate the generated tree
    destroyTree(root);

    return pathHead;
}