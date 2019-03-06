/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

int x = 1;



// ----------Define LAYERS------------
enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST,
  _UTIL,
  _BRAIN,
  _PHOTO,
  _DOTA,
  CURR_LAYER = _DOTA
};

//Define TAP DANCE - KEYS
enum tap_dances {
  TD_EXQM_QUEST = 0,
  TD_DOT = 1,
  TD_COMMA = 2,
  TD_MINUS = 3
};


//All tap dance functions would go here. Only showing this one
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_EXQM_QUEST]  = ACTION_TAP_DANCE_DOUBLE(KC_QUES, KC_EXLM),
  [TD_DOT]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLN),
  [TD_COMMA]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCLN),
  [TD_MINUS]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS)
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  DOTA,
  LOWER,
  RAISE,
  BACKLIT,
  EXIT,
  HEART,
  PHOTO,
  SWAP_LAYER,
  M_BACK
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE LAYER
 *                                ,-----------------------------------------------------------------------------------.
 *                                | Tab  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 *                                |------+------+------+------+------+-------------+------+------+------+------+------|
 *     HOLD for UTIL layer -------| Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   "  |ENTER |------- HOLD for BRAIN layer
 *                                |------+------+------+------+------+------|------+------+------+------+------+------|
 *                                | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   !  |SHIFT |
 *                                |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | SLSH |  Up  | SWAP |
 *                                `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {LT(_UTIL, KC_ESC),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_DQUO, LT(_BRAIN, KC_ENTER)},
  {KC_LSFT, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    TD(TD_COMMA), TD(TD_DOT),  TD(TD_EXQM_QUEST), KC_RSFT},
  {KC_LCTL, KC_LGUI,  KC_LALT, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_SLSH, KC_UP,   SWAP_LAYER}
},
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   *  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_ASTR, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_PGUP, KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_PGDN, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______},
  {_______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  +   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   4  |   5  |   6  |   -  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   1  |   2  |   3  |   =  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_PLUS,      _______},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_4,    KC_5,    KC_6,    TD(TD_MINUS), _______},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_0,   KC_1,    KC_2,    KC_3,    KC_EQL,       _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    KC_VOLU,      KC_MPLY}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      | PHOTO| DOTA |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,     PHOTO,  DOTA, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* UTIL
 * ,-----------------------------------------------------------------------------------.
 * |      | PREV | PLAY | NEXT |      |      |      |      |  UP  |      |      | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | VOL- | Mute | VOL+ |      |      |      | LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |PRTSCR|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_UTIL] = {
  {_______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_TRNS,   KC_UP, XXXXXXX, _______,  KC_DEL},
  {_______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______},
  {_______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* BRAIN
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |   <  |  {   |   }  |   >  |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |   [  |  (   |   )  |   ]  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  "   |      |  =   |  '   |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_BRAIN] = {
  {_______, _______, _______, _______, KC_LABK, KC_LCBR, KC_RCBR, KC_RABK, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_DQUO, _______,  KC_EQL, KC_QUOT, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},


/* PHOTOSHOP
 * ,-----------------------------------------------------------------------------------.
 * |      |   I  |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |back  |  B   |  E   |  [   |  ]   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SHFT  |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ALT  |  R   |    SPACE    |   Z  |      |      |      | EXIT |
 * `-----------------------------------------------------------------------------------'
 */

[_PHOTO] = {
  {_______,    KC_I, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { M_BACK,    KC_B,    KC_E, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, KC_LALT,    KC_R,  KC_SPC,  KC_SPC,    KC_Z, _______, _______, _______,    EXIT}
},

/* DOTA
 *                                      ,-----------------------------------------------------------------------------------.
 * Press once for ^ twice for ESC ------|  ^   |   1  |   2  |      |   C  |      |      |      |      |      |      | HOME |
 *                                      |------+------+------+------+------+-------------+------+------+------+------+------|
 *                                      |  TAB |   Q  |   W  |   E  |   R  |   T  |   Z  |      |      |      |      |      |
 *                                      |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                      | SHIFT|   A  |   S  |   D  |   F  |      |      |      |      |      |      |      |
 *                                      |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                      | CTRL |      |      |      |      |    SPACE    |      |      |      |      / EXIT |
 *                                      `-----------------------------------------------------------------------------------'
 */

[_DOTA] = {
  {      KC_P,   KC_F1,   KC_F2,   KC_F3,    KC_C, _______, _______, _______, _______, _______, _______,    KC_F9},
  {    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z, _______, _______, _______, _______,  _______},
  {   KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F, _______, _______, _______, _______, _______, _______,  _______},
  {  KC_LCTRL, _______, _______,    KC_C, KC_LALT,  KC_SPC,  KC_SPC, _______, _______, _______, _______,     EXIT}
}

};

#ifdef AUDIO_ENABLE
  float querty_song[][2]      = SONG(QWERTY_SOUND);
  float photoshop_song[][2]   = SONG(VIOLIN_SOUND);
  float dota_song[][2]        = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]   = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case M_BACK:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("z")); // Control z
      }
      return false;
      break;

    //SWAP TO CURRENT SECONDARY LAYER
    case SWAP_LAYER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_gb_song);
          #endif
          layer_off(_RAISE);
          layer_off(_LOWER);
          layer_off(_ADJUST);
          if (x == 1) {PLAY_SONG(dota_song); layer_on(_DOTA);}
          else if (x == 2) {PLAY_SONG(photoshop_song); layer_on(_PHOTO);}
          if (!eeconfig_is_enabled()) {
            eeconfig_init();
          }
          keymap_config.raw = eeconfig_read_keymap();
          keymap_config.nkro = 1;
          eeconfig_update_keymap(keymap_config.raw);
        }
        return false;
        break;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case DOTA:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(dota_song);
        #endif
        x = 1;
      }
      return false;
      break;
    case PHOTO:
        if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(photoshop_song);
          #endif
          x = 2;
        }
        return false;
        break;
    case EXIT:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(querty_song);
        #endif
        if (x == 1) {layer_off(_DOTA);}
        else if (x == 2) {layer_off(_PHOTO);}
      }
      return false;
      break;
  }
  return true;
}
