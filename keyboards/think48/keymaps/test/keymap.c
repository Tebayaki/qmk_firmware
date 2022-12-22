#include "think48.h"

enum my_keycodes{
    CT_IME = SAFE_RANGE, // ime switch
	CT_LCTL,
    CT_AT,
	CT_MO1,
	CT_MO2,
	CT_MO3,
	CT_MO4,
	CT_OSL5,
	CT_1,
	CT_2,
	CT_3,
	CT_4,
	CT_5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT (
    KC_MS_BTN1, KC_Q,    KC_W,    KC_E,      KC_R,      KC_T,    KC_Y,     KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
    CT_MO2    , KC_A,    KC_S,    KC_D,      KC_F,      KC_G,    KC_H,     KC_J,      KC_K,      KC_L,      CT_MO3,    KC_ENT,
    KC_LSPO   , KC_Z,    KC_X,    KC_C,      KC_V,      KC_B,    KC_N,     KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSPC,
    KC_ESC    , KC_NO,   KC_NO,   KC_LALT,   CT_LCTL,   CT_MO1,  KC_SPC,   KC_RWIN,   CT_MO4,    RESET,     KC_NO,     KC_CAPS),

    [1] = LAYOUT (
    A(KC_F4), CT_1,      CT_2,       CT_3,         CT_4,       CT_5,    KC_HOME,    C(KC_LEFT),  C(KC_RGHT),    KC_END,        KC_PGUP,  KC_DEL,
    KC_NO,    CT_AT,     CT_OSL5,    C(S(KC_TAB)), C (KC_TAB), KC_NO,   KC_LEFT,    KC_DOWN,     KC_UP,         KC_RGHT,       KC_PGDN,  KC_ENT,
    KC_LSFT,  KC_NO,     A (KC_UP),  A(KC_LEFT),   A(KC_RGHT), KC_NO,   KC_NO,      KC_NO,       G(C(KC_RGHT)), G(C(KC_RGHT)), KC_NO,    KC_RSFT,
    TO(0),    KC_NO,     KC_NO,      KC_NO,        KC_NO,      KC_NO,   CT_IME,     KC_NO,       KC_NO,         KC_NO,         KC_NO,    KC_NO),

    [2] = LAYOUT (
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_7,   KC_8,    KC_9,   KC_NO,  KC_DEL,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_4,   KC_5,    KC_6,   KC_DOT, KC_ENT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_1,   KC_2,    KC_3,   KC_NO,  KC_NO,
    TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_0,      KC_NO,  KC_NO,   KC_NO,  KC_NO,  KC_NO),

    [3] = LAYOUT (
    KC_GRV,    KC_EXLM,    KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,    KC_CIRC,  KC_AMPR,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_TILD,   KC_MINS,    KC_EQL,  KC_DQUO,  KC_LCBR, KC_COLN,    KC_RCBR,  KC_BSLS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_LSFT,   KC_ASTR,    KC_PLUS, KC_QUOT,  KC_LBRC, KC_SCLN,    KC_RBRC,  KC_PIPE,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
    TO(0),     KC_NO,      KC_NO,   KC_LALT,  KC_LCTL, KC_NO,      KC_NO,    KC_RGUI,  KC_NO,   KC_NO,   KC_NO,   KC_NO),

    [4] = LAYOUT (
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),

    [5] = LAYOUT (
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
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
struct key_state_t ct_mo_1_state = {{0, 0}, 0, 0};
struct key_state_t ct_mo_2_state = {{0, 0}, 0, 0};
struct key_state_t ct_mo_3_state = {{0, 0}, 0, 0};
struct key_state_t ct_lctl_state = {{0, 0}, 0, 0};
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
	if (!record->event.pressed && !layer_state_is(0) && !kb_state.high && !kb_state.low && !layer_state_is(5)) {
		layer_clear();
	}
	// 执行对应的操作
	switch (keycode) {
		case CT_MO1:
			if (record->event.pressed) {
				layer_on(1);
				ct_mo_1_state.time_down = record->event.time;
				ct_mo_1_state.kb_state_when_down = kb_state;
			} else {
				if (timer_elapsed(ct_mo_1_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code16(KC_UNDS);
				} else if (is_gui_num_down){
					unregister_code(KC_LGUI);
					is_gui_num_down = false;
				}
			}
			break;
		case CT_MO2:
			if (record->event.pressed) {
				layer_on(2);
				ct_mo_2_state.time_down = record->event.time;
				ct_mo_2_state.kb_state_when_down = kb_state;
			} else {
				if (timer_elapsed(ct_mo_2_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code(KC_TAB);
				}
			}
			break;
		case CT_MO3:
			if (record->event.pressed) {
				layer_on(3);
				ct_mo_3_state.time_down = record->event.time;
				ct_mo_3_state.kb_state_when_down = kb_state;
			} else {
				if (timer_elapsed(ct_mo_3_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code(KC_SCLN);
				}
			}
			break;
		case CT_MO4:
			if (record->event.pressed) {
				layer_on(4);
			}
			break;
		case CT_OSL5:
			if (record->event.pressed) {
				layer_on(5);
			}
			break;
		case CT_LCTL:
			if (record->event.pressed) {
				register_code(KC_LCTL);
				ct_lctl_state.time_down = record->event.time;
				ct_lctl_state.kb_state_when_down = kb_state;
			} else {
				unregister_code(KC_LCTL);
				if (timer_elapsed(ct_lctl_state.time_down) < 200 && last_key_bit == this_key_bit) {
					tap_code16(KC_COLN);
				}
			}
			break;
		case CT_IME:
            if (record->event.pressed){
                tap_code (KC_RCTL), tap_code16(C(S(KC_SPC)));
            }
            break;
		case CT_AT:
            if (record->event.pressed){
                register_code (KC_LALT), tap_code (KC_TAB);
            }else{
                unregister_code (KC_LALT);
            }
            break;
		case CT_1:
		case CT_2:
		case CT_3:
		case CT_4:
		case CT_5:
			if (record->event.pressed && layer_state_is(1)) {
				register_code(KC_LGUI), tap_code(keycode - CT_1 + 30);
				is_gui_num_down = true;
			}
			break;
		default:
			// 当处于第5层时, 按下任意键返回第0层
			if (record->event.pressed && layer_state_is(5)) {
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

    if (layer_state_is (2)){
        if (interval > 50){
            last_sample_time = timer_read ();
            mouse_report->v = mouse_report->y > 2 ? -1 : mouse_report->y < -2 ? 1 : 0;
            mouse_report->h = mouse_report->x > 2 ? 1 : mouse_report->x < -2 ? -1 : 0;
        }
        mouse_report->x = mouse_report->y = 0;
    }
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
