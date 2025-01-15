#include <stdio.h>
#include <stdbool.h>

#define NUM_OF_BOARDS 5
#define ROWS 8
#define COLS 8

#define SUBMARINE 'S'
#define EMPTY '~'
#define HIDDEN ' '

#define CHAR_A 65
#define CHAR_H 72
#define CHAR_0 48
#define CHAR_7 55

// global variables
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

int n_moves = 0;
int n_submarines = 0;
char display_board[ROWS][COLS];
char game_board[ROWS][COLS];
int user_row_idx;
int user_col_idx;


// Function Declarations
void clear_scanf_buffer();
int get_column_idx(char user_col);
void print_welcome_message();
int select_game_board();
void check_row_or_col(char chosen_row, char chosen_col);
void print_error_position_already_bombed();
void print_winning_message();
void printMatrix(const char matrix[ROWS][COLS]);
void set_game_board(int board_num);
void set_display_board();
void get_user_move();
void check_and_update_submarine(int shift_row_idx, int shift_col_idx);
void update_display_board_when_submarine_found();
void game_logic();
bool check_keep_game();
int main(void);


// Function Implementations
void clear_scanf_buffer(){
     while (getchar() != '\n');
}

int get_column_idx(char user_col){
    return (user_col - 'A');
}

void print_welcome_message() {
    printf("Welcome to Battleship!!!\n");
}

int select_game_board(){
    int board_num = 3;
    bool answer_ok = false;
    while(!answer_ok){
        printf("Please enter board number [1-5]: ");
        int result = scanf("%d", &board_num);
        clear_scanf_buffer();
        if(result == 0){
            printf("Error in input. You should enter a number [1-5]. Please, try again\n");
            continue;
        }

        if (board_num >= 1 && board_num <= 5) {
            answer_ok = true;
        }
        else{
            printf("Error in board number, try again\n"); 
        }
    }
    printf("Thank you for selecting board number %d \n", board_num);
    return board_num;
}

void check_row_or_col(char chosen_row, char chosen_col) {
    while (chosen_row < CHAR_0 || chosen_row > CHAR_7 ||
        chosen_col < CHAR_A || chosen_col > CHAR_H){
        printf("Error in row or column - out of bound\n");
        scanf("%c %c", &chosen_row, &chosen_col);
        }
    //need to add function if the pos has already been chosen before
}

void print_error_position_already_bombed() {
    printf("This position was already bombed - try again!\n");
}

void print_winning_message() {
    printf("Congratulations, Admiral!\nYou've successfully "
           "revealed all %d submarines in %d moves!\n", n_submarines, n_moves);
}

// Print a ROWSxCOLS matrix
void printMatrix(const char matrix[ROWS][COLS]) {
    // Print column headers
    printf("\n");
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

void set_game_board(int board_num){
    const char (*p_board)[COLS];
    switch(board_num){
        case 1:
        p_board = MATRIX_1;
        break;
        case 2:
        p_board = MATRIX_2;
        break;
        case 3:
        p_board = MATRIX_3;
        break;
        case 4:
        p_board = MATRIX_4;
        break;
        case 5:
        p_board = MATRIX_5;
        break;
     }
    for(int row_idx=0; row_idx<ROWS; row_idx++){
        for(int col_idx=0; col_idx<COLS; col_idx++){
            game_board[row_idx][col_idx] = p_board[row_idx][col_idx];
        }
    }
}

void set_display_board(){
    for(int row_idx=0; row_idx<ROWS; row_idx++){
        for(int col_idx=0; col_idx<COLS; col_idx++){
            display_board[row_idx][col_idx] = HIDDEN;
        }
    }
}

void get_user_move(){
    int result;
    char user_col_char;
    printf("Please enter position, for example D4:\n");
    result = scanf("%c%d", &user_col_char, &user_row_idx);
    clear_scanf_buffer();
    user_col_idx = get_column_idx(user_col_char);
}

void check_and_update_submarine(int shift_row_idx, int shift_col_idx){
    int row_idx = user_row_idx;
    int col_idx = user_col_idx;
    while(true){
        if(row_idx<0) break;
        if(row_idx>ROWS) break;
        if(col_idx<0) break;
        if(col_idx>COLS) break;
        if(game_board[row_idx][col_idx] != SUBMARINE) break;

        display_board[row_idx][col_idx] = SUBMARINE;

        row_idx += shift_row_idx;
        col_idx += shift_col_idx;
    }
}

void update_display_board_when_submarine_found(){
    check_and_update_submarine(1, 0);
    check_and_update_submarine(-1, 0);
    check_and_update_submarine(0, 1);
    check_and_update_submarine(0, -1);
}

void game_logic(){
    n_moves++;
    char sign = game_board[user_row_idx][user_col_idx];
    display_board[user_row_idx][user_col_idx] = sign;
    if(sign == SUBMARINE){
        n_submarines++;
        update_display_board_when_submarine_found();
    }    
}

bool check_keep_game(){
    for(int i=0; i<ROWS;i++){
        for(int j=0; j<COLS; j++){
            if(
                (game_board[i][j] == SUBMARINE) && (display_board[i][j] != SUBMARINE)
                ){
                return true;
            } 
        }
    }
    return false;

}

int main(void) {
    print_welcome_message();
    int board_num = select_game_board();
    set_game_board(board_num);
//    printMatrix(game_board);

    set_display_board(display_board);

    while(check_keep_game()){
        printMatrix(display_board);
        printf("Moves: %d, Submarines: %d\n", n_moves, n_submarines);
        get_user_move();
        game_logic();
    }
    printMatrix(display_board);
    print_winning_message();
    return(0);
}
