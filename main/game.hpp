#ifndef GAME_H
#define GAME_H

#ifdef __cplusplus
extern "C" {
#endif

	#define BOARD_SIZE 3

	struct grids_t {
	    int grid_x[BOARD_SIZE];
	    int grid_y[BOARD_SIZE];
	};

	void start_new_game();
	void print_board();
	void prompt_new_move();
	void place_new_move(int);
	struct grids_t get_grids();

#ifdef __cplusplus
}
#endif

#endif
