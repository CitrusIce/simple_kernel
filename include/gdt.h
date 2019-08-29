#ifndef _INCLUDE_GDT_
#define _INCLUDE_GDT_
#include "types.h"

typedef struct gdt_entry_struct
{
	uint16_t limit_low;           // The lower 16 bits of the limit.
	uint16_t  base_low;            // The lower 16 bits of the base.
	uint8_t  base_middle;         // The next 8 bits of the base.
	uint8_t  access;              // Access flags, determine what ring this segment can be used in.
	uint8_t  granularity;
	uint8_t  base_high;           // The last 8 bits of the base.
}__attribute__((packed)) gdt_entry_t;


typedef struct gdt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed)) gdt_ptr_t;

void init_gdt();
#endif
