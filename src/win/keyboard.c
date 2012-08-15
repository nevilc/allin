#include "os.h"

#ifdef WINDOWS_OS

// HACK ish
#include "../keyboard.h"
#include "error.h"

#include "directinput.h"

#include <stdio.h>
#include <stdlib.h>

#include <Winuser.h>

enum keyboard_dikey keyboard_ukey_to_dikey(enum keyboard_ukey key) {
	// Convert to DirectInput compatible keycodes
	//if ((key < keyboard_ukey_ascii_min || key > keyboard_ukey_ascii_max) && (key < keyboard_ukey_private_min || key > keyboard_ukey_private_max))
	//{
	//	return keyboard_dikey_na;
	//}

	switch (key) {
	case keyboard_ukey_escape:
		return keyboard_dikey_escape;
	case '1':
		return keyboard_dikey_1;
	case '2':
		return keyboard_dikey_2;
	case '3':
		return keyboard_dikey_3;
	case '4':
		return keyboard_dikey_4;
	case '5':
		return keyboard_dikey_5;
	case '6':
		return keyboard_dikey_6;
	case '7':
		return keyboard_dikey_7;
	case '8':
		return keyboard_dikey_8;
	case '9':
		return keyboard_dikey_9;
	case '0':
		return keyboard_dikey_0;
	case '-':
		return keyboard_dikey_minus;
	case '=':
		return keyboard_dikey_equals;
	case keyboard_ukey_backspace:
		return keyboard_dikey_backspace;
	case '\t':
	case keyboard_ukey_tab:
		return keyboard_dikey_tab;
	case 'q':
		return keyboard_dikey_q;
	case 'w':
		return keyboard_dikey_w;
	case 'e':
		return keyboard_dikey_e;
	case 'r':
		return keyboard_dikey_r;
	case 't':
		return keyboard_dikey_t;
	case 'y':
		return keyboard_dikey_y;
	case 'u':
		return keyboard_dikey_u;
	case 'i':
		return keyboard_dikey_i;
	case 'o':
		return keyboard_dikey_o;
	case 'p':
		return keyboard_dikey_p;
	case '[':
		return keyboard_dikey_lbracket;
	case ']':
		return keyboard_dikey_rbracket;
	case '\n':
	case keyboard_ukey_return:
		return keyboard_dikey_return;
	case keyboard_ukey_ctrl_l:
		return keyboard_dikey_ctrl_l;
	case 'a':
		return keyboard_dikey_a;
	case 's':
		return keyboard_dikey_s;
	case 'd':
		return keyboard_dikey_d;
	case 'f':
		return keyboard_dikey_f;
	case 'g':
		return keyboard_dikey_g;
	case 'h':
		return keyboard_dikey_h;
	case 'j':
		return keyboard_dikey_j;
	case 'k':
		return keyboard_dikey_k;
	case 'l':
		return keyboard_dikey_l;
	case ';':
		return keyboard_dikey_semicolon;
	case '\'':
		return keyboard_dikey_apostrophe;
	case '`':
		return keyboard_dikey_grave;
	case keyboard_ukey_shift_l:
		return keyboard_dikey_shift_l;
	case '\\':
		return keyboard_dikey_oem_102; // ?
	case 'z':
		return keyboard_dikey_z;
	case 'x':
		return keyboard_dikey_x;
	case 'c':
		return keyboard_dikey_c;
	case 'v':
		return keyboard_dikey_v;
	case 'b':
		return keyboard_dikey_b;
	case 'n':
		return keyboard_dikey_n;
	case 'm':
		return keyboard_dikey_m;
	case ',':
		return keyboard_dikey_comma;
	case '.':
		return keyboard_dikey_period;
	case '/':
		return keyboard_dikey_slash;
	case keyboard_ukey_shift_r:
		return keyboard_dikey_shift_r;
	case '*':
		return keyboard_dikey_multiply;
	case keyboard_ukey_alt_l:
		return keyboard_dikey_alt_l;
	case ' ':
		return keyboard_dikey_space;
	case keyboard_ukey_capslock:
		return keyboard_dikey_capslock;
	case keyboard_ukey_f1:
		return keyboard_dikey_f1;
	case keyboard_ukey_f2:
		return keyboard_dikey_f2;
	case keyboard_ukey_f3:
		return keyboard_dikey_f3;
	case keyboard_ukey_f4:
		return keyboard_dikey_f4;
	case keyboard_ukey_f5:
		return keyboard_dikey_f5;
	case keyboard_ukey_f6:
		return keyboard_dikey_f6;
	case keyboard_ukey_f7:
		return keyboard_dikey_f7;
	case keyboard_ukey_f8:
		return keyboard_dikey_f8;
	case keyboard_ukey_f9:
		return keyboard_dikey_f9;
	case keyboard_ukey_f10:
		return keyboard_dikey_f10;
	case keyboard_ukey_numlock:
		return keyboard_dikey_numlock;
	case keyboard_ukey_scrolllock:
		return keyboard_dikey_scrolllock;
	case keyboard_ukey_num7:
		return keyboard_dikey_num7;
	case keyboard_ukey_num8:
		return keyboard_dikey_num8;
	case keyboard_ukey_num9:
		return keyboard_dikey_num9;
//	case '-':
//		return keyboard_dikey_SUBTRACT;
	case keyboard_ukey_num4:
		return keyboard_dikey_num4;
	case keyboard_ukey_num5:
		return keyboard_dikey_num5;
	case keyboard_ukey_num6:
		return keyboard_dikey_num6;
//	case '+':
//		return keyboard_dikey_ADD;
	case keyboard_ukey_num1:
		return keyboard_dikey_num1;
	case keyboard_ukey_num2:
		return keyboard_dikey_num2;
	case keyboard_ukey_num3:
		return keyboard_dikey_num3;
	case keyboard_ukey_num0:
		return keyboard_dikey_num0;
//		return keyboard_dikey_DECIMAL;
//	case '\\':
//		return keyboard_dikey_oem_102;
	case keyboard_ukey_f11:
		return keyboard_dikey_f11;
	case keyboard_ukey_f12:
		return keyboard_dikey_f12;
	case keyboard_ukey_f13:
		return keyboard_dikey_f13;
	case keyboard_ukey_f14:
		return keyboard_dikey_f14;
	case keyboard_ukey_f15:
		return keyboard_dikey_f15;
	/*
		return keyboard_dikey_KANA;
		return keyboard_dikey_ABNT_C1;
		return keyboard_dikey_CONVERT;
		return keyboard_dikey_NOCONVERT;
		return keyboard_dikey_YEN;
		return keyboard_dikey_ABNT_C2;
		return keyboard_dikey_NUMPADEQUALS;
		return keyboard_dikey_PREVTRACK;
	//case '@':
		return keyboard_dikey_AT;
	//case ':':
		return keyboard_dikey_COLON;
	//case '_':
		return keyboard_dikey_UNDERLINE;
		return keyboard_dikey_KANJI;
		return keyboard_dikey_STOP;
		return keyboard_dikey_AX;
		return keyboard_dikey_UNLABELED;
		return keyboard_dikey_NEXTTRACK;
		return keyboard_dikey_NUMPADENTER;
		return keyboard_dikey_RCONTROL;
		return keyboard_dikey_MUTE;
		return keyboard_dikey_CALCULATOR;
		return keyboard_dikey_PLAYPAUSE;
		return keyboard_dikey_MEDIASTOP;
		return keyboard_dikey_VOLUMEDOWN;
		return keyboard_dikey_VOLUMEUP;
		return keyboard_dikey_WEBHOME;
		return keyboard_dikey_NUMPADCOMMA;
		return keyboard_dikey_DIVIDE;
		return keyboard_dikey_SYSRQ;*/
	case keyboard_ukey_alt_r:
		return keyboard_dikey_alt_r;
	case keyboard_ukey_pause:
		return keyboard_dikey_pause;
	case keyboard_ukey_home:
		return keyboard_dikey_home;
	case keyboard_ukey_up:
		return keyboard_dikey_up;
	case keyboard_ukey_pgup:
		return keyboard_dikey_pgup;
	case keyboard_ukey_left:
		return keyboard_dikey_left;
	case keyboard_ukey_right:
		return keyboard_dikey_right;
	case keyboard_ukey_end:
		return keyboard_dikey_end;
	case keyboard_ukey_down:
		return keyboard_dikey_down;
	case keyboard_ukey_pgdn:
		return keyboard_dikey_pgdn;
	case keyboard_ukey_insert:
		return keyboard_dikey_insert;
	case keyboard_ukey_delete:
		return keyboard_dikey_delete;
	case keyboard_ukey_meta_l:
		return keyboard_dikey_meta_l;
	case keyboard_ukey_meta_r:
		return keyboard_dikey_meta_r;
	case keyboard_ukey_apps:
		return keyboard_dikey_apps;
	case keyboard_ukey_power:
		return keyboard_dikey_power;
	case keyboard_ukey_sleep:
		return keyboard_dikey_sleep;
	case keyboard_ukey_wake:
		return keyboard_dikey_wake;
		/*
		return keyboard_dikey_WEBSEARCH;
		return keyboard_dikey_WEBFAVORITES;
		return keyboard_dikey_WEBREFRESH;
		return keyboard_dikey_WEBSTOP;
		return keyboard_dikey_WEBFORWARD;
		return keyboard_dikey_WEBBACK;
		return keyboard_dikey_MYCOMPUTER;
		return keyboard_dikey_MAIL;
		return keyboard_dikey_MEDIASELECT;*/
	default:
		return keyboard_dikey_na;
	}
}

EXPORT struct keyboard_state* keyboard_initialize() {
	struct keyboard_state *state = (struct keyboard_state*) malloc(sizeof(struct keyboard_state));

	return state;
}

EXPORT void keyboard_deinitialize(struct keyboard_state* state) {
	keyboard_clear(state);
	
	free((void*) state);
}

void keyboard_key_set(struct keyboard_state* state, enum keyboard_ukey ukey, int updown) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0;
    input.ki.wScan = keyboard_ukey_to_dikey(ukey);
	input.ki.dwFlags = (updown == KEYBOARD_KEY_ISUP ? KEYEVENTF_KEYUP : 0);
	if (input.ki.wScan == keyboard_dikey_na) {
		// printscreen and break likely need KEYEVENTF_EXTENDED set
		input.ki.wScan = ukey;
		input.ki.dwFlags |= KEYEVENTF_UNICODE;
	} else {
		switch (input.ki.wScan) {
			// Catch all extended keys
		case keyboard_dikey_left:
		case keyboard_dikey_right:
		case keyboard_dikey_up:
		case keyboard_dikey_down:
		case keyboard_dikey_ctrl_r:
		case keyboard_dikey_alt_r:
		case keyboard_dikey_insert:
		case keyboard_dikey_delete:
		case keyboard_dikey_home:
		case keyboard_dikey_end:
		case keyboard_dikey_pgup:
		case keyboard_dikey_pgdn:
		case keyboard_dikey_numlock:
		case keyboard_dikey_numenter:
			input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
		}


		input.ki.dwFlags |= KEYEVENTF_SCANCODE;
	}

    input.ki.time = 0;
    input.ki.dwExtraInfo = (ULONG_PTR)NULL;

    if (SendInput(1, &input, sizeof(INPUT)) != 1) {
        windows_error("SendInput");
    }
}

EXPORT int keyboard_key_status(struct keyboard_state* state, enum keyboard_ukey ukey) {
	SHORT status = GetAsyncKeyState(ukey);
	if ((status & (1 << (sizeof(SHORT) - 1))) > 0) {
		return KEYBOARD_KEY_ISDOWN;
	} else {
		return KEYBOARD_KEY_ISUP;
	}
}

#endif//WINDOWS_OS
