#ifndef _INCLUDE_MONITOR_
#define _INCLUDE_MONITOR_
#include "types.h"
#include "common.h"

extern uint16_t * const video_memory;
extern const int screen_width;
extern const int screen_height;
extern const int default_color;
int cursor_x;
int cursor_y;

void print_char(char c);
void print(const char * text);
void print_num_dec(int num);
void print_num_hex(int num);
void printk(const char *format, ...);
void clear();
#endif
