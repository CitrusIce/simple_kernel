#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H
#include "types.h"
#include "monitor.h"
#define PANIC(msg) panic(msg, __FILE__, __LINE__);
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

void panic(const char *message, const char *file, uint32_t line);
void assert(int exp,const char* str);
#endif
