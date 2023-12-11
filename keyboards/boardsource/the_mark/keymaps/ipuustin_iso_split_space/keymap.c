/* Copyright 2022 Boardsource
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

extern rgblight_config_t rgblight_config;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Split spacebar with mute key (shift-ctrl-M) in the middle.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_iso_split_bs_space(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_PGUP,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGDN,
        KC_CAPS_LOCK,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_DEL,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,          KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           RCS(KC_M),        KC_SPC,           KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT_iso_split_bs_space(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_HOME,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU,          KC_END,
        QK_BOOT,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,          _______,          _______,          _______,          _______, _______, _______, _______, _______, _______
    )
};

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_fn_layer
);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    return state;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    // set default color to off; otherwise it's red
    rgblight_sethsv_noeeprom(HSV_OFF);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
