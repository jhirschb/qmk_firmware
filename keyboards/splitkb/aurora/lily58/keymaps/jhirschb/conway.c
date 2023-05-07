#include QMK_KEYBOARD_H
#include "conway.h"

bool current_gen[HEIGHT][WIDTH];
bool next_gen[HEIGHT][WIDTH];
bool seeding = true; 
const short seed_startpos_h = HEIGHT / 2 - SEED_HEIGHT / 2;
const short seed_startpos_w = WIDTH / 2 - SEED_WIDTH / 2;
short seed_offset = 0;


void render_grid(void) 
{
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
             oled_write_pixel(i, j, current_gen[i][j]);
        }
    }
}
int count_neighbours(int row, int col) 
{
    int count = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = (row + i + HEIGHT) % HEIGHT;
            int c = (col + j + WIDTH) % WIDTH;
            if(current_gen[r][c]) count++;
        }
    }
    return count;
}

void update_state(void) 
{
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            int neighbours = count_neighbours(i, j);
            if(current_gen[i][j]) {
                next_gen[i][j] = !(neighbours < 2 || neighbours > 3);
            } else {
                next_gen[i][j] = (neighbours == 3);
            }
        }
    }

    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            current_gen[i][j] = next_gen[i][j];
        }
    }
}

void start_state_machine(void)
{
    seeding = false;
}

void reset_state_machine(void) 
{
    seeding = true;
    seed_offset = 0;
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            current_gen[i][j] = false;
        }
    }
}

void add_seed(uint16_t keycode)
{
    int row = seed_startpos_h + seed_offset / SEED_HEIGHT;
    int col = seed_startpos_w + seed_offset % SEED_WIDTH;
    switch(keycode) {
        case SPACE:
            seed_offset++;  
            break;
        case ROWSPACE:
            seed_offset += SEED_WIDTH;
            break;
        default:
            current_gen[row][col] = true;
            seed_offset++;
    }

    if(seed_offset > SEED_WIDTH * SEED_HEIGHT - 1) {
        seeding = false;
        seed_offset = 0;
    }
}

void conway_gol(uint16_t keycode)
{
    switch (keycode) {
        case START:
            start_state_machine();
            break;
        case RESET:
            reset_state_machine();
            break;
        default:
            if(seeding) {
                add_seed(keycode);
            } else {
                update_state();
            }
    }
    render_grid();
}
