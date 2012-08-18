#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "mouse.h"
#include "keyboard.h"
#include "system.h"

#define DEVICE_LENGTH 33
#define ACTION_LENGTH 33
#define OPTIONS_LENGTH 129

#define BUFFER_LENGTH DEVICE_LENGTH + ACTION_LENGTH + OPTIONS_LENGTH + 30

#define MACRO_STRINGIFY(str) #str
#define MACRO_STRING(str) MACRO_STRINGIFY(str)

#define COMMENT_SYMBOL '#'

#define ARRAY_GEOMETRIC_EXPANSION 2

#define _MACRO_ENUM(pre, x) pre##_##x,
#define _MACRO_STRUCT(pre, x) {pre##_##x, #x},

#define MACRO_ENUM(pre) enum pre##_option { pre##_LIST(_MACRO_ENUM) pre##_option_count}

#define MACRO_STRUCT(pre) struct { enum pre##_option type; char* name; } pre##_list[] = { pre##_LIST(_MACRO_STRUCT) }

#define NAMED_ENUM(pre) \
	MACRO_ENUM(pre); \
	MACRO_STRUCT(pre);

#define device_LIST(f) \
	f(device, system) \
	f(device, keyboard) \
	f(device, mouse) \
	f(device, goto)

#define system_LIST(f) \
	f(system, wait)

#define keyboard_LIST(f) \
	f(keyboard, press) \
	f(keyboard, release) \
	f(keyboard, click) \
	f(keyboard, type)

#define mouse_LIST(f) \
	f(mouse, press) \
	f(mouse, release) \
	f(mouse, click) \
	f(mouse, move) \
	f(mouse, moveto) \
	f(mouse, scroll) \
	f(mouse, clear)

NAMED_ENUM(device);
NAMED_ENUM(system);
NAMED_ENUM(keyboard);
NAMED_ENUM(mouse);



struct command {
	device_option device;
	union {
		char action_text[ACTION_LENGTH];
		int action_value;
	};
	union {
		char options_text[OPTIONS_LENGTH];
		int options_value;
	};
};

struct label {
	const char* name;
	int line;
};

// Ideally a hash table or something would be used, but realistically there shouldn't be enough labels to matter
struct label_table {
	struct label** labels;
	size_t length;
	size_t _alloc_length;
};

struct script {
	char* name;

	struct command** commands;
	size_t length;
	size_t _alloc_length;

	struct label_table* table;
};

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

void grow_array(void** array, size_t element_size, size_t* length, size_t* alloc_length) {
	if (*length >= *alloc_length) {
		*alloc_length *= ARRAY_GEOMETRIC_EXPANSION;
		void* new_array = (void*)malloc(element_size * *alloc_length);
		memcpy(new_array, *array, element_size * *length);
		free(*array);
		*array = new_array;
	}
}

void add_command(struct script* scr, struct command* com) {
	grow_array((void**) &scr->commands, sizeof(struct command*), &scr->length, &scr->_alloc_length);
	scr->commands[++scr->length] = com;
}

void add_label(struct label_table* table, struct label* l) {
	grow_array((void**)&table->labels, sizeof(label*), &table->length, &table->_alloc_length);
	table->labels[table->length] = l;
}

int label_to_line(struct label_table* table, const char* l) {
	int i;
	char* lcopy;

	lcopy = (char*)malloc(sizeof(char) * (strlen(l) + 1));
	strcpy(lcopy, l);

	str_tolower(lcopy);

	for (int i = 0; i < table->length; ++i) {
		if (strcmp(lcopy, table->labels[i]->name) == 0) {
			return table->labels[i]->line;
		}
	}

	return -1;
}

struct pair {
	int x;
	int y;
};

// TODO worry about buffer overflows and exploits



void cleanup(void);

struct pair parse_mouse_direction(const char* button);
int parse_mouse_button(const char* button);
enum keyboard_ukey parse_keyboard_key(const char* key);

void parse_mouse(struct script* scr, struct command* com, const char* action, const char* options);
void parse_keyboard(struct script* scr, struct command* com, const char* action, const char* options);
void parse_system(struct script* scr, struct command* com, const char* action, const char* options);
void parse_goto(struct script* scr, struct command* com, const char* action, const char* options);

void parse_label(struct script* scr, const char* action);

void generate_label(struct script* scr, const char* label);

struct command* parse_line(const char* line);

void read_file(FILE* file, script* scr);

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
		script scr;
		scr.length = 0;
		scr._alloc_length = 20;
		scr.commands = (struct command**)malloc(sizeof(struct command*) * scr._alloc_length);
		scr.table = (struct label_table*)malloc(sizeof(struct label_table));
		scr.table->length = 0;
		scr.table->_alloc_length = 5;
		scr.table->labels = (struct label**)malloc(sizeof(struct label*) * scr.table->_alloc_length);
		
		if (file == NULL) {
			//fprintf(stderr, "Could not open file '%s'\n", argv[i]);
			perror("Error opening file");
			continue;
		}
		scr.name = (char*)malloc(sizeof(char)*(strlen(argv[i]) + 1));

		printf("Running file '%s'...\n", argv[i]);
		

		read_file(file, &scr);

		// EOF won't trigger line break (on Windows?)
		printf("\n");
	}
	
	return 0;
}

void read_file(FILE* file, struct script* scr) {
	char buffer[BUFFER_LENGTH];
	
	while (fgets(buffer, BUFFER_LENGTH, file) != NULL) {
		struct command* com;
		printf(">%s", buffer);
		
		com = parse_line(scr, buffer);

		add_command(scr, com);
	}
	
	if (ferror(file) != 0) {
		perror("Error reading file");
		return;
	}		
}

struct command* parse_line(struct script* scr, const char* line) {
	char device[DEVICE_LENGTH];
	char action[ACTION_LENGTH];
	char options[OPTIONS_LENGTH];
	struct command* com;

	int i;

	if (line[0] == '\0' || line[0] == COMMENT_SYMBOL) {
		return NULL;
	}
	
	sscanf(line, "%"MACRO_STRING(DEVICE_LENGTH)"s %"MACRO_STRING(ACTION_LENGTH)"s %"MACRO_STRING(OPTIONS_LENGTH)"[^\n]", device, action, options);
	
	str_tolower(device);
	str_tolower(action);

	if (strcmp(device, "label")) {
		generate_label(scr, action);
		return NULL;
	}

	com = (struct command*)malloc(sizeof(struct command));

	for (i = 0; i < device_option_count; ++i) {
		if (strcmp(device, device_list[i].name) == 0) {
			com->device = device_list[i].type;
			break;
		}
	}
	if (i == device_option_count) {
		fprintf(stderr, "Unknown device '%s'\n", device);
		exit(EXIT_FAILURE);
	}

	switch (com->device) {
	case device_system:
		parse_system(src, com, action, options);
	case device_keyboard:
		parse_keyboard(src, com, action, options);
	case device_mouse:
		parse_mouse(src, com, action, options);
	case device_goto:
		parse_goto(src, com, action, options);
	}

	return com;
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

void parse_mouse(struct script* scr, struct command* com, const char* action, const char* options) {
	char action_copy[ACTION_LENGTH];
	char options_copy[OPTIONS_LENGTH];
	int i;
	
	if (m_state == NULL) {
		m_state = mouse_initialize();
	}

	strcpy(action_copy, action);
	strcpy(options_copy, options);

	str_tolower(action_copy);
	str_tolower(options_copy);

	for (i = 0; i < mouse_option_count; ++i) {
		if (strcmp(action, mouse_list[i].name) == 0) {
			com->action_value = mouse_list[i].type;
			break;
		}
	}
	if (i == mouse_option_count) {
		fprintf(stderr, "Unknown mouse action '%s'\n", action);
		exit(EXIT_FAILURE);
	}

	switch (com->action_value) {
	case mouse_move:
		{
			int x, y;
			if (sscanf(options, "%i %i", &x, &y) != 2) {
				fprintf(stderr, "Invalid options '%s'\n", options);
				return;
			}
			mouse_move(m_state, x, y);
		} break;
	case mouse_moveto:
		{
			int x, y;
			if (sscanf(options, "%i %i", &x, &y) != 2) {
				fprintf(stderr, "Invalid options '%s'\n", options);
				return;
			}
			mouse_moveto(m_state, x, y);
		} break;
	case mouse_press:
		{
			char button[32];
			if (sscanf(options, "%s", &button) != 1) {
				fprintf(stderr, "Invalid options '%s'\n", options);
				return;
			}
		
			mouse_button_press(m_state, parse_mouse_button(button));
		} break;
	case mouse_release:
		{
			char button[32];
			if (sscanf(options, "%s", &button) != 1) {
				fprintf(stderr, "Invalid options '%s'\n", options);
				return;
			}
		
			mouse_button_release(m_state, parse_mouse_button(button));
		} break;
	case mouse_click:
		{
			char button[32];
			if (sscanf(options, "%s", &button) != 1) {
				fprintf(stderr, "Invalid options '%s'\n", options);
				return;
			}
		
			mouse_button_click(m_state, parse_mouse_button(button));
		} break;
	case mouse_scroll:
		{
			char direction[32];
			struct pair p;

			if (sscanf(options, "%s", &direction) != 1) {
				fprintf(stderr, "Invalid options '%s'\n", options);
				return;
			}

			p = parse_mouse_direction(direction);

			mouse_scroll(m_state, p.x, p.y);
		} break;
	case mouse_clear:
		mouse_clear(m_state);
		break;
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

void parse_goto(struct script* scr, const char* action, char* options) {
	struct command* com = (struct command*)malloc(sizeof(struct command));
	int line;
	char label[ACTION_LENGTH];

	com->device = device_goto;

	// Use options_value to indicate whether the label destination has been found yet
	// Hackish, but allows for a single-pass approach
	com->options_value = 0;
	if (sscanf(action, "%u", &line) == 1) {
		com->action_value = line;
	} else if (sscanf(action, "%s", label) == 1) {
		line = label_to_line(scr->table, label);
		if (line == -1) {
			char* c = (char*)malloc(sizeof(char) * (strlen(label) + 1));
			com->action_text = c;
			com->options_value = 1;
		} else {
			com->action_value = line;
		}
	} else {
		fprintf(stderr, "Invalid line number or label '%s'\n", action);
		exit(EXIT_FAILURE);
	}
}

void parse_label(struct script* scr, const char* action) {
	struct label* l;
	char* name;
	int dummy;

	name = (char*)malloc(sizeof(char) * strlen(action));
	str_tolower(name);
	if (label_to_line(scr->table, name) != -1) {
		// Label already exists
		fprintf(stderr, "Duplicate label '%s' (Labels are not case-sensitive)\n", action);
		exit(EXIT_FAILURE);
	} else if (sscanf(action, "%i", &dummy) == 1) {
		// Label name begins with a number
		fprintf(stderr, "Invalid label name '%s'\n", action);
		exit(EXIT_FAILURE);
	} else {
		l = (label*)malloc(sizeof(label));
		l->line = scr->length;
		l->name = name;
		add_label(scr->table, l);
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
