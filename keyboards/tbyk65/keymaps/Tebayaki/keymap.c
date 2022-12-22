#include "tbyk65.h"

#define CS(kc) C(S(kc))
#define CA(kc) C(A(kc))
#define SA(kc) S(A(kc))
#define GC(kc) G(C(kc))
#define CSA(kc) C(S(A(kc)))
#define KC_LB KC_MS_BTN1
#define KC_RB KC_MS_BTN2
#define KC_MB KC_MS_BTN3

#define IS_MOD_ON(mods) ((get_mods() & MOD_BIT(mods)) == MOD_BIT(mods))

enum my_keycodes{
    FN_3 = SAFE_RANGE,
    KC_MS_SCRL
};

keyboard_state_t keyboard_state = {0, 0};
bool is_scrolling = false;

/*
    LAYOUT(
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO
    )
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV       , KC_1         , KC_2         ,  KC_3        , KC_4         , KC_5         , KC_6         , KC_7         , KC_8         , KC_9         , KC_0         , KC_MINS      , KC_EQL       , KC_BSPC      ,
        KC_DEL       , KC_Q         , KC_W         ,  KC_E        , KC_R         , KC_T         , KC_Y         , KC_U         , KC_I         , KC_O         , KC_P         , KC_LBRC      , KC_RBRC      , KC_BSLS      ,
        KC_TAB       , KC_A         , KC_S         ,  KC_D        , KC_F         , KC_G         , KC_H         , KC_J         , KC_K         , KC_L         , KC_SCLN      , KC_QUOT      , KC_ENT       ,
        KC_LSFT      , KC_Z         , KC_X         ,  KC_C        , KC_V         , KC_B         , KC_N         , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH      , KC_RSFT      ,
        KC_LCTL      , LT(2, KC_ESC), KC_LGUI      ,  KC_LALT     , KC_LCTL      , MO(1)        , KC_SPC       , KC_RGUI      , KC_NO        , FN_3         , KC_RCTL      , KC_ESC
    ),
    [1] = LAYOUT(
        KC_NO        , KC_F1        , KC_F2        , KC_F3        , KC_F4        , KC_F5        , KC_F6        , KC_F7        , KC_F8        , KC_F9        , KC_F10       , KC_F11       , KC_F12       , KC_DEL       ,
        KC_NO        , CSA(KC_Q)    , CSA(KC_W)    , CSA(KC_E)    , CSA(KC_R)    , CSA(KC_T)    , KC_HOME      , C(KC_LEFT)   , C(KC_RGHT)   , KC_END       , KC_PGUP      , KC_NO        , KC_NO        , KC_NO        ,
        A(KC_F4)     , KC_TAB       , CSA(KC_S)    , CS(KC_TAB)   , C(KC_TAB)    , CSA(KC_G)    , KC_LEFT      , KC_DOWN      , KC_UP        , KC_RGHT      , KC_PGDN      , KC_NO        , KC_NO        ,
        KC_TRNS      , GC(KC_LEFT)  , A(KC_UP)     , A(KC_LEFT)   , A(KC_RGHT)   , GC(KC_RGHT)  , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_TRNS      ,
        KC_TRNS      , KC_NO        , KC_TRNS      , KC_TRNS      , KC_TRNS      , KC_NO        , KC_NO        , KC_TRNS      , KC_NO        , KC_NO        , KC_TRNS      , RESET
    ),
    [2] = LAYOUT(
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_BSPC      ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_PERC      , KC_7         , KC_8         , KC_9         , KC_ASTR      , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_MB        , KC_LB        , KC_RB        , KC_PLUS      , KC_4         , KC_5         , KC_6         , KC_DOT       , KC_EQL       , KC_ENT       ,
        KC_TRNS      , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_MINS      , KC_1         , KC_2         , KC_3         , KC_SLSH      , KC_NO        ,
        KC_TRNS      , KC_NO        , KC_TRNS      , KC_TRNS      , KC_TRNS      , KC_MS_SCRL   , KC_0         , KC_TRNS      , KC_NO        , KC_NO        , KC_TRNS      , DEBUG
    ),
    [3] = LAYOUT(
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        ,
        KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO        , KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    static uint16_t press_time = 0;
    static uint8_t last_scancode = 0;

    bool res = true;

    // 获取按下的键位
    // uint8_t this_scancode = record->event.key.row << 4 | record->event.key.col;
    uint8_t this_scancode = (MATRIX_COLS * record->event.key.row + record->event.key.col);
    // 更新键盘状态
    if (record->event.pressed) {
        this_scancode < 64 ? (keyboard_state.part1 |= 1ULL << this_scancode) : (keyboard_state.part2 |= 1ULL << (this_scancode & 63));
    } else {
        this_scancode < 64 ? (keyboard_state.part1 &= ~(1ULL << this_scancode)) : (keyboard_state.part2 &= ~(1ULL << (this_scancode & 63)));

        if (IS_LAYER_ON(1) && !keyboard_state.part1 && !keyboard_state.part2) {
            layer_off(1);
        }
    }

    switch (keycode) {
        case FN_3:
            if (record->event.pressed) {
                press_time = record->event.time;
                layer_on(3);
            }
            else {
                layer_off(3);
                if (timer_elapsed(press_time) < TAPPING_TERM && this_scancode == last_scancode) {
                    tap_code(KC_RCTL);
                    tap_code16(CS(KC_SPC));
                }
            }
            res = false;
            break;
        case KC_TAB:
            if (record->event.pressed) {
                if (IS_LAYER_ON(1) && !IS_MOD_ON(KC_RALT)) {
                    register_mods(MOD_BIT(KC_RALT));
                }
            }
            break;
        case MO(1):
            if (record->event.pressed) {
            }
            else {
                if (keyboard_state.part1 || keyboard_state.part2) {
                    res = false;
                }
                if (IS_MOD_ON(KC_RALT)) {
                    unregister_mods(MOD_BIT(KC_RALT));
                }
            }
            break;
        // tap caps if left shift is held
        case KC_RSHIFT:
            if (record->event.pressed) {
                if (IS_MOD_ON(KC_LSFT)) {
                    tap_code(KC_CAPS);
                }
            }
            break;
        case KC_MS_SCRL:
            if (record->event.pressed) {
                is_scrolling = true;
            }
            else {
                is_scrolling = false;
            }
            res = false;
            break;
    }

    last_scancode = this_scancode;
    return res;
}

void ps2_mouse_moved_user (report_mouse_t *mouse_report){
    static uint16_t last_sample_time = 0;
    uint16_t interval = timer_elapsed (last_sample_time);

    if (is_scrolling){
        if (interval > 50){
            last_sample_time = timer_read ();
            mouse_report->v = mouse_report->y > 2 ? -1 : mouse_report->y < -2 ? 1 : 0;
            mouse_report->h = mouse_report->x > 2 ? 1 : mouse_report->x < -2 ? -1 : 0;
        }
        mouse_report->x = mouse_report->y = 0;
    }
}