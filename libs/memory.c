#include "memory.h"

uint32_t placement_address;

void memset(void* s, uint8_t ch, size_t n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        ((uint8_t*)s)[i] = ch;
    }
}

uint32_t kmalloc(uint32_t sz)
{
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}


uint32_t kmalloc_a(uint32_t sz)
{
    uint32_t tmp;
    if(placement_address & ~0xFFFF000)
    {
        placement_address &= 0xFFFF000;
        placement_address += 0x1000;
    }
    tmp = placement_address;
    placement_address += sz;
    return tmp;
}
uint32_t kmalloc_p(uint32_t sz,uint32_t* phys)
{
    uint32_t tmp;
	*phys=placement_address;
    tmp = placement_address;
    placement_address += sz;
    return tmp;

}
uint32_t kmalloc_ap(uint32_t sz,uint32_t* phys)
{
    uint32_t tmp;
    if(placement_address & ~0xFFFF000)
    {
        placement_address &= 0xFFFF000;
        placement_address += 0x1000;
    }
	*phys=placement_address;
    tmp = placement_address;
    placement_address += sz;
    return tmp;
}
