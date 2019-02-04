#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
    #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum planck_layers {
    _NORM,
    _RAISE,
    _LOWER,
    //_III1,
    //_III2,
    _NAV,
    _RST
};

enum planck_keycodes {
    NORM = SAFE_RANGE,
    RAISE,
    LOWER,
    //III1,
    //III2,
    NAV,
    RST
};

// Tap Dance
enum{
    TD_PLUS_ASTR = 0,
    TD_MINS_SLSH = 1,
    TD_SCLN_QUOT = 2
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PLUS_ASTR] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_ASTR),
    [TD_MINS_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_SLSH),
    [TD_SCLN_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT)
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define PLUS_ASTR 0
#define MINS_SLSH 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
NORM
 ,-----------------------------------------------------------------------------------------------.
 |   ~   |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |       |
 |  ESC  |   q   |   w   |   e   |   r   |   t   |   y   |   u   |   i   |   o   |   p   | BKSP  |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   :   |       |
 |  TAB  |   a   |   s   |   d   |   f   |   g   |   h   |   j   |   k   |   l   |   ;   | ENTER |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |       |       |   ?   |       |
 | LSHFT |   z   |   x   |   c   |   v   |   b   |   n   |   m   |   ,   |   .   |   /   | RSHFT |
 |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 |       |   "   |       |       | LOWER |               | RAISE |       |       |       |       |
 | LCTRL |   '   |  GUI  | LALT  | (hold)|     SPACE     | (hold)| LEFT  | DOWN  |  UP   | RIGHT |
 `-----------------------------------------------------------------------------------------------'
                                  ^tap 3x to toggle       ^tap 3x to toggle
 */

[_NORM] = {
  {KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {KC_LCTL, KC_QUOT, KC_LGUI, KC_LALT, TT(_LOWER),KC_SPC,KC_SPC,  TT(_RAISE),KC_LEFT,KC_DOWN,KC_UP,   KC_RGHT}
},

/*
RAISE
 ,-----------------------------------------------------------------------------------------------.
 |   ~   |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   _   |   +   |   |   |
 |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   -   |   =   |   \   |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |       |       |   (   |   )   |   {   |   }   |   "   |
 |INSERT |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |   9   |   0   |   [   |   ]   |   '   |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |       |       |       |       |       |       |       |
 | LSHFT |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |   <   |   >   | HOME  | PGUP  | RSHFT |
 |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 |       |       |       |       |  NAV  |               | RAISE |       |       |       |       |
 | LCTRL |DELETE |  GUI  | LALT  | (tap) |     SPACE     | (hold)|       |  END  | PGDN  | RALT  |
 `-----------------------------------------------------------------------------------------------'

 */

[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_MINS, KC_EQL,  KC_BSLS},
  {KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_QUOT},
  {KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LABK, KC_RABK, KC_HOME, KC_PGUP, KC_RSFT},
  {KC_LCTL, KC_DEL,  KC_LGUI, KC_LALT, TO(_NAV),KC_SPC,  KC_SPC,  _______, XXXXXXX, KC_END,  KC_PGDN, KC_RALT}
},

/*
LOWER
 ,-----------------------------------------------------------------------------------------------.
 |       |       |       |       |       |       |       |       |       |       |       |       |
 | BKSP  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   =   | HOME  |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |   |   |   "   |   E   |   :   |   {   |   }   |       |       |       |       |       |
 |  TAB  |   \   |   '   |   e   |   ;   |   [   |   ]   |   4   |   5   |   6   | +(2*) | PGUP  |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |       |       |       |       |       |       |       |
 | LSHFT | LEFT  | DOWN  |  UP   | RIGHT |   (   |   )   |   1   |   2   |   3   | -(2/) | PGDN  |
 |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 |       |       |       |       | LOWER |               |   <   |       |   >   |       |       |
 | LCTRL | CAPS  |  GUI  | LALT  | (hold)|     SPACE     |   ,   |   0   |   .   | ENTER |  END  |
 `-----------------------------------------------------------------------------------------------'

 */

[_LOWER] = {
  {KC_BSPC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_EQL,  KC_HOME},
  {KC_TAB,  KC_BSLS, KC_QUOT, KC_E,    KC_SCLN, KC_LBRC, KC_RBRC, KC_4,    KC_5,KC_6,TD(TD_PLUS_ASTR),KC_PGUP},
  {KC_LSFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LPRN, KC_RPRN, KC_1,    KC_2,KC_3,TD(TD_MINS_SLSH),KC_PGDN},
  {KC_LCTL, KC_CAPS, KC_LGUI, KC_LALT, _______, KC_SPC,  KC_SPC,  KC_COMM, KC_0,    KC_DOT,  KC_ENT,  KC_END }
},

///*
//III1
// ,-----------------------------------------------------------------------------------------------.
// |       |       |       |       |       |       |       |       |       |       |       |  VOL  |
// |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |  UP   |
// |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
// | III2  |   A   |   S   |       |   F   |   T   |   Y   |   J   |   K   |   L   |       |  VOL  |
// | (tap) |   a   |   s   |       |   f   |   t   |   y   |   j   |   k   |   l   |       | DOWN  |
// |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
// |       |       |   X   |       |       |       |       |       |       |       |       |       |
// | LSHFT |       |   x   |       |       |       |       |       |       |   -   |   =   | RSHFT |
// |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
// |       | NORM  |       |       |       |               |       |       |       |       |       |
// | LCTRL | (tap) |  GUI  | LALT  |       |     SPACE     |       |       |   [   |   ]   | MUTE  |
// `-----------------------------------------------------------------------------------------------'
//
// */
//
//[_III1] = {
//  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU},
//  {TO(_III2),KC_A,   KC_S,    XXXXXXX, KC_F,    KC_T,    KC_Y,    KC_J,    KC_K,    KC_L,    XXXXXXX, KC_VOLD},
//  {KC_LSFT, XXXXXXX, KC_X,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_RSFT},
//  {KC_LCTL, TO(_NORM),KC_LGUI,KC_LALT, XXXXXXX, KC_SPC,  KC_SPC,  XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_MUTE}
//},
//
///*
//III2
// ,-----------------------------------------------------------------------------------------------.
// |       |       |       |       |       |       |       |       |       |       |       |  VOL  |
// |   `   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  UP   |
// |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
// | III1  |   A   |   S   |       |   F   |   T   |   Y   |   J   |   K   |   L   |       |  VOL  |
// | (tap) |   a   |   s   |       |   f   |   t   |   y   |   j   |   k   |   l   |       | DOWN  |
// |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
// |       |       |   X   |       |       |       |       |       |       |       |       |       |
// | LSHFT |       |   x   |       |       |       |       |       |       |   -   |   =   | RSHFT |
// |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
// |       | NORM  |       |       |       |               |       |       |       |       |       |
// | LCTRL | (tap) |  GUI  | LALT  |       |     SPACE     |       |       |   [   |   ]   | MUTE  |
// `-----------------------------------------------------------------------------------------------'
//
// */
//
//[_III2] = {
//  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______},
//  {TO(_III1),_______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
//  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
//  {_______, TO(_NORM),_______,_______, _______, _______, _______, _______, _______, _______, _______, _______}
//},

/*
NAV
 ,-----------------------------------------------------------------------------------------------.
 |       | RIGHT | MOUSE | LEFT  | SCROLL|       |       |       |       | SCROLL|       |       |
 |  ESC  | CLICK |  UP   | CLICK |  UP   |       |       |       | BTN4  |  UP   | BTN5  |       |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       | MOUSE | MOUSE | MOUSE | SCROLL|       |       | SCROLL| LEFT  |  MID  | RIGHT | SCROLL|
 | NORM  | LEFT  | DOWN  | RIGHT | DOWN  |       |       | LEFT  | CLICK | CLICK | CLICK | RIGHT |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       | SCROLL|  MID  | SCROLL|       |       |       |       |       | SCROLL|       |       |
 |       | LEFT  | CLICK | RIGHT |       |       |       | HOME  | PGUP  | DOWN  |  UP   |       |
 |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |               |       |       |       |       |       |
 |  RST  |       |       |       |       |               |  END  | PGDN  | LEFT  | DOWN  | RIGHT |
 `-----------------------------------------------------------------------------------------------'

 */

[_NAV] = {
  {KC_ESC,  KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN4, KC_WH_U, KC_BTN5, XXXXXXX},
  {TO(_NORM),KC_MS_L,KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, XXXXXXX, KC_WH_L, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_R},
  {XXXXXXX, KC_WH_L, KC_BTN3, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGUP, KC_WH_D, KC_UP,   XXXXXXX},
  {MO(_RST),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT}
},

/*
RST
 ,-----------------------------------------------------------------------------------------------.
 |       |       |       |       |       |       |       |       |       |       |       |       |
 |       |       |       |       |       |       |       |       |       |       |       | RESET |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |       |       |       |       |       |       |       |
 |       |       |       |       |       |       |       |       |       |       |       |       |
 |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |       |       |       |       |       |       |       |
 |       |       |       |       |       |       |       |       |       |       |       |       |
 |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 |       |       |       |       |       |               |       |       |       |       |       |
 |       |       |       |       |       |               |       |       |       |       |       |
 `-----------------------------------------------------------------------------------------------'

 */

[_RST] = {
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  },
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
}

};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MACRO_TAP(0),
    [1] = ACTION_MACRO_TAP(1),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt){
    switch(id){
        case 0:
            if(record->event.pressed){
                register_code(KC_LSFT);
                register_code(KC_8);
            }else{
                unregister_code(KC_8);
                unregister_code(KC_LSFT);

                if(record->tap.count && !record->tap.interrupted){
                    register_code(KC_LSFT);
                    register_code(KC_EQL);
                    unregister_code(KC_EQL);
                    unregister_code(KC_LSFT);
                }

                record->tap.count = 0;
            }
            break;
        case 1:
            if(record->event.pressed){
                register_code(KC_SLSH);
            }else{
                unregister_code(KC_SLSH);

                if(record->tap.count && !record->tap.interrupted){
                    register_code(KC_MINS);
                    unregister_code(KC_MINS);
                }
                record->tap.count = 0;
            }
            break;
    }
    return MACRO_NONE;
}

#ifdef AUDIO_ENABLE

float tone_startup[][2] = SONG(STARTUP_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

#endif

