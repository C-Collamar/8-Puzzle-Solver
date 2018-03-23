//external variables declared from main.c
extern unsigned int nodesExpanded; 
extern unsigned int nodesGenerated;
extern unsigned int solutionLength;
extern double runtime;             

/**
 * DESCRIPTION: This displays the '8-Puzzle Solver' ASCII art to the screen
**/
void welcomeUser(void) {
    //style from: http://patorjk.com/software/taag/#p=display&f=Standard&t=8-Puzzle%20Solver
    printf("\n\
   ___        ____                _        ____        _\n\
  ( _ )      |  _ \\ _   _ _______| | ___  / ___|  ___ | |_   _____ _ __\n\
  / _ \\ _____| |_) | | | |_  /_  / |/ _ \\ \\___ \\ / _ \\| \\ \\ / / _ \\ '__|\n\
 | (_) |_____|  __/| |_| |/ / / /| |  __/  ___) | (_) | |\\ V /  __/ |\n\
  \\___/      |_|    \\__,_/___/___|_|\\___| |____/ \\___/|_| \\_/ \\___|_|\n");
}

/**
 * DESCRIPTION: This displays the input instructions for the user to read
**/
void printInstructions(void) {
    printf(
        "------------------------------------------------------------------------\n"
        "Instructions:\n"
        "    Enter the initial and goal state of the 8-puzzle board. Input\n"
        "    either integers 0-8, 0 representing the space character, to assign\n"
        "    symbols toeach board[row][col].\n"
        "------------------------------------------------------------------------\n"
    );
}

/**
 * DESCRIPTION:
 *    This function fills `state` with non-repeating numbers from 0 to 9
**/
void inputState(State * const state) {
    state->action = NOT_APPLICABLE;
    char row, col;
    int symbol;

    // flags for input validation
    char isNumUsed[9] = { 0 };

    for(row = 0; row < 3; ++row) {
        for(col = 0; col < 3; ++col) {
            printf("    board[%i][%i]: ", row, col);

            // to prevent scanning newline from the input stream
            scanf("%i", &symbol);

            // check if input is a blank character or is a number greater than 0 and less than 9
            if(symbol >= 0 && symbol < 9) {
                // check if input is repeated
                if(!isNumUsed[symbol]) {
                    state->board[row][col] = symbol + '0';
                    isNumUsed[symbol] = 1;
                }
                else {
                    printf("    ERROR: Number %c is already used. Try again with different input.\n", symbol);
                    --col;
                }
            }
            else {
                printf("    ERROR: Invalid input. Enter a number from 0 to 8.\n");
                --col;
            }
        }
    }
    printf("\n");
}

/**
 * DESCRIPTION: This displays contents of `board` to the standard output
**/
void printBoard(char const board[][3]) {
    char row, col;

    for(row = 0; row < 3; ++row) {
        printf("+---+---+---+\n");
        for(col = 0; col < 3; ++col) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }
    printf("+---+---+---+\n");
}

/**
 * DESCRIPTION:
 *    This function interprets numerical instructions of the move to make,
 *    to it's verbal counterpart to be displayed to the screen.
 * PARAMETER:
 *    solution - the solution path consisting a list of nodes from the root
 *               to the goal
**/
void printSolution(struct SolutionPath *path) {
	//check if solution exists
    if(!path) {
        printf("No solution found.\n");
        return;
    }

	//if the initial state is already the goal state
	if(!path->next) {
		printf("No moves needed. The initial state is already the goal state.\n");
		return;
	}

    printf("SOLUTION: (Relative to the space character)\n");

    //will use hash map to speed up the proccess a bit
    char *move[4] = { "UP", "DOWN", "LEFT", "RIGHT" };
    int counter = 1;

    //will be skipping the first node since it represents the initial state with no action
    for(path = path->next; path; path = path->next, ++counter) {
        printf("%i. Move %s\n", counter, move[path->action]);
    }

    printf(
        "DETAILS:\n"
        " - Solution length : %i\n"
        " - Nodes expanded  : %i\n"
        " - Nodes generated : %i\n"
        " - Runtime         : %g milliseconds\n"
        " - Memory used     : %i bytes\n", //only counting allocated `Node`s
        solutionLength, nodesExpanded, nodesGenerated, runtime, nodesGenerated * sizeof(Node));
}
