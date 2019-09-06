#ifndef _INCLUDE_MEMORY_
#define _INCLUDE_MEMORY_
#include "types.h" 

// void memset(void *s,uint8_t ch,size_t n);
uint32_t kmalloc_a(uint32_t sz);  // page aligned.
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys); // returns a physical address.
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys); // page aligned and returns a physical address.
uint32_t kmalloc(uint32_t sz); // vanilla (normal).
#endif
