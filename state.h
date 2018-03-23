#define BLANK_CHARACTER '0'

//this enumerates available movements in the game relative to the blank character
typedef enum Move {
    UP, DOWN, LEFT, RIGHT, //values for moving up, down, left, right, respectively
    NOT_APPLICABLE         //value assigned for initial and goal input states
} Move;

typedef struct State {
    Move action;           //action that resulted to `this` board state
    char board[3][3];      //resulting board configuration after applying action
} State;

/**
 * DESCRIPTION:
 *    This creates a state if `move` is a valid move of the `state` board state.
 * PARAMETERS:
 *    state - pointer to the initial state
 *    move  - action to be applied to the given state
 * RETURN:
 *    Returns a pointer to a new `State` after the move is applied. Returns NULL
 *    upon failure.
**/
State* createState(State *state, Move move) {
    State *newState = malloc(sizeof(State));

    //copy the board configuration of `state` to `newState`
    //while searching for the row and column of the blank character
    char i, j;        //used for traversing the 3x3 arrays
    char row, col;    //coordinates of the blank character

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(state->board[i][j] == BLANK_CHARACTER) {
                row = i;
                col = j;
            }

            newState->board[i][j] = state->board[i][j];
        }
    }

    //test if the coordinates are valid after translation based on the move
    //if it is, swap the concerned board values to reflect the move
    if(move == UP && row - 1 >= 0) {
        char temp = newState->board[row - 1][col];
        newState->board[row - 1][col] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = UP;
        return newState;
    }
    else if(move == DOWN  && row + 1 < 3) {
        char temp = newState->board[row + 1][col];
        newState->board[row + 1][col] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = DOWN;
        return newState;
    }
    else if(move == LEFT  && col - 1 >= 0) {
        char temp = newState->board[row][col - 1];
        newState->board[row][col - 1] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = LEFT;
        return newState;
    }
    else if(move == RIGHT && col + 1 < 3) {
        char temp = newState->board[row][col + 1];
        newState->board[row][col + 1] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = RIGHT;
        return newState;
    }

    free(newState);
    return NULL;
}

/**
 * DESCRIPTION: This frees memory of `s` and is reassigned to NULL
**/
void destroyState(State **state) {
    free(*state);
    state = NULL;
}

/**
 * DESCRIPTION:
 *    A heuristic function that assigns h-cost to nodes. Lower values
 *    indicate the more closer to the goal.
 * PARAMETER:
 *    curr - the current board configuration
 *    goal - a pointer to the goal configuration of the board
 * RETURN:
 *    Returns a heuristic value greater than or equal to 0.
**/
int manhattanDist(State * const curr, State * const goal) {
    int x0, y0; //used for indexing each symbol in `curr`
    int x1, y1; //correspoinding row and column of symbol from curr[y0, x0] at `goal`
    int dx, dy; //change in x0 and x1, and y0 and y1, respectively
    int sum = 0;

    //for each symbol in `curr`
    for(y0 = 0; y0 < 3; ++y0) {
        for(x0 = 0; x0 < 3; ++x0) {
            //find the coordinates of the same symbol in `goal`
            for(y1 = 0; y1 < 3; ++y1) {
                for(x1 = 0; x1 < 3; ++x1) {
                    if(curr->board[y0][x0] == goal->board[y1][x1]) {
                        dx = (x0 - x1 < 0)? x1 - x0 : x0 - x1;
                        dy = (y0 - y1 < 0)? y1 - y0 : y0 - y1;
                        sum += dx + dy;
                    }
                }
            }
        }
    }

    return sum;
}

/**
 * DESCRIPTION:
 *    This checks whether the two given states match against each other. An alternative
 *    way is to check if the manhattan distance between these two states is zero, but it
 *    would take a more significant amount of time and computational resource
 * PARAMETERS:
 *    state1 - state to match against `state2`
 *    state2 - state to match against `state1`
 * RETURN:
 *    Returns 1 if states match, 0 otherwise.
**/
char statesMatch(State const *testState, State const *goalState) {
    char row = 3, col;

    while(row--) {
        col = 3;
        while(col--) {
            if(testState->board[row][col] != goalState->board[row][col])
                return 0;
        }
    }

    return 1;
}