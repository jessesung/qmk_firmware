/* Copyright 2020 imchipwood
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  Bkspc  |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |   Esc   |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |   Tab   |
    |-------------|---------|---------|---------|---------|
    | Left mouse  |  TT(1)  |    0    |    .    |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_7,      KC_8,    KC_9,             KC_BSPC,
                    KC_4,      KC_5,    KC_6,             KC_ESC,
                    KC_1,      KC_2,    KC_3,             KC_TAB,
        KC_BTN1,    TT(1),     KC_0,    LSFT_T(KC_DOT),   KC_ENTER
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    +    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    -    |
    |-------------|---------|---------|---------|---------|
    |    LOCK     |         |         |         |    =    |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    _______,     _______,     _______,      RESET,
                    _______,     _______,     _______,      KC_KP_PLUS,
                    _______,     _______,     _______,      KC_KP_MINUS,
        KC_LOCK,    _______,     _______,     _______,      KC_EQL
    ),
};

#if defined(ENCODER_MAP_ENABLE)
#define NUM_ENCODERS 1
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =   { ENCODER_CCW_CW(KC_BRMD, KC_BRMU)  },
    [2] =   { ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [3] =   { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
/*
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
*/
    return true;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
}
