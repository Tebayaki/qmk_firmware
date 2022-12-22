#include "think48.h"
#include "stdlib.h"

enum my_keycodes{
    CT_IME = SAFE_RANGE, // ime switch
    CT_AT, // alt-tab
    CT_L1,
    CT_L2,
    CT_L3,
    CT_L4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT (
    KC_MS_BTN1    , KC_Q,    KC_W,    KC_E,      KC_R,      KC_T,    KC_Y,     KC_U,      KC_I,      KC_O,     KC_P,      KC_BSPC,
    CT_L3        , KC_A,    KC_S,    KC_D,      KC_F,      KC_G,    KC_H,     KC_J,      KC_K,      KC_L,      CT_L1,    KC_ENT,
    KC_LSPO       , KC_Z,    KC_X,    KC_C,      KC_V,      KC_B,    KC_N,     KC_M,      KC_COMM,   KC_DOT,   KC_SLSH,   KC_RSPC,
    KC_ESC        , KC_LALT, KC_APP,  CT_L4,   KC_LCTL,     CT_L2,  KC_SPC,   KC_RWIN,   KC_F5,    S(KC_F5),   KC_RALT,    KC_CAPS),

    [1] = LAYOUT (
    KC_GRV,    KC_EXLM,    KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,    KC_CIRC,  KC_AMPR,  KC_F1,    KC_F2,    KC_F3,    KC_F4,
    KC_TILD,   KC_MINS,    KC_EQL,  KC_DQUO,  KC_LCBR, KC_COLN,    KC_RCBR,  KC_BSLS,  KC_F5,    KC_F6,    KC_F7,    KC_F8,
    KC_LSFT,   KC_ASTR,    KC_PLUS, KC_QUOT,  KC_LBRC, KC_SCLN,    KC_RBRC,  KC_PIPE,  KC_F9,    KC_F10,   KC_F11,   KC_F12,
    TO (0),     TO (1),      KC_NO,   KC_LGUI,  KC_LCTL, KC_NO,      KC_NO,    KC_RALT,  KC_NO,    KC_NO,    KC_NO,    KC_NO),

    [2] = LAYOUT (
    A (KC_F4), G (KC_1),   G (KC_2),       G (KC_3),      G (KC_4),    G (KC_5),    KC_HOME,    C (KC_LEFT),  C (KC_RGHT),  KC_END,   KC_PGUP,  KC_DEL,
    KC_NO,    CT_AT,      OSL(5),  C (S (KC_TAB)),    C (KC_TAB), KC_NO, KC_LEFT,    KC_DOWN,     KC_UP,       KC_RGHT,  KC_PGDN,  KC_ENT,
    KC_LSFT,   KC_NO,     A (KC_UP),      A(KC_LEFT),   A(KC_RGHT), KC_BTN2, G (C (KC_LEFT)),      G (C (KC_LEFT)),       G (C (KC_RGHT)),   G (C (KC_RGHT)),    KC_NO,    KC_NO,
    TO (0),    KC_NO,     KC_NO,         KC_NO,        KC_NO,      KC_NO,      CT_IME,      KC_NO,     DEBUG,       RESET,    KC_NO,    TO (2)),

    [3] = LAYOUT (
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ASTR,   KC_7,   KC_8,    KC_9,   KC_CIRC,  KC_BSPC,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PLUS,   KC_4,   KC_5,    KC_6,   KC_DOT,   KC_ENT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS,   KC_1,   KC_2,    KC_3,   KC_SLSH,  KC_EQL,
    TO (0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_0,      KC_DLR, KC_PERC, KC_NO,  KC_NO,    TO (3)),

    [4] = LAYOUT (
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F1,    KC_F2,   KC_F3,  KC_F4,
    KC_LCTL,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F5,    KC_F6,   KC_7,   KC_F8,
    KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F9,    KC_F10,   KC_F11,  KC_F12,
    TO (0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_0,   KC_NO,     KC_NO,  KC_NO,    KC_NO, KC_NO),

    [5] = LAYOUT (
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F1,    KC_F2,   KC_F3,  KC_F4,
    KC_LCTL,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F5,    KC_F6,   KC_7,   KC_F8,
    KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F9,    KC_F10,   KC_F11,  KC_F12,
    TO (0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_0,   KC_NO,     KC_NO,  KC_NO,    KC_NO, KC_NO)
};


struct key_time_t{
    uint16_t down;
    uint16_t up;
};

struct key_state_t{
    uint64_t kb_view_when_down;
    struct key_time_t time;
};

struct key_state_t ctl1_state = { 0, {0, 0} };
struct key_state_t ctl2_state = { 0, {0, 0} };
struct key_state_t ctl3_state = { 0, {0, 0} };
struct key_state_t ctl4_state = { 0, {0, 0} };

bool process_record_user (uint16_t keycode, keyrecord_t *record){
    static uint64_t kb_view = 0;
    static uint16_t last_keypos = 0;
    bool res = 0;

    kb_view = record->event.pressed ? kb_view | 1ULL << (MATRIX_COLS * record->event.key.row + record->event.key.col) : kb_view & ~(1ULL << (MATRIX_COLS * record->event.key.row + record->event.key.col));

    if (!record->event.pressed && !kb_view){
        if (layer_state_is (1)){
            layer_off (1);
        }
        else if (layer_state_is (2)){
            layer_off (2);
        }
        else if (layer_state_is (3)){
            layer_off (3);
        }
        else if (layer_state_is (4)){
            layer_off (4);
        }
    }

    switch (keycode){
        case CT_L1:
            if (record->event.pressed){
                layer_on (1);
                ctl1_state.time.down = record->event.time;
                ctl1_state.kb_view_when_down = kb_view;
            }
            else{
                if (timer_elapsed (ctl1_state.time.down) < 200 && last_keypos == (record->event.key.col << 8 | record->event.key.row)){
                    tap_code (KC_SCLN);
                }
            }
            break;

        case CT_L2:
            if (record->event.pressed){
                layer_on (2);
                ctl2_state.time.down = record->event.time;
                ctl2_state.kb_view_when_down = kb_view;
            }
            else{
                if (timer_elapsed (ctl2_state.time.down) < 200 && last_keypos == (record->event.key.col << 8 | record->event.key.row)){
                    tap_code16 (KC_UNDS);
                }
            }
            break;

        case CT_L3:
            if (record->event.pressed){
                layer_on (3);
                ctl3_state.time.down = record->event.time;
                ctl3_state.kb_view_when_down = kb_view;
            }
            else{
                // layer_off (3);
                if (timer_elapsed (ctl3_state.time.down) < 200 && last_keypos == (record->event.key.col << 8 | record->event.key.row)){
                    tap_code (KC_TAB);
                }
            }
            break;

        case CT_L4:
            if (record->event.pressed){
                layer_on (4);
                ctl4_state.time.down = record->event.time;
                ctl4_state.kb_view_when_down = kb_view;
            }
            else{
                if (timer_elapsed (ctl4_state.time.down) < 200 && last_keypos == (record->event.key.col << 8 | record->event.key.row)){
                    tap_code (KC_TAB);
                }
            }
            break;

        case CT_IME:
            if (record->event.pressed){
                tap_code (KC_RCTL), tap_code16 (C (S (KC_SPC)));
            }
            break;

        case CT_AT:
            if (record->event.pressed){
                register_code (KC_LALT), tap_code (KC_TAB);
            }
            else{
                unregister_code (KC_LALT);
            }
            break;

        default:
            res = 1;
            break;
    }

    last_keypos = (record->event.key.col << 8 | record->event.key.row);
    return res;
}

void ps2_mouse_moved_user (report_mouse_t *mouse_report){
    static uint16_t last_sample_time = 0;
    uint16_t interval = timer_elapsed (last_sample_time);

    if (layer_state_is (3)){
        if (interval > 50){
            last_sample_time = timer_read ();
            mouse_report->v = mouse_report->y > 2 ? -1 : mouse_report->y < -2 ? 1 : 0;
            mouse_report->h = mouse_report->x > 2 ? 1 : mouse_report->x < -2 ? -1 : 0;
        }
        mouse_report->x = mouse_report->y = 0;
    }
    // else{
    //     int8_t absx = abs (mouse_report->x), absy = abs (mouse_report->y);

    //     if (absx > 5 && absy > 5){
    //     }
    //     else if (absx <= 5 && absy <= 5 && interval < 15){
    //         mouse_report->x = mouse_report->y = 0;
    //     }
    //     else if (absx > 5 && absy <= 5 && interval < 15){
    //         mouse_report->y = 0;
    //     }
    //     if (interval >= 15){
    //         last_sample_time = timer_read ();
    //     }
    // }
}


// 按下 Capslock 的時候，第 6 個 RGB 燈與之後 (也就第 7 個) 的 4 個會亮與第 12 個燈 RGB (也就是第 13 個) 之後的 4 個燈會亮紅色。
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    { 0, 1, HSV_RED }       // Light 4 LEDs, starting with LED 6
);
// Layer 1 啟用的時候，第 9, 10 個燈會亮
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    { 0, 1, HSV_ORANGE }
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    { 0, 1, HSV_AZURE }
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    { 0, 1, HSV_GREEN }
);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    { 0, 1, HSV_BLUE }
);
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS (
    { 0, 1, HSV_WHITE }
);
// etc..

// 接者將您的 rgblight_segment_t 放到 RGBLIGHT_LAYERS_LIST 內
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST (
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,     // Overrides other layers
    my_layer3_layer,    // Overrides caps lock layer
    my_layer4_layer,    // Overrides caps lock layer
    my_layer5_layer    // Overrides caps lock layer
);

void keyboard_post_init_user (void){
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user (layer_state_t state){
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state (1, layer_state_cmp (state, 1));
    rgblight_set_layer_state (2, layer_state_cmp (state, 2));
    rgblight_set_layer_state (3, layer_state_cmp (state, 3));
    rgblight_set_layer_state (4, layer_state_cmp (state, 4));
    rgblight_set_layer_state (5, layer_state_cmp (state, 5));
    return state;
}

bool led_update_user (led_t led_state){
    rgblight_set_layer_state (0, led_state.caps_lock);
    return true;
}
