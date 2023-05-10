#include <stdio.h>
#include "game.hpp"
#include "mqtt_client.c"

struct grids_t grids;

// Get input from standard input
int get_input(void) {
    int num_input = -1;
    int i = 0;
    while (i < 5) {
      // Get number from CLI
      scanf("%d", &num_input);
      // Clear input buffer
      while (getchar() != '\n');

      // Check for valid input
      if ((num_input >= 0) && (num_input < 10)) {
        return num_input;
      }

      printf("Invalid input. Try again.\nInput number (1-9): ");
      i++;
    }

    // Exit with invalid input
    return -1;
}


// Publish to mqtt broker: Request board
// After make move, publish to broker: new move

void main(void)
{
    int i = 0;
    int position;
    //int confirmation;
    start_new_game();

    int num_plays = 9;
    while (i < num_plays) {
        prompt_new_move();

        // Wait for input
	      position = get_input();
        // Given number of tries and input was bad every time
        if (position == -1) {
          printf("You fail at input");
          break;
        }

        printf("input= %d", position);

        place_new_move(position);

        // Get x and y grid from game module
        grids = get_grids();
        printf("grid_x: %d %d %d\n", grids.grid_x[0], grids.grid_x[1], grids.grid_x[2]);
        printf("grid_y: %d %d %d\n", grids.grid_y[0], grids.grid_y[1], grids.grid_y[2]);

        printf("\n\n");
        i++;
    }
    printf("\nDonezo\n");
}
