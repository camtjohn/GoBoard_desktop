#include <iostream>
using namespace std;

#define BOARD_SIZE 3

class TicTacToe {
public:
    int score_x = 0;
    int score_o = 0;
    char board[BOARD_SIZE][BOARD_SIZE];
    int layout[BOARD_SIZE][BOARD_SIZE];
    int position = 1;
    char current_move = 'x';
    int count_move = 0;

    TicTacToe() {

        // Assign layout position numbers
        for (int i_row = 0; i_row<BOARD_SIZE; i_row++) {
                for (int i_col = 0; i_col<BOARD_SIZE; i_col++) {
                    layout[i_row][i_col] = position;
                    position++;
                }
        }

    }

    void print_layout() {
        position = 1;
        for (int i_row = 0; i_row<BOARD_SIZE; i_row++) {
                for (int i_col = 0; i_col<BOARD_SIZE; i_col++) {
                    cout << layout[i_row][i_col] << ' ';
                }
                std::cout << '\n';
        }
    }

    void new_game() {
        std::cout << "\nNew game. Board cleared.\n";
        // Clear board
        for (int i_row = 0; i_row<BOARD_SIZE; i_row++) {
                for (int i_col = 0; i_col<BOARD_SIZE; i_col++) {
                    board[i_row][i_col] = '_';
                }
        }
        // Reset counter
        count_move = 0;
    }

    void prompt_new_move() {
        // Print board, Print layout, Print prompt
        std::cout << "Board:\n";
        for (int i_row = 0; i_row<BOARD_SIZE; i_row++) {
                for (int i_col = 0; i_col<BOARD_SIZE; i_col++) {
                    std::cout << board[i_row][i_col] << ' ';
                }
                std::cout << '\n';
        }
        std::cout << '\n';
        print_layout();
        std::cout << "\nTurn: " << current_move << "\nWhere do you go?\n";
    }

    void winner_chicken_dinner() {
        std::cout << "\n\nWINNER!!! " << current_move << '\n';
        if (current_move == 'x') {
            score_x++;
        } else {score_o++;}
        std::cout << "Score: X=" << score_x << " O=" << score_o;
        std::cout << "\n\n";
    }

    void new_move(int position) {
        int var_new_game;
        std::cout << '\n';
        if ((position<1) || (position>9)) {
            std::cout << "Invalid selection. Try again.";
            return;
        }
        // Top row
        if (position < 4) {
            // Check if position is already occupied
            if (board[0][position-1] == '_') {
                board[0][position-1] = current_move;
                count_move++;
            } else {
                std::cout << "Space occupied. Try Again.";
                return;
            }
        // Bottom Row
        } else if (position > 6) {
            // Check if position is already occupied
            if (board[2][position-7] == '_') {
                board[2][position-7] = current_move;
                count_move++;
            } else {
                std::cout << "Space occupied. Try Again.";
                return;
            }
        // Middle row
        } else {
            // Check if position is already occupied
            if (board[1][position-4] == '_') {
                board[1][position-4] = current_move;
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
        // Check for full board
        } if (count_move==9) {
            std::cout << "\n\nDraw!\n";
            return 1;
        } else {return 0;}
    }

};


int main() {
    TicTacToe game;

    int i = 0;
    int position;
    game.new_game();

    //Prompt for move. New move->
    while (i<99) {
        game.prompt_new_move();
        std::cin >> position;
        game.new_move(position);
        std::cout << "\n\n\n\n\n\n";

        i++;
    }

}
