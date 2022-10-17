/* Copyright 2021 James Sa
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

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define _LG(X) LGUI_T(X)
#define _LA(X) LALT_T(X)
#define _LC(X) LCTL_T(X)
#define _LS(X) LSFT_T(X)
#define _RG(X) RGUI_T(X)
#define _RA(X) RALT_T(X)
#define _RC(X) RCTL_T(X)
#define _RS(X) RSFT_T(X)

#define COPY C(KC_C)
#define PSTE C(KC_V)
#define CUT C(KC_X)
#define ZOOMIN C(KC_PLUS)
#define ZOOMOUT C(KC_PMNS)
#define ACTUAL C(KC_0)

enum my_layers {
    COLEMAK = 0,
    NUM,
    SYM,
    WM,
    FUNC,
    QWERTY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [COLEMAK] = LAYOUT(
             KC_Q,     KC_W,     KC_F,     KC_P, KC_B, KC_J,     KC_L,     KC_U,     KC_Y,  KC_SCLN,
        _LG(KC_A),_LA(KC_R),_LC(KC_S),_LS(KC_T), KC_G, KC_M,_LS(KC_N),_LC(KC_E),_LA(KC_I),_LG(KC_O),
             KC_Z,     KC_X,     KC_C,     KC_D, KC_V, KC_K,     KC_H,  KC_COMM,   KC_DOT,  KC_SLSH,
                           TG(QWERTY), LT(NUM,KC_SPC),LT(SYM,KC_BSPC), LT(WM,KC_ENT)
    ),
    [NUM] = LAYOUT(
        KC_ESC,  _______, _______,  KC_UNDS, KC_DQUO, KC_PLUS, KC_7,   KC_8,   KC_9,   KC_PERC,
        KC_TAB,  CUT,     COPY,      PSTE,   KC_QUOT,  KC_MINS, KC_4,   KC_5,   KC_6,   KC_ASTR,
        KC_CAPS,ZOOMIN, ZOOMOUT,   ACTUAL,  KC_EQL,  KC_DLR,  KC_1,   KC_2,   KC_3,   KC_SLSH,
                                     _______, XXXXXXX, KC_0,   KC_DOT
    ),
    [SYM] = LAYOUT(
        KC_CIRC, KC_GRV,  KC_TILD, KC_LCBR, KC_RCBR, _______,  KC_PGUP, KC_UP,   _______, _______,
        KC_EXLM, KC_AT,   KC_HASH, KC_LPRN, KC_RPRN, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        KC_BSLS, KC_AMPR, KC_PIPE, KC_LBRC, KC_RBRC, _______, KC_PGDN, _______, _______, _______,
                                   _LG(KC_INS), _LA(KC_DEL),  XXXXXXX, _______
    ),
    [WM] = LAYOUT(
        _______, G(KC_7), G(KC_8), G(KC_9), G(KC_MINS), _______, _______, G(KC_UP), _______, _______,
        KC_LSFT, G(KC_4), G(KC_5), G(KC_6), G(KC_0), _______, G(KC_LEFT), G(KC_DOWN), G(KC_RGHT), _______,
        _______, G(KC_1), G(KC_2), G(KC_3), _______, _______, _______, _______, _______, _______,
                                   KC_VOLD, KC_VOLU, _______, XXXXXXX
    ),
    [QWERTY] = LAYOUT(
             KC_Q,     KC_W,     KC_E,     KC_R, KC_T, KC_Y,     KC_U,     KC_I,     KC_O,  KC_P,
        _LG(KC_A),_LA(KC_S),_LC(KC_D),_LS(KC_F), KC_G, KC_H,_LS(KC_J),_LC(KC_K),_LA(KC_L),_LG(KC_SCLN),
             KC_Z,     KC_X,     KC_C,     KC_V, KC_B, KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,
                                  _______, KC_SPC,KC_BSPC, KC_ENT
    ),
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    //   debug_matrix=true;
    //   debug_keyboard=true;
    //   debug_mouse=true;
}

#ifdef OLED_ENABLE

bool    oled_needs_update = true;
bool    caps_lock         = false;
uint8_t layer             = 0;

// for caps lock
bool led_update_user(led_t led_state) {
    if (caps_lock == led_state.caps_lock) return true;
    dprint("caps lock changed\n");

    caps_lock         = led_state.caps_lock;
    oled_needs_update = true;
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // render layer indicator
    if (layer == get_highest_layer(state)) return state;
    dprint("layer changed\n");

    layer             = get_highest_layer(state);
    oled_needs_update = true;
    return state;
}

bool oled_task_user(void) {
    if (!oled_needs_update) return false;
    oled_needs_update = false;

    // render caps lock indicator
    if (caps_lock) {
        oled_write_P(PSTR("CAPS LOCK"), false);
    } else {
        oled_write_P(PSTR("PRAGMATIC"), false);
    }

    oled_set_cursor(0, 1);

    if (layer == 0) {
        oled_write_P(PSTR("-= 34 =-"), false);
    } else {
        char layer_indicator[] = "--------";
        layer_indicator[layer] = layer + 48; // ex. ---3---
        oled_write(layer_indicator, false);
        layer_indicator[layer] = '-'; // reset indicator
    }
    return false;
}

#endif // OLED_ENABLE
