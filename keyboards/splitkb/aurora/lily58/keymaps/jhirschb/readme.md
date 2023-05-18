_This keymap is a copy of the [Lily58 default keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/lily58/keymaps/default), with slight modifications._

I'm running this code on a Liatris Microcontroller, it might, or might not run on controllers with less memory. Feel free to leave feedback. 

# How to show conways game of life on your OLED display

Add the files _conway.c_ and _conway.h to your keymap folder and add the line 

    SRC += conway.c 

to your rules.mk file.


Include conway.h in your keymap.c file and call the method from your code like this:

    #include "conway.h" 

    bool process_record_user(uint16_t keycode, keyrecord_t *record) 
    {
        if (record->event.pressed) {
            if(is_keyboard_master()) {
                conway_gol(keycode);
            }
        }
        return true;
    }

Now build your firmware as usual.

# Using the state machine 

The idea is to generate a random seed while typing and then calculate a number of states until the reset key is hit. 

Initially the machine is in seeding state where any keystroke will set a cell alive in a 12x12 cell area in the center of the display.
Exceptions are the keycodes KC_SPC which will add a single dead cell and KC_TAB which adds 12 dead cells.

Once the seeding area is full, or KS_ENTER is hit, any keystroke will calculate and display the next state.

Except KC_BSPC which will reset the machine.

Enjoy!
