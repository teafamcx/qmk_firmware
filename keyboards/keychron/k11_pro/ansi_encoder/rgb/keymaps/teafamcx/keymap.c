/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "keymap_japanese.h"

// clang-format off
enum layers{
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    FN2,
};

/// Windowsキーコードマッピング変更
/// GRV -> JP版キーコード
/// EQL -> JP版...
/// [] -> JP...
/// バックスラッシュ -> 円
/// ' -> JP...
/// Win -> Alt
/// LALT -> 無変換
/// RALT -> 変換
/// Light -> Win
/// 右スペース -> エンター
/// FN1 + SPC -> BKSP
/// FN2 + SPC -> DEL
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_HOME,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_END,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPTN, KC_LCMMD,          KC_SPC,           MO(MAC_FN1), MO(FN2),       KC_SPC,            KC_RCMMD,           KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_69_ansi(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  JP_EQL,   KC_BSPC,          KC_LGUI,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     JP_LBRC,  JP_RBRC,  JP_YEN,           KC_HOME,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  JP_QUOT,  KC_ENT,           KC_END,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT,  MO(WIN_FN1),       KC_SPC,           JP_MHEN,  JP_HENK,          KC_ENT,            MO(FN2),            KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN1] = LAYOUT_69_ansi(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          _______,
        _______, BT_HST1,  BT_HST2,  BT_HST3, _______, _______, _______,  _______, _______, _______, _______,  KC_INS,   KC_PGUP,  _______,          _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,           _______, _______, _______, KC_SNAP,  KC_PGDN,  KC_END,   _______,          _______,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, KC_PGUP,
        _______, _______,  _______,           KC_BSPC,          JP_PLUS,  KC_MINS,          KC_BSPC,           _______,            _______, KC_PGDN, _______),

    [WIN_FN1] = LAYOUT_69_ansi(
        JP_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FILE, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          _______,
        _______, BT_HST1,  BT_HST2,  BT_HST3, _______, _______, _______,  _______, _______, KC_APP,  KC_SCRL,  KC_INS,   KC_PGUP,  _______,          _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,           _______, _______, _______, KC_PSCR,  KC_PGDN,  KC_END,   _______,          _______,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, KC_PGUP,
        _______, _______,  _______,           KC_BSPC,          JP_PLUS,  KC_MINS,          KC_BSPC,           _______,            _______, KC_PGDN, _______),

    [FN2] = LAYOUT_69_ansi(
        JP_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL,           _______,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, BAT_LVL,  BAT_LVL, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           KC_DEL ,          KC_EQL ,  JP_UNDS,          KC_DEL ,           _______,            _______, _______, _______)
};

/// SHIFT + ` -> ~
//const key_override_t kor_jp_tild = ko_make_basic(MOD_MASK_SHIFT, JP_GRV, JP_TILD);
/// SHIFT + 2 -> @
const key_override_t kor_jp_at = ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT);
/// SHIFT + 6 -> JP_CIRC
const key_override_t kor_jp_circ = ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC);
/// SHIFT + 7 -> &
const key_override_t kor_jp_ampr = ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR);
/// SHIFT + 8 -> *
const key_override_t kor_jp_astr = ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR);
/// SHIFT + 9 -> (
const key_override_t kor_jp_lprn = ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN);
/// SHIFT + 0 -> )
const key_override_t kor_jp_rprn = ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN);
/// SHIFT + MINUS:- -> _
const key_override_t kor_jp_unds = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, JP_UNDS);
/// SHIFT + EQUAL:= -> PLUS:+
const key_override_t kor_jp_plus = ko_make_basic(MOD_MASK_SHIFT, JP_EQL, JP_PLUS);
/// SHIFT + \ -> |
const key_override_t kor_jp_pipe = ko_make_basic(MOD_MASK_SHIFT, JP_YEN, JP_PIPE);
/// SHIFT + ; -> :
const key_override_t kor_jp_coln = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN);
/// SHIFT + ' -> "
const key_override_t kor_jp_dquo = ko_make_basic(MOD_MASK_SHIFT, JP_QUOT, JP_DQUO);

const key_override_t **key_overrides = (const key_override_t *[]){
//    &kor_jp_tild,
    &kor_jp_at,
    &kor_jp_circ,
    &kor_jp_ampr,
    &kor_jp_astr,
    &kor_jp_lprn,
    &kor_jp_rprn,
    &kor_jp_unds,
    &kor_jp_plus,
    &kor_jp_pipe,
    &kor_jp_coln,
    &kor_jp_dquo,
    NULL // オーバーライドの配列は Null で終了します！
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [FN2]      = { ENCODER_CCW_CW(_______, _______)},
};
#endif // ENCODER_MAP_ENABLE
