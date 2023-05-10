#include <iostream>
#include "game.hpp"

using namespace std;


class TicTacToe {
public:
    int score_x = 0;
    int score_o = 0;
    char board[BOARD_SIZE][BOARD_SIZE];
    int position = 1;
    char current_move = 'x';
    int count_move = 0;
    struct grids_t grids;

    TicTacToe() {
        // Constructor fns go here
        // Board/Position numbers:
        // 0 1 2
        // 3 4 5
        // 6 7 8
    }

    // Two 3 element arrays of numbers 0-7 each represent rows of grid
    // eg. 0 1 0 = 2, 1 1 0 => 6
    // Both grids start [0 0 0]. Input position, add appropriate amt to row
    void update_grid(int position) {
        int value = 4;  // 100
        int row = 0;    // Default to top row

        // Middle row
        if ((position >= BOARD_SIZE) && (position < (BOARD_SIZE*2)))  {
            position -= BOARD_SIZE;      // Reset back to 0, 1, 2
            row = 1;
        // Bottom row
        } else if (position >= (BOARD_SIZE*2)) {
            position -= (BOARD_SIZE*2);      // Reset back to 0,1,2
            row = 2;
        }

        // Calculate binary amount to add to column for that row
        value = value >> position;

        // Update appropriate grid
        if (current_move == 'x') {
            grids.grid_x[row] = grids.grid_x[row] + value;
        } else if (current_move == 'o') {
            grids.grid_y[row] = grids.grid_y[row] + value;
        }
    }

    void new_game() {
        std::cout << "\nNew game. Board cleared.\n\n";
        // Clear board
        for (int i_row = 0; i_row<BOARD_SIZE; i_row++) {
                for (int i_col = 0; i_col<BOARD_SIZE; i_col++) {
                    board[i_row][i_col] = '_';
                }
            grids.grid_x[i_row] = 0;
            grids.grid_y[i_row] = 0;
        }
        // Reset counter
        count_move = 0;
    }

    void print_board() {
        for (int i_row = 0; i_row<BOARD_SIZE; i_row++) {
                for (int i_col = 0; i_col<BOARD_SIZE; i_col++) {
                    std::cout << board[i_row][i_col] << ' ';
                }
                std::cout << '\n';
        }

    }

    void prompt_new_move() {
        // Print board, Print prompt
        std::cout << "Board:\n";
        print_board();
        std::cout << '\n';
        std::cout << "\nTurn: " << current_move << "\nWhere do you go?\n";
    }

    void winner_chicken_dinner() {
        std::cout << "WINNER!!! " << current_move << '\n';
        if (current_move == 'x') {
            score_x++;
        } else {score_o++;}
        std::cout << "Score: X=" << score_x << " O=" << score_o << "\n";
    }

    void new_move(int position) {
        int var_new_game;
        std::cout << '\n';
        // Position out of bounds (below 0 or above 8)
        if ((position < 0) || (position > 8)) {
            std::cout << "Invalid selection: " << position << ". Try again.";
            return;
        }
        // Top row
        if (position < 3) {
            // Check if position is already occupied
            if (board[0][position] == '_') {
                board[0][position] = current_move;
                update_grid(position);
                count_move++;
            } else {
                std::cout << "Space occupied. Try Again.";
                return;
            }
        // Bottom Row
        } else if (position > 5) {
            // Check if position is already occupied
            if (board[2][position-6] == '_') {
                board[2][position-6] = current_move;
                update_grid(position);
                count_move++;
            } else {
                std::cout << "Space occupied. Try Again.";
                return;
            }
        // Middle row
        } else {
            // Check if position is already occupied
            if (board[1][position-3] == '_') {
                board[1][position-3] = current_move;
                update_grid(position);
                count_move++;
            } else {
                std::cout << "Space occupied. Try Again.";
                return;
            }
        }
        var_new_game = check_board();
        if (var_new_game == 1) {
            new_game();
        } else {change_turn();}
    }

    void change_turn () {
        if (current_move == 'x') {
            current_move = 'o';
        } else {current_move = 'x';}
    }

    // Check after a move, did the last move by current_move win? Or fill board?
    // Returns 1 for start a new game
    int check_board() {
        // Check Middle position
        if (board[1][1] == current_move) {
            // Check Top Left, Bottom Right
            if ((board[0][0] == current_move) && (board[2][2] == current_move)) {
                winner_chicken_dinner();
                return 1;
            // Check Top Right, Bottom Left
            } else if ((board[0][2] == current_move) && (board[2][0] == current_move)) {
                winner_chicken_dinner();
                return 1;
            // Check Top Middle, Bottom Middle
            } else if ((board[0][1] == current_move) && (board[2][1] == current_move)) {
                winner_chicken_dinner();
                return 1;
            // Check Middle Left, Middle Right
            } else if ((board[1][0] == current_move) && (board[1][2] == current_move)) {
                winner_chicken_dinner();
                return 1;
            }
        }
        // Check Top Left
        if (board[0][0] == current_move) {
            // Check Top Middle, Top Right
            if ((board[0][1] == current_move) && (board[0][2] == current_move)) {
                winner_chicken_dinner();
                return 1;
            // Check Middle Left, Bottom Left
            } else if ((board[1][0] == current_move) && (board[2][0] == current_move)) {
                winner_chicken_dinner();
                return 1;
            }
        }
        // Check Bottom Right
        if (board[2][2] == current_move) {
            // Check Bottom Middle, Bottom Left
            if ((board[2][1] == current_move) && (board[2][0] == current_move)) {
                winner_chicken_dinner();
                return 1;
            // Check Middle Right, Top Right
            } else if ((board[1][2] == current_move) && (board[0][2] == current_move)) {
                winner_chicken_dinner();
                return 1;
            }
        // Check for full board/cats game
        } if (count_move==9) {
            std::cout << "\n\nDraw!\n";
            return 1;
	// None of the above apply
        } else {return 0;}
    }

};

TicTacToe game;

void start_new_game() {
	game.new_game();
}

void print_board() {
    game.print_board();
}

void prompt_new_move() {
	game.prompt_new_move();
}

void place_new_move(int pos) {
	game.new_move(pos);
}

struct grids_t get_grids() {
    return game.grids;
}

