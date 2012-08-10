#ifndef UNICODE_H_
#define UNICODE_H_

// Map control keys to Unicode Private use characters

#define KEYBOARD_UKEY_ASCII_MIN 0x0000
#define KEYBOARD_UKEY_ASCII_MAX 0x007F

#define KEYBOARD_UKEY_PRIVATE_MIN 0xE000
#define KEYBOARD_UKEY_PRIVATE_MAX 0xF8FF

enum keyboard_ukey {
	keyboard_ukey_ascii_min				= KEYBOARD_UKEY_ASCII_MIN,
	keyboard_ukey_ascii_max				= KEYBOARD_UKEY_ASCII_MAX,

	keyboard_ukey_private_min			= KEYBOARD_UKEY_PRIVATE_MIN,

	keyboard_ukey_cancel				= KEYBOARD_UKEY_PRIVATE_MIN, // ctrl+c signal

	keyboard_ukey_backspace,
	keyboard_ukey_tab,
	keyboard_ukey_clear,
	keyboard_ukey_return,

	keyboard_ukey_shift_l,
	keyboard_ukey_shift_r,

	keyboard_ukey_ctrl_l,
	keyboard_ukey_ctrl_r,
	
	keyboard_ukey_alt_l,
	keyboard_ukey_alt_r,

	keyboard_ukey_pause,

	keyboard_ukey_capslock,
	keyboard_ukey_numlock,
	keyboard_ukey_scrolllock,

	keyboard_ukey_escape,

	keyboard_ukey_pgup,
	keyboard_ukey_pgdn,

	keyboard_ukey_home,
	keyboard_ukey_end,

	keyboard_ukey_up,
	keyboard_ukey_down,
	keyboard_ukey_left,
	keyboard_ukey_right,

	keyboard_ukey_select, // ???
	keyboard_ukey_print, // ctrl+p?
	keyboard_ukey_execute, // ???
	
	keyboard_ukey_printscreen,

	keyboard_ukey_insert,
	keyboard_ukey_delete,

	keyboard_ukey_help,
	
	keyboard_ukey_meta_l,
	keyboard_ukey_meta_r,

	keyboard_ukey_apps, // context menu? (button between altr and ctrlr)

	keyboard_ukey_power,
	keyboard_ukey_sleep,
	keyboard_ukey_wake,

	keyboard_ukey_f1,
	keyboard_ukey_f2,
	keyboard_ukey_f3,
	keyboard_ukey_f4,
	keyboard_ukey_f5,
	keyboard_ukey_f6,
	keyboard_ukey_f7,
	keyboard_ukey_f8,
	keyboard_ukey_f9,
	keyboard_ukey_f10,
	keyboard_ukey_f11,
	keyboard_ukey_f12,
	keyboard_ukey_f13,
	keyboard_ukey_f14,
	keyboard_ukey_f15,

	keyboard_ukey_num0,
	keyboard_ukey_num1,
	keyboard_ukey_num2,
	keyboard_ukey_num3,
	keyboard_ukey_num4,
	keyboard_ukey_num5,
	keyboard_ukey_num6,
	keyboard_ukey_num7,
	keyboard_ukey_num8,
	keyboard_ukey_num9,

	
	//keyboard_ukey_
	
	keyboard_ukey_unknown,

	keyboard_ukey_private_max				= KEYBOARD_UKEY_PRIVATE_MAX
};

#endif // UNICODE_H_
