#include "think84.h"
// #include "stdlib.h"
// #include "ps2_mouse.h"

enum my_keycodes{
    FN_IME = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC),

  [1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

typedef uint8_t key_bit_t;

struct keyboard_state_t {
	uint64_t high;
	uint64_t low;
};

struct key_state_t {
	struct keyboard_state_t kb_state_when_down;
	uint16_t time_down;
	uint16_t time_up;
};

struct keyboard_state_t kb_state = {0, 0};
struct key_state_t fn_1_state = {{0, 0}, 0, 0};
struct key_state_t fn_2_state = {{0, 0}, 0, 0};
struct key_state_t fn_3_state = {{0, 0}, 0, 0};
key_bit_t this_key_bit = 0;
key_bit_t last_key_bit = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
	bool res = 0;
	static bool mo_flag = 0;
	// 获取按下的键位
	this_key_bit = (MATRIX_COLS * record->event.key.row + record->event.key.col);
	// 更新键盘状态
	if (record->event.pressed) {
		this_key_bit < 64 ? (kb_state.high |= 1ULL << this_key_bit) : (kb_state.low |= 1ULL << (this_key_bit & 63));
	} else {
		this_key_bit < 64 ? (kb_state.high &= ~(1ULL << this_key_bit)) : (kb_state.low &= ~(1ULL << (this_key_bit & 63)));
	}

	// 当没有键被按下时，回到0层
	if (!record->event.pressed && !kb_state.high && !kb_state.low) {
		layer_clear();
	}
	// 执行对应的操作
	switch (keycode) {
		case FN_IME:
            if (record->event.pressed){
                tap_code (KC_RCTL), tap_code16 (C (S (KC_SPC)));
            }
            break;
		case FN_AT:
            if (record->event.pressed){
                register_code (KC_LALT), tap_code (KC_TAB);
            }else{
                unregister_code (KC_LALT);
            }
            break;
		default:
			res = 1;
			break;
	}

	if (QK_MOMENTARY == (QK_MOMENTARY & keycode)){
		mo_flag = 1;
		res = record->event.pressed ? 1 : 0;
    }
    if (mo_flag && !record->event.pressed && !kb_state.high && !kb_state.low){
        mo_flag = 0;
        layer_clear ();
    }

	last_key_bit = this_key_bit;
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
}