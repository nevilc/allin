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

// TODO worry about buffer exploits

void str_tolower(char* str) {
	int i;
	for (i = 0; str[i] != '\0'; ++i) {
		str[i] = tolower(str[i]);
	}
}

void cleanup(void);

int parse_mouse_button(const char* button);
enum keyboard_ukey parse_keyboard_key(const char* key);

void parse_mouse(const char* action, const char* options);
void parse_keyboard(const char* action, const char* options);
void parse_system(const char* action, const char* options);

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
	str_tolower(options);
	
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

int parse_mouse_button(const char* button) {
	// TODO add numerical button codes?
	int buttonval;
	char buttonname[32];
	if (sscanf(button, "%s", buttonname) == 1) {
		str_tolower(buttonname);
	
		if (strcmp(button, "left") == 0) {
			buttonval = MOUSE_BUTTON_LEFT;
		} else if (strcmp(button, "right") == 0) {
			buttonval = MOUSE_BUTTON_RIGHT;
		} else if (strcmp(button, "middle") == 0) {
			buttonval = MOUSE_BUTTON_MIDDLE;
		} else if (strcmp(button, "4") == 0) { 
			buttonval = MOUSE_BUTTON_4;
		} else if (strcmp(button, "5") == 0) {
			buttonval = MOUSE_BUTTON_5;
		} else {
			buttonval -1;
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
	printf("Key: %x\n", keyval);
	return (enum keyboard_ukey) keyval;
}

void parse_mouse(const char* action, const char* options) {
	if (m_state == NULL) {
		m_state = mouse_initialize();
	}
	
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
	} else if (strcmp(action, "clear") == 0) {
		mouse_clear(m_state);
	} else {
		fprintf(stderr, "Unknown mouse action '%s'\n", action);
		return;
	}
}

void parse_keyboard(const char* action, const char* options) {
	if (k_state == NULL) {
		k_state = keyboard_initialize();
	}
	if (strcmp(action, "press") == 0) {
		keyboard_key_press(k_state, parse_keyboard_key(options));
	} else if (strcmp(action, "release") == 0) {
		keyboard_key_saferelease(k_state, parse_keyboard_key(options));
	} else if (strcmp(action, "click") == 0) {
		keyboard_key_click(k_state, parse_keyboard_key(options));
	} else  {
		fprintf(stderr, "Unknown keyboard action '%s'\n", action);
		return;
	}
}

void parse_system(const char* action, const char* options) {
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