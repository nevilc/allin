// DirectInput-compatable keycodes
// Courtesy of apollo of the Elite PvPers forum

#include "os.h"

#ifdef WINDOWS_OS

#ifndef H_DIRECTINPUT
#define H_DIRECTINPUT

#define DIKEYBOARD_ESCAPE 0x0401 //
#define DIKEYBOARD_1 0x0402 //
#define DIKEYBOARD_2 0x0403 //
#define DIKEYBOARD_3 0x0404 //
#define DIKEYBOARD_4 0x0405 //
#define DIKEYBOARD_5 0x0406 //
#define DIKEYBOARD_6 0x0407 //
#define DIKEYBOARD_7 0x0408 //
#define DIKEYBOARD_8 0x0409 //
#define DIKEYBOARD_9 0x040A //
#define DIKEYBOARD_0 0x040B //
#define DIKEYBOARD_MINUS 0x040C // (* - on main keyboard *)
#define DIKEYBOARD_EQUALS 0x040D //
#define DIKEYBOARD_BACK 0x040E // (* backspace *)
#define DIKEYBOARD_TAB 0x040F //
#define DIKEYBOARD_Q 0x0410 //
#define DIKEYBOARD_W 0x0411 //
#define DIKEYBOARD_E 0x0412 //
#define DIKEYBOARD_R 0x0413 //
#define DIKEYBOARD_T 0x0414 //
#define DIKEYBOARD_Y 0x0415 //
#define DIKEYBOARD_U 0x0416 //
#define DIKEYBOARD_I 0x0417 //
#define DIKEYBOARD_O 0x0418 //
#define DIKEYBOARD_P 0x0419 //
#define DIKEYBOARD_LBRACKET 0x041A //
#define DIKEYBOARD_RBRACKET 0x041B //
#define DIKEYBOARD_RETURN 0x041C // (* Enter on main keyboard *)
#define DIKEYBOARD_LCONTROL 0x041D //
#define DIKEYBOARD_A 0x041E //
#define DIKEYBOARD_S 0x041F //
#define DIKEYBOARD_D 0x0420 //
#define DIKEYBOARD_F 0x0421 //
#define DIKEYBOARD_G 0x0422 //
#define DIKEYBOARD_H 0x0423 //
#define DIKEYBOARD_J 0x0424 //
#define DIKEYBOARD_K 0x0425 //
#define DIKEYBOARD_L 0x0426 //
#define DIKEYBOARD_SEMICOLON 0x0427 //
#define DIKEYBOARD_APOSTROPHE 0x0428 //
#define DIKEYBOARD_GRAVE 0x0429 // (* accent grave *)
#define DIKEYBOARD_LSHIFT 0x042A //
#define DIKEYBOARD_BACKSLASH 0x042B //
#define DIKEYBOARD_Z 0x042C //
#define DIKEYBOARD_X 0x042D //
#define DIKEYBOARD_C 0x042E //
#define DIKEYBOARD_V 0x042F //
#define DIKEYBOARD_B 0x0430 //
#define DIKEYBOARD_N 0x0431 //
#define DIKEYBOARD_M 0x0432 //
#define DIKEYBOARD_COMMA 0x0433 //
#define DIKEYBOARD_PERIOD 0x0434 // (* . on main keyboard *)
#define DIKEYBOARD_SLASH 0x0435 // (* / on main keyboard *)
#define DIKEYBOARD_RSHIFT 0x0436 //
#define DIKEYBOARD_MULTIPLY 0x0437 // (* * on numeric keypad *)
#define DIKEYBOARD_LMENU 0x0438 // (* left Alt *)
#define DIKEYBOARD_SPACE 0x0439 //
#define DIKEYBOARD_CAPITAL 0x043A //
#define DIKEYBOARD_F1 0x043B //
#define DIKEYBOARD_F2 0x043C //
#define DIKEYBOARD_F3 0x043D //
#define DIKEYBOARD_F4 0x043E //
#define DIKEYBOARD_F5 0x043F //
#define DIKEYBOARD_F6 0x0440 //
#define DIKEYBOARD_F7 0x0441 //
#define DIKEYBOARD_F8 0x0442 //
#define DIKEYBOARD_F9 0x0443 //
#define DIKEYBOARD_F10 0x0444 //
#define DIKEYBOARD_NUMLOCK 0x0445 //
#define DIKEYBOARD_SCROLL 0x0446 // (* Scroll Lock *)
#define DIKEYBOARD_NUMPAD7 0x0447 //
#define DIKEYBOARD_NUMPAD8 0x0448 //
#define DIKEYBOARD_NUMPAD9 0x0449 //
#define DIKEYBOARD_SUBTRACT 0x044A // (* - on numeric keypad *)
#define DIKEYBOARD_NUMPAD4 0x044B //
#define DIKEYBOARD_NUMPAD5 0x044C //
#define DIKEYBOARD_NUMPAD6 0x044D //
#define DIKEYBOARD_ADD 0x044E // (* + on numeric keypad *)
#define DIKEYBOARD_NUMPAD1 0x044F //
#define DIKEYBOARD_NUMPAD2 0x0450 //
#define DIKEYBOARD_NUMPAD3 0x0451 //
#define DIKEYBOARD_NUMPAD0 0x0452 //
#define DIKEYBOARD_DECIMAL 0x0453 // (* . on numeric keypad *)
#define DIKEYBOARD_OEM_102 0x0456 // (* < > | on UK/Germany keyboards *)
#define DIKEYBOARD_F11 0x0457 //
#define DIKEYBOARD_F12 0x0458 //
#define DIKEYBOARD_F13 0x0464 // (* (NEC PC98) *)
#define DIKEYBOARD_F14 0x0465 // (* (NEC PC98) *)
#define DIKEYBOARD_F15 0x0466 // (* (NEC PC98) *)
#define DIKEYBOARD_KANA 0x0470 // (* (Japanese keyboard) *)
#define DIKEYBOARD_ABNT_C1 0x0473 // (* / ? on Portugese (Brazilian) keyboards *)
#define DIKEYBOARD_CONVERT 0x0479 // (* (Japanese keyboard) *)
#define DIKEYBOARD_NOCONVERT 0x047B // (* (Japanese keyboard) *)
#define DIKEYBOARD_YEN 0x047D // (* (Japanese keyboard) *)
#define DIKEYBOARD_ABNT_C2 0x047E // (* Numpad . on Portugese (Brazilian) keyboards *)
#define DIKEYBOARD_NUMPADEQUALS 0x048D // (* = on numeric keypad (NEC PC98) *)
#define DIKEYBOARD_PREVTRACK 0x0490 // (* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) *)
#define DIKEYBOARD_AT 0x0491 // (* (NEC PC98) *)
#define DIKEYBOARD_COLON 0x0492 // (* (NEC PC98) *)
#define DIKEYBOARD_UNDERLINE 0x0493 // (* (NEC PC98) *)
#define DIKEYBOARD_KANJI 0x0494 // (* (Japanese keyboard) *)
#define DIKEYBOARD_STOP 0x0495 // (* (NEC PC98) *)
#define DIKEYBOARD_AX 0x0496 // (* (Japan AX) *)
#define DIKEYBOARD_UNLABELED 0x0497 // (* (J3100) *)
#define DIKEYBOARD_NEXTTRACK 0x0499 // (* Next Track *)
#define DIKEYBOARD_NUMPADENTER 0x049C // (* Enter on numeric keypad *)
#define DIKEYBOARD_RCONTROL 0x049D //
#define DIKEYBOARD_MUTE 0x04A0 // (* Mute *)
#define DIKEYBOARD_CALCULATOR 0x04A1 // (* Calculator *)
#define DIKEYBOARD_PLAYPAUSE 0x04A2 // (* Play / Pause *)
#define DIKEYBOARD_MEDIASTOP 0x04A4 // (* Media Stop *)
#define DIKEYBOARD_VOLUMEDOWN 0x04AE // (* Volume - *)
#define DIKEYBOARD_VOLUMEUP 0x04B0 // (* Volume + *)
#define DIKEYBOARD_WEBHOME 0x04B2 // (* Web home *)
#define DIKEYBOARD_NUMPADCOMMA 0x04B3 // (* , on numeric keypad (NEC PC98) *)
#define DIKEYBOARD_DIVIDE 0x04B5 // (* / on numeric keypad *)
#define DIKEYBOARD_SYSRQ 0x04B7 //
#define DIKEYBOARD_RMENU 0x04B8 // (* right Alt *)
#define DIKEYBOARD_PAUSE 0x04C5 // (* Pause *)
#define DIKEYBOARD_HOME 0x04C7 // (* Home on arrow keypad *)
#define DIKEYBOARD_UP 0x04C8 // (* UpArrow on arrow keypad *)
#define DIKEYBOARD_PRIOR 0x04C9 // (* PgUp on arrow keypad *)
#define DIKEYBOARD_LEFT 0x04CB // (* LeftArrow on arrow keypad *)
#define DIKEYBOARD_RIGHT 0x04CD // (* RightArrow on arrow keypad *)
#define DIKEYBOARD_END 0x04CF // (* End on arrow keypad *)
#define DIKEYBOARD_DOWN 0x04D0 // (* DownArrow on arrow keypad *)
#define DIKEYBOARD_NEXT 0x04D1 // (* PgDn on arrow keypad *)
#define DIKEYBOARD_INSERT 0x04D2 // (* Insert on arrow keypad *)
#define DIKEYBOARD_DELETE 0x04D3 // (* Delete on arrow keypad *)
#define DIKEYBOARD_LWIN 0x04DB // (* Left Windows key *)
#define DIKEYBOARD_RWIN 0x04DC // (* Right Windows key *)
#define DIKEYBOARD_APPS 0x04DD // (* AppMenu key *)
#define DIKEYBOARD_POWER 0x04DE // (* System Power *)
#define DIKEYBOARD_SLEEP 0x04DF // (* System Sleep *)
#define DIKEYBOARD_WAKE 0x04E3 // (* System Wake *)
#define DIKEYBOARD_WEBSEARCH 0x04E5 // (* Web Search *)
#define DIKEYBOARD_WEBFAVORITES 0x04E6 // (* Web Favorites *)
#define DIKEYBOARD_WEBREFRESH 0x04E7 // (* Web Refresh *)
#define DIKEYBOARD_WEBSTOP 0x04E8 // (* Web Stop *)
#define DIKEYBOARD_WEBFORWARD 0x04E9 // (* Web Forward *)
#define DIKEYBOARD_WEBBACK 0x04EA // (* Web Back *)
#define DIKEYBOARD_MYCOMPUTER 0x04EB // (* My Computer *)
#define DIKEYBOARD_MAIL 0x04EC // (* Mail *)
#define DIKEYBOARD_MEDIASELECT 0x04ED // (* Media Select *)

enum keyboard_dikey
{
	keyboard_dikey_na					= 0,

	keyboard_dikey_escape				= DIKEYBOARD_ESCAPE,
	keyboard_dikey_1					= DIKEYBOARD_1,
	keyboard_dikey_2					= DIKEYBOARD_2,
	keyboard_dikey_3					= DIKEYBOARD_3,
	keyboard_dikey_4					= DIKEYBOARD_4,
	keyboard_dikey_5					= DIKEYBOARD_5,
	keyboard_dikey_6					= DIKEYBOARD_6,
	keyboard_dikey_7					= DIKEYBOARD_7,
	keyboard_dikey_8					= DIKEYBOARD_8,
	keyboard_dikey_9					= DIKEYBOARD_9,
	keyboard_dikey_0					= DIKEYBOARD_0,

	keyboard_dikey_minus				= DIKEYBOARD_MINUS,
	keyboard_dikey_equals				= DIKEYBOARD_EQUALS,
	keyboard_dikey_backspace			= DIKEYBOARD_BACK,
	keyboard_dikey_tab					= DIKEYBOARD_TAB,

	keyboard_dikey_q					= DIKEYBOARD_Q,
	keyboard_dikey_w					= DIKEYBOARD_W,
	keyboard_dikey_e					= DIKEYBOARD_E,
	keyboard_dikey_r					= DIKEYBOARD_R,
	keyboard_dikey_t					= DIKEYBOARD_T,
	keyboard_dikey_y					= DIKEYBOARD_Y,
	keyboard_dikey_u					= DIKEYBOARD_U,
	keyboard_dikey_i					= DIKEYBOARD_I,
	keyboard_dikey_o					= DIKEYBOARD_O,
	keyboard_dikey_p					= DIKEYBOARD_P,

	keyboard_dikey_lbracket				= DIKEYBOARD_LBRACKET,
	keyboard_dikey_rbracket				= DIKEYBOARD_RBRACKET,
	keyboard_dikey_return				= DIKEYBOARD_RETURN,
	keyboard_dikey_ctrl_l				= DIKEYBOARD_LCONTROL,

	keyboard_dikey_a					= DIKEYBOARD_A,
	keyboard_dikey_s					= DIKEYBOARD_S,
	keyboard_dikey_d					= DIKEYBOARD_D,
	keyboard_dikey_f					= DIKEYBOARD_F,
	keyboard_dikey_g					= DIKEYBOARD_G,
	keyboard_dikey_h					= DIKEYBOARD_H,
	keyboard_dikey_j					= DIKEYBOARD_J,
	keyboard_dikey_k					= DIKEYBOARD_K,
	keyboard_dikey_l					= DIKEYBOARD_L,

	keyboard_dikey_semicolon			= DIKEYBOARD_SEMICOLON,
	keyboard_dikey_apostrophe			= DIKEYBOARD_APOSTROPHE,
	keyboard_dikey_grave				= DIKEYBOARD_GRAVE,
	keyboard_dikey_shift_l				= DIKEYBOARD_LSHIFT,
	keyboard_dikey_backslash			= DIKEYBOARD_BACKSLASH,

	keyboard_dikey_z					= DIKEYBOARD_Z,
	keyboard_dikey_x					= DIKEYBOARD_X,
	keyboard_dikey_c					= DIKEYBOARD_C,
	keyboard_dikey_v					= DIKEYBOARD_V,
	keyboard_dikey_b					= DIKEYBOARD_B,
	keyboard_dikey_n					= DIKEYBOARD_N,
	keyboard_dikey_m					= DIKEYBOARD_M,
	
	keyboard_dikey_comma				= DIKEYBOARD_COMMA,
	keyboard_dikey_period				= DIKEYBOARD_PERIOD,
	keyboard_dikey_slash				= DIKEYBOARD_SLASH,
	keyboard_dikey_shift_r				= DIKEYBOARD_RSHIFT,
	keyboard_dikey_multiply				= DIKEYBOARD_MULTIPLY,
	keyboard_dikey_alt_l				= DIKEYBOARD_LMENU,
	keyboard_dikey_space				= DIKEYBOARD_SPACE,
	keyboard_dikey_capslock				= DIKEYBOARD_CAPITAL,

	keyboard_dikey_f1					= DIKEYBOARD_F1,
	keyboard_dikey_f2					= DIKEYBOARD_F2,
	keyboard_dikey_f3					= DIKEYBOARD_F3,
	keyboard_dikey_f4					= DIKEYBOARD_F4,
	keyboard_dikey_f5					= DIKEYBOARD_F5,
	keyboard_dikey_f6					= DIKEYBOARD_F6,
	keyboard_dikey_f7					= DIKEYBOARD_F7,
	keyboard_dikey_f8					= DIKEYBOARD_F8,
	keyboard_dikey_f9					= DIKEYBOARD_F9,
	keyboard_dikey_f10					= DIKEYBOARD_F10,

	keyboard_dikey_numlock				= DIKEYBOARD_NUMLOCK,
	keyboard_dikey_scrolllock			= DIKEYBOARD_SCROLL,
	keyboard_dikey_num7					= DIKEYBOARD_NUMPAD7,
	keyboard_dikey_num8					= DIKEYBOARD_NUMPAD8,
	keyboard_dikey_num9					= DIKEYBOARD_NUMPAD9,
	keyboard_dikey_subtract				= DIKEYBOARD_SUBTRACT,
	keyboard_dikey_num4					= DIKEYBOARD_NUMPAD4,
	keyboard_dikey_num5					= DIKEYBOARD_NUMPAD5,
	keyboard_dikey_num6					= DIKEYBOARD_NUMPAD6,
	keyboard_dikey_add					= DIKEYBOARD_ADD,
	keyboard_dikey_num1					= DIKEYBOARD_NUMPAD1,
	keyboard_dikey_num2					= DIKEYBOARD_NUMPAD2,
	keyboard_dikey_num3					= DIKEYBOARD_NUMPAD3,
	keyboard_dikey_num0					= DIKEYBOARD_NUMPAD0,
	keyboard_dikey_decimal				= DIKEYBOARD_DECIMAL,
	keyboard_dikey_oem_102				= DIKEYBOARD_OEM_102, // backslash?

	keyboard_dikey_f11					= DIKEYBOARD_F11,
	keyboard_dikey_f12					= DIKEYBOARD_F12,
	keyboard_dikey_f13					= DIKEYBOARD_F13,
	keyboard_dikey_f14					= DIKEYBOARD_F14,
	keyboard_dikey_f15					= DIKEYBOARD_F15,

	//stuff

	keyboard_dikey_ctrl_r				= DIKEYBOARD_RCONTROL,

	//stuff

	keyboard_dikey_alt_r				= DIKEYBOARD_RMENU,

	keyboard_dikey_pause				= DIKEYBOARD_PAUSE,
	keyboard_dikey_home					= DIKEYBOARD_HOME,
	keyboard_dikey_up					= DIKEYBOARD_UP,
	keyboard_dikey_pgup					= DIKEYBOARD_PRIOR,
	keyboard_dikey_left					= DIKEYBOARD_LEFT,
	keyboard_dikey_right				= DIKEYBOARD_RIGHT,
	keyboard_dikey_end					= DIKEYBOARD_END,
	keyboard_dikey_down					= DIKEYBOARD_DOWN,
	keyboard_dikey_pgdn					= DIKEYBOARD_NEXT,
	keyboard_dikey_insert				= DIKEYBOARD_INSERT,
	keyboard_dikey_delete				= DIKEYBOARD_DELETE,

	keyboard_dikey_meta_l				= DIKEYBOARD_LWIN,
	keyboard_dikey_meta_r				= DIKEYBOARD_RWIN,
	keyboard_dikey_apps					= DIKEYBOARD_APPS,

	keyboard_dikey_power				= DIKEYBOARD_POWER,
	keyboard_dikey_sleep				= DIKEYBOARD_SLEEP,
	keyboard_dikey_wake					= DIKEYBOARD_WAKE,

	//stuff
};

#endif//H_DIRECTINPUT

#endif//WINDOWS_OS
