#ifndef CONWAY_H
#define CONWAY_H

#define SEED_WIDTH 12
#define SEED_HEIGHT 12

#define START KC_ENTER
#define RESET KC_BSPC
#define SPACE KC_SPC
#define ROWSPACE KC_TAB

#define WIDTH OLED_DISPLAY_WIDTH
#define HEIGHT OLED_DISPLAY_HEIGHT

void conway_gol(uint16_t keycode);

#endif // CONWAY_H
