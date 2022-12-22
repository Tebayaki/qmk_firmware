#include "think84.h"
// #include "stdlib.h"
#include "ps2_mouse.h"

enum my_keycodes{
    FN_IME = SAFE_RANGE, // ime switch
    FN_AT, // alt-tab
    FN_1,
    FN_2,
    FN_3,
	FN_4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
        RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_DEL, KC_CAPS,
        FN_3,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, FN_2, KC_ENT, FN_IME,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LALT, KC_ESC, KC_APP, KC_LCTL, FN_1, KC_MS_BTN1, KC_SPC, KC_RGUI, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

  [1] = LAYOUT(
        KC_NO,     KC_6,     KC_7,     KC_8,          KC_9,       KC_0,            KC_NO,     KC_NO,       KC_NO,       KC_NO,       KC_NO,     KC_NO,      KC_NO,      KC_NO,
        A(KC_F4),  KC_1,     KC_2,     KC_3,          KC_4,       KC_5,            KC_HOME,   C(KC_LEFT),  C(KC_RGHT),  KC_END,      KC_PGUP,   KC_BSPC,    KC_DEL,     KC_NO,
        KC_NO,     FN_AT,    FN_4,     C(S(KC_TAB)),   C(KC_TAB),   G(C(KC_LEFT)),    KC_LEFT,   KC_DOWN,     KC_UP,       KC_RGHT,     KC_PGDN,   KC_ENT,     KC_NO,
        KC_LSFT,   KC_NO,    A(KC_UP),  A(KC_LEFT),     A(KC_RGHT),  G(C(KC_RGHT)),    KC_NO,     KC_NO,       KC_NO,       KC_NO,       KC_NO,     KC_RSFT,
        KC_LALT,   KC_NO,    KC_NO,     KC_LCTL,        KC_NO,       KC_MS_BTN2,       KC_NO,     KC_RGUI,       KC_NO,       KC_NO,       KC_NO,     KC_NO),

  [2] = LAYOUT(
        KC_NO,     KC_NO,      KC_LPRN,    KC_RPRN,   KC_NO,   KC_NO,      KC_NO,    KC_NO,       KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_GRV,    KC_EXLM,    KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,    KC_CIRC,  KC_AMPR,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_TILD,   KC_MINS,    KC_EQL,  KC_DQUO,  KC_LCBR, KC_LPRN,    KC_RCBR,  KC_BSLS,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_LSFT,   KC_ASTR,    KC_PLUS, KC_QUOT,  KC_LBRC, KC_SCLN,    KC_RBRC,  KC_PIPE,     KC_NO,     KC_NO,     KC_NO,     KC_RSFT,
        KC_LALT,   KC_NO,     KC_NO,    KC_LCTL,  KC_COLN, KC_NO,      KC_NO,    KC_NO,       KC_NO,     KC_NO,     KC_NO,     KC_NO),

  [3] = LAYOUT(
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_7,      KC_8,      KC_9,      KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_4,      KC_5,      KC_6,      KC_NO,     KC_NO,     KC_NO,
        KC_LSFT,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_1,      KC_2,      KC_3,      KC_NO,     KC_RSFT,
        KC_LALT,   KC_NO,     KC_NO,     KC_LCTL,   KC_NO,     KC_NO,     KC_0,      KC_RGUI,   KC_NO,     KC_NO,     KC_NO,     KC_NO),

  [4] = LAYOUT(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
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
bool is_gui_num_down = false;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
	bool res = 0;
	// 获取按下的键位
	this_key_bit = (MATRIX_COLS * record->event.key.row + record->event.key.col);
	// 更新键盘状态
	if (record->event.pressed) {
		this_key_bit < 64 ? (kb_state.high |= 1ULL << this_key_bit) : (kb_state.low |= 1ULL << (this_key_bit & 63));
	} else {
		this_key_bit < 64 ? (kb_state.high &= ~(1ULL << this_key_bit)) : (kb_state.low &= ~(1ULL << (this_key_bit & 63)));
	}
	// 当没有键被按下时，回到0层
	if (!record->event.pressed && !layer_state_is(0) && !kb_state.high && !kb_state.low && !layer_state_is(4)) {
		layer_clear();
	}
	// 执行对应的操作
	switch (keycode) {
		case FN_1:
			if (record->event.pressed) {
				layer_on(1);
				fn_1_state.time_down = record->event.time;
				fn_1_state.kb_state_when_down = kb_state;
			} else {
				if (timer_elapsed(fn_1_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code16(KC_UNDS);
				} else if (is_gui_num_down){
					unregister_code(KC_LGUI);
					is_gui_num_down = false;
				}
			}
			break;
		case FN_2:
			if (record->event.pressed) {
				layer_on(2);
				fn_1_state.time_down = record->event.time;
				fn_1_state.kb_state_when_down = kb_state;
			} else {
				if (timer_elapsed(fn_1_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code(KC_SCLN);
				}
			}
			break;
		case FN_3:
			if (record->event.pressed) {
				layer_on(3);
				fn_1_state.time_down = record->event.time;
				fn_1_state.kb_state_when_down = kb_state;
			} else {
				if (timer_elapsed(fn_1_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code(KC_TAB);
				}
			}
			break;
		case FN_4:
			if (record->event.pressed) {
				layer_on(4);
			}
			break;
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
		case KC_1:
		case KC_2:
		case KC_3:
		case KC_4:
		case KC_5:
		case KC_6:
		case KC_7:
		case KC_8:
		case KC_9:
		case KC_0:
			if (record->event.pressed && layer_state_is(1)) {
				register_code(KC_LGUI), tap_code(keycode);
				is_gui_num_down = true;
			}
			break;
		default:
			// 当处于第四层时, 按下任意键返回第0层
			if (record->event.pressed && layer_state_is(4)) {
				layer_clear();
			} else {
				res = 1;
			}
			break;
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