#include <stdio.h>
#include <stdbool.h>

#define ROWS 8
#define COLS 8
#define NUM_OF_BOARDS 5
#define SUBMARINE 'S'
#define EMPTY '~'
#define HIDDEN ' '

// Function Declarations
int print_welcome_message();

void check_board_number(int board_num);

char* choose_board(int chosen_n);

int print_enter_position();

void check_row_or_col();

void print_error_position_already_bombed();

int make_a_move(int board[ROWS][COLS], int chosen_row, int chosen_col, int num_of_sub);

void print_winning_message(int n_submarines, int n_moves);

void printMatrix(char matrix[ROWS][COLS]);


// Optional Boards

const char MATRIX_1[ROWS][COLS] = {
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', 'S', '~', '~', '~', 'S', '~'},
    {'~', '~', 'S', '~', '~', '~', 'S', '~'},
    {'~', '~', 'S', '~', '~', '~', 'S', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'S', '~', '~', 'S', '~', '~', '~', '~'},
    {'S', '~', '~', 'S', '~', '~', '~', '~'},
    {'S', '~', '~', 'S', '~', '~', '~', '~'}
};
const char MATRIX_2[ROWS][COLS] = {
    {'S', '~', '~', '~', '~', '~', '~', '~'},
    {'S', '~', 'S', '~', '~', '~', '~', '~'},
    {'S', '~', 'S', '~', '~', '~', '~', '~'},
    {'~', '~', 'S', '~', '~', '~', '~', 'S'},
    {'~', '~', '~', '~', '~', '~', '~', 'S'},
    {'~', '~', '~', '~', '~', '~', '~', 'S'},
    {'~', 'S', 'S', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'}
};
const char MATRIX_3[ROWS][COLS] = {
    {'~', 'S', 'S', 'S', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', 'S', 'S', 'S'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', 'S', 'S', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', 'S', 'S', 'S', 'S', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'S', '~', '~', '~', '~', '~', '~', '~'}
};
const char MATRIX_4[ROWS][COLS] = {
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'}
};
const char MATRIX_5[ROWS][COLS] = {
    {'S', '~', 'S', '~', '~', '~', '~', 'S'},
    {'~', '~', '~', '~', '~', 'S', '~', '~'},
    {'~', '~', 'S', '~', '~', '~', '~', '~'},
    {'~', '~', '~', '~', '~', '~', 'S', '~'},
    {'~', '~', '~', 'S', '~', '~', '~', '~'},
    {'~', 'S', '~', '~', '~', '~', 'S', '~'},
    {'~', '~', '~', '~', '~', '~', '~', '~'},
    {'S', '~', '~', 'S', '~', '~', '~', 'S'}
};


int print_welcome_message() {
    int board_num = 0;
    printf("Welcome to Battleship! Please enter board number:\n");

    while (board_num < 1 || board_num > 5) {
        printf("Error in board number, try again\n");
        scanf("%d", &board_num);
    }
    return(board_num);
}

char* choose_board(int chosen_n) {
    char* all_boards[5] = {&MATRIX_1[0][0], &MATRIX_2[0][0], &MATRIX_3[0][0], &MATRIX_4[0][0], &MATRIX_5[0][0]};
    return(all_boards[chosen_n -1]);
}

int print_enter_position(char *p_board) {
    char chosen_col = 0;
    char chosen_row = 0;
    int num_of_sub = 0;
    printf("Please enter position:\n");
    scanf("%d %d", &chosen_row, &chosen_col);
    check_row_or_col(chosen_row, chosen_col);
    print_error_position_already_bombed();

    make_a_move(board, chosen_row, chosen_col, num_of_sub);
    return(num_of_sub);
}

void check_row_or_col(char chosen_row, char chosen_col) {
    while (chosen_row < 48 || chosen_row > 55 ||
        chosen_col < 65 || chosen_col > 72){
        printf("Error in row or column - out of bound\n");
        scanf("%d %d", &chosen_row, &chosen_col);
        }
    //need to add function if the pos has already been chosen before
}


int make_a_move(char *p_board ,char *p_current_board, int chosen_row, int chosen_col) {
    char *p_bombed = p_board[chosen_row][chosen_col];

    if(*p_bombed == SUBMARINE) {
        p_current_board[chosen_row][chosen_col] = SUBMARINE;

        //needs to check if its still in the board limits
        int i = 1;
        while(p_board[chosen_row + i][chosen_col] == SUBMARINE) {
            p_current_board[chosen_row + i][chosen_col] = SUBMARINE;
            i++;
        }
        i = 1;
        while(p_board[chosen_row - i][chosen_col] == SUBMARINE) {
            p_current_board[chosen_row - i][chosen_col] = SUBMARINE;
            i++;
        }
        i = 1;
        while(p_board[chosen_row][chosen_col + i] == SUBMARINE) {
            p_current_board[chosen_row][chosen_col+ i] = SUBMARINE;
            i++;
        }
        i = 1;
        while(p_board[chosen_row][chosen_col - i] == SUBMARINE) {
            p_current_board[chosen_row][chosen_col - i] = SUBMARINE;
            i++;
        }
        return (1);
    }else {
        p_current_board[chosen_row][chosen_col] = EMPTY;
        return(0);
    }
}


void print_error_position_already_bombed() {
    printf("This position was already bombed - try again!\n");
}

void print_winning_message(int n_submarines, int n_moves) {
    printf("Congratulations, Admiral!\nYou've successfully "
           "revealed all %d submarines in %d moves!\n", n_submarines, n_moves);
}

// Print a ROWSxCOLS matrix
void printMatrix(char matrix[ROWS][COLS]) {
    // Print column headers
    printf("  ");
    for (int j = 0; j < COLS; j++) {
        printf(" %c", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        // Print row label
        printf("%d ", i);

        // Print row
        for (int j = 0; j < COLS; j++) {
            // Each cell is in "|x|" format
            printf("|%c", matrix[i][j]);
        }
        printf("|\n");
    }
}


int main(void) {
    char board[ROWS][COLS] = {EMPTY};
    int n_submarines = 0, n_moves = 0;
    bool still_playing = true;

    int chosen_board = print_welcome_message();
    char *p_board = choose_board(chosen_board);


    while(still_playing) {
        printMatrix(board);
        n_submarines += print_enter_position(p_board);
        n_moves++;
        if(n_submarines == 4) {
            still_playing = false;
        }
    }

    print_winning_message(n_submarines, n_moves);
    return 0;
}