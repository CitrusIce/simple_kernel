// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials
#include "types.h"
#include "monitor.h"
#include "timer.h"
#include "descriptor_tables.h"
#include "multiboot.h"
#include "pmm.h"

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}
//int main(struct multiboot *mboot_ptr)
int main(multiboot_t* mboot)
{
    glb_mboot_ptr = mboot;
    init_descriptor_tables();
    clear();
    print("hello world!");
    print_num_dec(12345);
    // asm volatile ("int $0x0");
    init_timer(50);
    printk("kernel in memory start: 0x%08X\n", kern_start);
    printk("kernel in memory end:   0x%08X\n", kern_end);
    printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start + 1023) / 1024);
    show_memory_map();
    init_pmm();
    printk("\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

    uint32_t allc_addr = NULL;
    printk("Test Physical Memory Alloc :\n");
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    // asm volatile ("sti");
    return 0xDEADBAB1;
}
