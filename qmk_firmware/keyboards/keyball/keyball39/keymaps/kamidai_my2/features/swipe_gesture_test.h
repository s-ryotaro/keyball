/* Copyright 2023 kamidai (@d_kamiichi)
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------
 *
 * 参考文献：
 * - 以下のリソースを参考にしました：
 *   https://www.reddit.com/r/ploopy/comments/pbmrh3/qmk_options_on_ploopy_mouse_gestures/
 *   https://github.com/RobertCurry0216/qmk_firmware/blob/59f83aac8fa06010c3a1a0a53fcd453d96ce2f80/keyboards/ploopyco/trackball/keymaps/robertcurry0216/keymap.c
 *
 */

int16_t current_keycode;
const int16_t SWIPE_THRESHOLD = 5;
bool is_swiped = false;
bool is_repeat = false;

// スワイプジェスチャーで何が起こるかを処理する関数です
// 上、下、左、右の4つのオプションがあります
void process_swipe_gesture(int16_t x, int16_t y) {
  // Alt
  if (current_keycode == KC_1) {
    //unregister_code(KC_LALT);

    // 拡大と縮小
    if (my_abs(x) < my_abs(y)) {
      tap_code(KC_A);

      if (y < 0) {
        // swipe up: 拡大
        tap_code(KC_B);
      } else {
        // swipe down: 縮小
        tap_code(KC_C);
      }
    }
  }
}