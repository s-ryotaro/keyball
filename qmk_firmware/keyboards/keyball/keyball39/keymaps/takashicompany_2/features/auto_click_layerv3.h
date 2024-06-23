// ヘッダーガード
#ifndef FEATURES_AUTO_CLICK_LAYERV3_H
#define FEATURES_AUTO_CLICK_LAYERV3_H

#include "quantum.h"

// カスタムキーコードの定義
enum custom_keycodes {
    CUSTOM_A = SAFE_RANGE,
    KC_MY_BTN1,
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_SCR,
    KC_TO_CLICKABLE_INC,
    KC_TO_CLICKABLE_DEC,
    KC_SCROLL_DIR_V,
    KC_SCROLL_DIR_H,
};

// クリック状態の列挙型
enum click_state {
    NONE = 0,
    WAITING,    // マウスレイヤーが有効になるのを待つ。
    CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる。
    CLICKING,   // クリック中。
    SCROLLING   // スクロール中。
};

// ユーザー設定の構造体
typedef union {
    uint32_t raw;
    struct {
        int16_t to_clickable_movement;
        bool mouse_scroll_v_reverse;
        bool mouse_scroll_h_reverse;
    };
} user_config_t;

// グローバル変数
extern user_config_t user_config;
extern enum click_state state;
extern uint16_t click_timer;
extern uint32_t to_reset_time;  // uint32_tに変更
extern int16_t scroll_v_mouse_interval_counter;
extern int16_t scroll_h_mouse_interval_counter;
extern int16_t scroll_v_threshold;
extern int16_t scroll_h_threshold;
extern int16_t after_click_lock_movement;
extern int16_t mouse_record_threshold;
extern int16_t mouse_move_count_ratio;
extern const uint16_t ignore_disable_mouse_layer_keys[];

// プロトタイプ宣言
int8_t clip2int8(int16_t x);
void eeconfig_init_user(void);
void keyboard_post_init_user(void);
void enable_click_layer(void);
void disable_click_layer(void);
int16_t my_abs(int16_t num);
bool is_clickable_mode(void);
void auto_click(void);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);

// クリッピング関数
inline int8_t clip2int8(int16_t x) {
    if (x > 127) {
        return 127;
    }
    if (x < -128) {
        return -128;
    }
    return (int8_t)x;
}

// 初期化関数
void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.to_clickable_movement = 50;
    user_config.mouse_scroll_v_reverse = false;
    user_config.mouse_scroll_h_reverse = false;
    eeconfig_update_user(user_config.raw);
}

// キーボード初期化後の処理
void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

// マウスレイヤーの有効化
void enable_click_layer(void) {
    layer_on(click_layer);
    click_timer = timer_read();
    state = CLICKABLE;
}

// マウスレイヤーの無効化
void disable_click_layer(void) {
    state = NONE;
    layer_off(click_layer);
    scroll_v_mouse_interval_counter = 0;
    scroll_h_mouse_interval_counter = 0;
}

// 絶対値計算関数
int16_t my_abs(int16_t num) {
    return num < 0 ? -num : num;
}

// クリックモードかどうかの判定関数
bool is_clickable_mode(void) {
    return state == CLICKABLE || state == CLICKING || state == SCROLLING;
}

// カスタムキーの処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t custom_hold_timer;

    switch (keycode) {
        // 以下省略
    }

    return true;
}

// ポインティングデバイスのタスク処理
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int16_t current_x = mouse_report.x;
    int16_t current_y = mouse_report.y;
    int16_t current_h = 0;
    int16_t current_v = 0;

    if (current_x || current_y) {
        switch (state) {
            case CLICKABLE:
                click_timer = timer_read();
                break;

            case CLICKING:
                after_click_lock_movement -= my_abs(current_x) + my_abs(current_y);

                if (after_click_lock_movement > 0) {
                    current_x = 0;
                    current_y = 0;
                }

                break;

            case SCROLLING:
                // スクロールの処理
                break;

            case WAITING:
                // 待機状態の処理
                break;

            default:
                break;
        }
    } else {
        // マウスが動かない場合の処理
    }

    mouse_report.x = current_x;
    mouse_report.y = current_y;
    mouse_report.h = current_h;
    mouse_report.v = current_v;

    return mouse_report;
}

#endif // FEATURES_AUTO_CLICK_LAYERV3_H
