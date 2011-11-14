#include <stdbool.h>
#include <stdint.h>

typedef void *term_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	TERM_TYPE_VT100
} term_type;

// Attributes
#define TERM_ATTRIB_BOLD		(1<<0)
#define TERM_ATTRIB_UNDERSCORE	(1<<1)
#define TERM_ATTRIB_BLINK		(1<<2)
#define TERM_ATTRIB_REVERSE		(1<<3)
#define TERM_ATTRIB_CONCEALED	(1<<4)

// Create a terminal object with the specified dimensions. Scrollback
// indicates the number of lines to be preserved after they have scrolled
// off the display
bool term_create(term_t *handle);

// Specify what type of terminal to emulate
bool term_set_emulation(term_t handle, term_type type);

// Set the shell to use
bool term_set_shell(term_t handle, char *shell);

// Begin a terminal session. Set up all parameters before calling this function
bool term_begin( term_t handle, int width, int height, int scrollback );

// Functions to set and get an opaque blob of data attached to the terminal instance
void term_set_user_data(term_t handle, void *user_data);
void *term_get_user_data(term_t handle);

// Callback functions for when the screen state changes
void term_register_update(term_t handle, void (*update)(term_t handle, int x, int y, int width, int height));

// Get a file descriptor to wait for data from the child process. Waiting on
// this file handle should be integrated in the programs event processing loop
int term_get_file_descriptor(term_t handle);

// Retrieve the grid of characters
const uint32_t **term_get_grid(term_t handle);
const uint32_t **term_get_attribs(term_t handle);
const uint32_t **term_get_colours(term_t handle);

// This function should be called to process data from the child process
bool term_process_child(term_t handle);

// Send input to the shell
void term_send_data(term_t handle, const char *string, int length);

// Release all resources associated with a terminal
void term_free(term_t handle);

#ifdef __cplusplus
}
#endif