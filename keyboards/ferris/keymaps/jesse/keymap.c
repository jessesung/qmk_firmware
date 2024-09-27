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
#include "action_layer.h"
#include "keycodes.h"
#include "keymap_us.h"
#include QMK_KEYBOARD_H

#define _LG(X) LGUI_T(X)
#define _LA(X) LALT_T(X)
#define _LC(X) LCTL_T(X)
#define _LS(X) LSFT_T(X)
#define _RG(X) RGUI_T(X)
#define _RA(X) RALT_T(X)
#define _RC(X) RCTL_T(X)
#define _RS(X) RSFT_T(X)

enum {
    U_TD_BOOT,
};

static void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2)
        reset_keyboard();
}

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
};

enum custom_keycodes {
    IME = SAFE_RANGE,
};

const uint16_t PROGMEM ctrl_a_combo[] = {KC_D, KC_H, COMBO_END};
combo_t key_combos[] = {
    COMBO(ctrl_a_combo, LCTL(KC_A)),
};

enum my_layers {
    COLEMAK = 0,
    QWERTY,
    NAV,
    NUM,
    SYM,
    FUNC,
    TOTAL_LAYER_COUNT,
};

const char *layer_names[TOTAL_LAYER_COUNT] = {
    [COLEMAK] = "COLEMAK",
    [QWERTY]  = "QWERTY",
    [NAV]     = "NAV",
    [NUM]     = "NUM",
    [SYM]     = "SYMBOL",
    [FUNC]    = "FUNCTION",
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [COLEMAK] = LAYOUT(
        KC_Q, KC_W, KC_F, KC_P, KC_B,
            KC_J, KC_L, KC_U, KC_Y, KC_SCLN,
        _LG(KC_A), _LA(KC_R), _LC(KC_S), _LS(KC_T), KC_G,
            KC_M, _LS(KC_N), _LC(KC_E), _LA(KC_I), _LG(KC_O),
        KC_Z, KC_X, KC_C, KC_D, KC_V,
            KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,
        LT(NAV, KC_TAB), LT(NUM, KC_SPC), LT(SYM, KC_ENT), LT(FUNC, KC_BSPC)
    ),
    [QWERTY] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,
            KC_Y, KC_U, KC_I, KC_O, KC_P,
        _LG(KC_A), _LA(KC_S), _LC(KC_D), _LS(KC_F), KC_G,
            KC_H, _LS(KC_J), _LC(KC_K), _LA(KC_L), _LG(KC_SCLN),
        KC_Z, KC_X, KC_C, KC_V, KC_B,
            KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        _______, _______, _______, _______
    ),
    [NAV] = LAYOUT(
        KC_ESC, TG(QWERTY), IME, XXXXXXX, XXXXXXX,
            KC_INS, KC_PGUP, XXXXXXX, KC_HOME, XXXXXXX,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,
            XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
        CW_TOGG, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX,
            KC_DEL, KC_PGDN, XXXXXXX, KC_END, XXXXXXX,
        _______, _______, _______, _______
    ),
    [NUM] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, KC_7, KC_8, KC_9, KC_MINS,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,
            XXXXXXX, KC_4, KC_5, KC_6, KC_PLUS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            KC_SLSH, KC_1, KC_2, KC_3, KC_EQL,
        _______, _______, KC_0, KC_DOT
    ),
    [SYM] = LAYOUT(
        KC_LBRC, KC_AMPR, KC_ASTR, XXXXXXX, KC_RBRC,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_QUOT, KC_CIRC, KC_PERC, KC_DLR, XXXXXXX,
            XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_BSLS,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LPRN, KC_RPRN, _______, _______
    ),
    [FUNC] = LAYOUT(
        KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,
            KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, TD(U_TD_BOOT),
        KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL,
            KC_VOLD, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______
    ),
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    //   debug_matrix=true;
    //   debug_keyboard=true;
    //   debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case IME:
            if (record->event.pressed) {
                layer_invert(QWERTY);
                SEND_STRING(SS_LCTL(" "));
            }
            return false;
            break;
    }
    return true;
}

#ifdef OLED_ENABLE

bool    oled_needs_update = true;
bool    caps_lock         = false;
bool    caps_word         = false;
uint8_t layer             = 0;

// for caps lock
bool led_update_user(led_t led_state) {
    if ((caps_lock == led_state.caps_lock) &&
        (caps_word == is_caps_word_on()))
        return true;

    caps_lock         = led_state.caps_lock;
    caps_word         = is_caps_word_on();
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
    oled_clear();

    // render caps lock indicator
    if (caps_lock) {
        oled_write_P(PSTR("CAPS LOCK"), false);
    } else if (caps_word) {
        oled_write_P(PSTR("CAPS WORD"), false);
    } else {
        oled_write_P(PSTR("PRAGMATIC"), false);
    }

    oled_set_cursor(0, 1);

    const char *layer_name = layer_names[layer];
    if (layer_name)
        oled_write(layer_name, false);
    return false;
}

#endif // OLED_ENABLE
