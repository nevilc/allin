#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "mouse.h"
#include "keyboard.h"
#include "system.h"

#define BUFFER_LENGTH 256

#define COMMENT_SYMBOL '#'

struct command {
	char device[32];
	char action[32];
	char options[128];
};

struct pair {
	int x;
	int y;
};

// TODO worry about buffer overflows and exploits

void str_tolower(char* str) {
	int i;
	for (i = 0; str[i] != '\0'; ++i) {
		str[i] = tolower(str[i]);
	}
}

size_t str_ascii_to_unicode(const char* astr, enum keyboard_ukey* ustr) {
	// takes an ascii string and places Unicode conversion into preallocated buffer
	// astr - ASCII string
	// ustr - Unicode buffer
	//			Unicode string is guaranteed to be no longer than the ASCII string, 
	//			so making the buffer equal length is recommended
	// returns -1 on improper escape sequences

	// name is slightly misleading
	// in addition to widening ASCII, it handles escaped ('\')
	// sequences, especially for unicode characters ('\uXXXX')
	// returns the length of the unicode string
	int a;
	int u = 0;
	for (a = 0; astr[a] != '\0'; ++a) {
		if (astr[a] == '\\') {
			switch (astr[++a]) {
			case '\0':
				fprintf(stderr, "Unexpected end of string. (Trailing backslash)\n");
				return -1;
			case '\\':
				// Escaped backslash
				ustr[u++] = (enum keyboard_ukey)'\\';
				break;
			case 'n':
				// Newline
				ustr[u++] = (enum keyboard_ukey)'\n';
				break;
			case 'u':
				// Unicode character
				// Must be in the format '\uXXXX'
				{
					int i;
					ustr[u] = (enum keyboard_ukey)0;
					for (i = 0, ++a; i < 4; ++i, ++a) {
						char c = astr[a];
						if (c == '\0') {
							fprintf(stderr, "Unexpected end of string. (Incomplete Unicode sequence)\n");
							return -1;
						}
						if (c >= '0' || c <= '9') {
							c -= '0';
						} else if (c >= 'a' || c <= 'f') {
							c -= 'a' - 10;
						} else if (c < 'A' || c <= 'F') {
							c -= 'A' - 10;
						} else {
							fprintf(stderr, "Unexpected character '%c' in Unicode sequence.\n", c);
							return -1;
						}
					
						ustr[u] *= (enum keyboard_ukey)16;
						ustr[u] += (enum keyboard_ukey)c;
					}
					++u;
					--a;
				}
				break;
			default:
				fprintf(stderr, "Unknown escape sequence '\\%c'.\n", astr[a]);
				break;
			}
			continue;
		}
		ustr[u++] = (enum keyboard_ukey)astr[a];
	}
	ustr[u] = (enum keyboard_ukey)'\0';
	return u;
}

void cleanup(void);

struct pair parse_mouse_direction(const char* button);
int parse_mouse_button(const char* button);
enum keyboard_ukey parse_keyboard_key(const char* key);

void parse_mouse(const char* action, char* options);
void parse_keyboard(const char* action, char* options);
void parse_system(const char* action, char* options);

void parse_line(const char* line);

void read_file(FILE* file);

struct mouse_state* m_state = NULL;
struct keyboard_state* k_state = NULL;

int main(int argc, char** argv) {
	int i;

	if (argc == 1) {
		printf("Usage: %s FILE [FILE2]...\n", argv[0]);
		return 0;
	}
	
	atexit(&cleanup);
	
	for (i = 1; i < argc; ++i) {
		FILE* file = fopen(argv[i], "r");
		
		if (file == NULL) {
			//fprintf(stderr, "Could not open file '%s'\n", argv[i]);
			perror("Error opening file");
			continue;
		}
		printf("Running file '%s'...\n", argv[i]);
		
		read_file(file);

		// EOF won't trigger line break (on Windows?)
		printf("\n");
	}
	
	return 0;
}

void read_file(FILE* file) {
	char buffer[BUFFER_LENGTH];
	
	while (fgets(buffer, BUFFER_LENGTH, file) != NULL) {
		printf(">%s", buffer);
		parse_line(buffer);
	}
	
	if (ferror(file) != 0) {
		perror("Error reading file");
		return;
	}		
}

void parse_line(const char* line) {
	char input[32];
	char action[32];
	char options[128];

	if (line[0] == '\0' || line[0] == COMMENT_SYMBOL) {
		return;
	}
	
	sscanf(line, "%s %s %[^\n]", input, action, options);
	
	str_tolower(input);
	str_tolower(action);
	// options may be case-sensitive
	//str_tolower(options);
	
	if (strcmp(input, "mouse") == 0) {
		parse_mouse(action, options);
	} else if (strcmp(input, "keyboard") == 0) {
		parse_keyboard(action, options);
	} else if (strcmp(input, "system") == 0) {
		parse_system(action, options);
	} else {
		fprintf(stderr, "Unknown input '%s'\n", input);
		return;
	}
	
}

struct pair parse_mouse_direction(const char* direction) {
	struct pair p = {0};
	int invalid = 0;

	char directionname[32];
	if (sscanf(direction, "%s", directionname) == 1) {
		str_tolower(directionname);
	
		if (strcmp(directionname, "left") == 0) {
			p.x = -1;
		} else if (strcmp(directionname, "right") == 0) {
			p.x = 1;
		} else if (strcmp(directionname, "up") == 0) {
			p.y = -1;
		} else if (strcmp(directionname, "down") == 0) { 
			p.y = 1;
		} else {
			invalid = 1;
		}
	} else {
		invalid = 1;
	}

	if (invalid) {
		fprintf(stderr, "Invalid scroll direction '%s'\n", direction);
	}

	return p;
}

int parse_mouse_button(const char* button) {
	// TODO add numerical button codes?
	int buttonval;
	char buttonname[32];
	if (sscanf(button, "%s", buttonname) == 1) {
		str_tolower(buttonname);
	
		if (strcmp(buttonname, "left") == 0) {
			buttonval = MOUSE_BUTTON_LEFT;
		} else if (strcmp(buttonname, "right") == 0) {
			buttonval = MOUSE_BUTTON_RIGHT;
		} else if (strcmp(buttonname, "middle") == 0) {
			buttonval = MOUSE_BUTTON_MIDDLE;
		} else if (strcmp(buttonname, "4") == 0) { 
			buttonval = MOUSE_BUTTON_4;
		} else if (strcmp(buttonname, "5") == 0) {
			buttonval = MOUSE_BUTTON_5;
		} else {
			buttonval = -1;
		}
	} else {
		buttonval = -1;
	}

	if (buttonval == -1) {
		fprintf(stderr, "Invalid mouse button '%s'\n", button);
	}
	return buttonval;
}

enum keyboard_ukey parse_keyboard_key(const char* key) {
	int keyval;
	char keyname[32];
	char keychar;

	if (sscanf(key, "%x", &keyval) == 1) {
		// successful unicode hex match
		// nothing else must be done
	} else if (sscanf(key, "%c%c", &keychar, &keychar) == 1) {
		// single ASCII character match
		// only succeed if there is a single character in the line
		keyval = (int) keychar;
	} else if (sscanf(key, "%s", keyname) == 1) {
		str_tolower(keyname);
		if (strcmp(keyname, "left") == 0) {
			keyval = keyboard_ukey_left;
		} else if (strcmp(keyname, "right") == 0) {
			keyval = keyboard_ukey_right;
		} else if (strcmp(keyname, "up") == 0) {
			keyval = keyboard_ukey_up;
		} else if (strcmp(keyname, "down") == 0) {
			keyval = keyboard_ukey_down;
		} else {
			keyval = -1;
		}
	} else {
		keyval = -1;
	}

	if (keyval == -1) {
		fprintf(stderr, "Invalid keyboard key '%s'\n", key);
	}
	return (enum keyboard_ukey) keyval;
}

void parse_mouse(const char* action, char* options) {
	if (m_state == NULL) {
		m_state = mouse_initialize();
	}

	str_tolower(options);
	
	if (strcmp(action, "move") == 0) {
		int x, y;
		if (sscanf(options, "%i %i", &x, &y) != 2) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}
		mouse_move(m_state, x, y);
	} else if (strcmp(action, "moveto") == 0) {
		int x, y;
		if (sscanf(options, "%i %i", &x, &y) != 2) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}
		mouse_moveto(m_state, x, y);
	} else if (strcmp(action, "press") == 0) {
		char button[32];
		if (sscanf(options, "%s", &button) != 1) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}
		
		mouse_button_press(m_state, parse_mouse_button(button));
	} else if (strcmp(action, "release") == 0) {
		char button[32];
		if (sscanf(options, "%s", &button) != 1) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}
		
		mouse_button_release(m_state, parse_mouse_button(button));
	} else if (strcmp(action, "click") == 0) {
		char button[32];
		if (sscanf(options, "%s", &button) != 1) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}
		
		mouse_button_click(m_state, parse_mouse_button(button));
	} else if (strcmp(action, "scroll") == 0) {
		char direction[32];
		struct pair p;

		if (sscanf(options, "%s", &direction) != 1) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}

		p = parse_mouse_direction(direction);

		mouse_scroll(m_state, p.x, p.y);
	} else if (strcmp(action, "clear") == 0) {
		mouse_clear(m_state);
	} else {
		fprintf(stderr, "Unknown mouse action '%s'\n", action);
		return;
	}
}

void parse_keyboard(const char* action, char* options) {
	if (k_state == NULL) {
		k_state = keyboard_initialize();
	}
	if (strcmp(action, "press") == 0) {
		str_tolower(options);
		keyboard_key_press(k_state, parse_keyboard_key(options));
	} else if (strcmp(action, "release") == 0) {
		str_tolower(options);
		keyboard_key_saferelease(k_state, parse_keyboard_key(options));
	} else if (strcmp(action, "click") == 0) {
		str_tolower(options);
		keyboard_key_click(k_state, parse_keyboard_key(options));
	} else if (strcmp(action, "type") == 0) {
		enum keyboard_ukey* kstring;

		kstring = (enum keyboard_ukey*)malloc(sizeof(enum keyboard_ukey) * (strlen(options) + 1));

		str_ascii_to_unicode(options, kstring);

		keyboard_type(k_state, kstring);
	} else {
		fprintf(stderr, "Unknown keyboard action '%s'\n", action);
		return;
	}
}

void parse_system(const char* action, char* options) {
	str_tolower(options);

	if (strcmp(action, "sleep") == 0) {
		int mseconds;
		if (sscanf(options, "%i", &mseconds) != 1) {
			fprintf(stderr, "Invalid options '%s'\n", options);
			return;
		}
		system_sleep(NULL, mseconds);
	} else {
		fprintf(stderr, "Unknown system action '%s'\n", action);
		return;
	}
}

void cleanup(void) {
	if (m_state != NULL) {
		mouse_deinitialize(m_state);
	}
	if (k_state != NULL) {
		keyboard_deinitialize(k_state);
	}
}