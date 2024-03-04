#include QMK_KEYBOARD_H

#include "quantum.h"

enum keyball39_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYMBOLS,
    LAYER_NAVNUM,
    LAYER_POINTER,
};

#define _LSFT_HALF_ROW(K00, K01, K02, K03, K04) LSFT(K00), LSFT(K01), LSFT(K02), LSFT(K03), LSFT(K04)
#define _TRANSPARENT_HALF_ROW_ _______, _______, _______, _______, _______
#define _TRANSPARENT_LEFT_LAST_ROW_ _______, _______, _______
#define _TRANSPARENT_RIGHT_LAST_ROW_ _______, _______, _______, _______
#define _TRANSPARENT_LEFT_THUMB_CLUSTER_ _______, _______, _______
#define _TRANSPARENT_RIGHT_THUMB_CLUSTER_ _______, _______
#define _MOUSE_RIGHT_HALF_ROW_ _______, KC_MS_BTN1, SCRL_MO, KC_MS_BTN3, KC_MS_BTN2

// Left-hand home row mods
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L LALT_T(KC_L)

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                                                         \
    KC_Q,    KC_W,     KC_E,     KC_R,     KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,            \
    KC_A,    ALT_S,    GUI_D,    CTL_F,    KC_G,                             KC_H,    CTL_J,    GUI_K,    ALT_L,    KC_SEMICOLON, \
    KC_Z,    KC_X,     KC_C,     KC_V,     KC_B,                             KC_N,    KC_M, KC_COMM,  KC_DOT,    KC_SLSH,         \
    _TRANSPARENT_LEFT_LAST_ROW_, OSM(MOD_LSFT), KC_SPACE, OSL(LAYER_SYMBOLS),     OSL(LAYER_NAVNUM), KC_ENTER, _TRANSPARENT_RIGHT_LAST_ROW_

/**
 * \brief Symbols layer.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                                                                                      \
    _______, _______, LSFT(KC_GRAVE), LSFT(KC_QUOTE), _______,                               _______, KC_QUOTE, KC_GRAVE, _______, _______,                       \
    _LSFT_HALF_ROW(KC_1, KC_2, KC_3, KC_4, KC_5),                                            _LSFT_HALF_ROW(KC_6, KC_7, KC_8, KC_9, KC_0),                        \
    _LSFT_HALF_ROW(KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_EQUAL, KC_MINUS, KC_BACKSLASH),     KC_BACKSLASH, KC_MINUS, KC_EQUAL, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, \
    _TRANSPARENT_LEFT_LAST_ROW_, _TRANSPARENT_LEFT_THUMB_CLUSTER_,                           _______, KC_ESCAPE, _TRANSPARENT_RIGHT_LAST_ROW_


/**
 * \brief Navigation and numeral layer.
 *
 * The left hand layer is the navigation layer.
 * The right hand layer is the numeral layer.
 */
#define LAYOUT_LAYER_NAVNUM                                                                                   \
    KC_DELETE, KC_HOME, KC_UP, KC_END, MEH(KC_T),                       _______, KC_7, KC_8, KC_9, MEH(KC_P), \
    KC_BACKSPACE, KC_LEFT, KC_DOWN, KC_RIGHT, _______,                  _______, KC_4, KC_5, KC_6, KC_0,      \
    _______, KC_PAGE_UP, _______, KC_PAGE_DOWN, _______,                _______, KC_1, KC_2, KC_3, KC_DOT,    \
    _TRANSPARENT_LEFT_LAST_ROW_, LCA(KC_TAB), KC_TAB, MEH(KC_SPACE),    _TRANSPARENT_RIGHT_THUMB_CLUSTER_, _TRANSPARENT_RIGHT_LAST_ROW_

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    _TRANSPARENT_HALF_ROW_,                                           _TRANSPARENT_HALF_ROW_, \
    _TRANSPARENT_HALF_ROW_,                                           _MOUSE_RIGHT_HALF_ROW_, \
    _TRANSPARENT_HALF_ROW_,                                           _TRANSPARENT_HALF_ROW_, \
    _TRANSPARENT_LEFT_LAST_ROW_, _TRANSPARENT_LEFT_THUMB_CLUSTER_,    _TRANSPARENT_RIGHT_THUMB_CLUSTER_, _TRANSPARENT_RIGHT_LAST_ROW_

#define LAYOUT_wrapper(...) LAYOUT_universal(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(LAYOUT_LAYER_BASE),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_NAVNUM] = LAYOUT_wrapper(LAYOUT_LAYER_NAVNUM),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
};
// clang-format on

void pointing_device_init_user(void) {
    set_auto_mouse_layer(LAYER_POINTER);
    set_auto_mouse_enable(true); // always required before the auto mouse feature will work
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable the scroll mode when the highest layer is not the pointer layer
    if (get_highest_layer(state) != LAYER_POINTER) {
        keyball_set_scroll_mode(false);
    }
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
