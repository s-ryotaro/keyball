// key_hold_macros.h

#ifndef KEY_HOLD_MACROS_H
#define KEY_HOLD_MACROS_H

#include "quantum.h"  // 必要に応じて、QMKの標準ヘッダファイルをインクルードする

#define KC_LEFT_HOLD_TIME 50
#define KC_RIGHT_HOLD_TIME 50
#define KC_UP_HOLD_TIME 50
#define KC_DOWN_HOLD_TIME 50

/* auto_click_layer.hでも定義しているのでこちらをコメントアウト
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_LEFT:
                register_code(KC_LEFT);
                wait_ms(KC_LEFT_HOLD_TIME);
                unregister_code(KC_LEFT);
                break;
            case KC_RIGHT:
                register_code(KC_RIGHT);
                wait_ms(KC_RIGHT_HOLD_TIME);
                unregister_code(KC_RIGHT);
                break;
            case KC_UP:
                register_code(KC_UP);
                wait_ms(KC_UP_HOLD_TIME);
                unregister_code(KC_UP);
                break;
            case KC_DOWN:
                register_code(KC_DOWN);
                wait_ms(KC_DOWN_HOLD_TIME);
                unregister_code(KC_DOWN);
                break;
            default:
                // 他のキーに対する処理が必要な場合はここに追加する
                return true;
        }
    }
    return true;
}

*/

#endif // KEY_HOLD_MACROS_H
