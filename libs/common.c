#include "common.h"
// 内核的偏移地址
inline void outb(uint16_t port, uint8_t value)
{
    // asm volatile ("outb %1, %0" : : "dN" (addr), "a" (value));
    asm volatile(
        "outb %1,%0"
        :
        :"d"(port), "a"(value)
    );
}
inline uint8_t inb(uint16_t port)
{
    uint8_t value;
    asm volatile(
        "inb %1,%0"
        :"=a"(value)
        :"dN"(port)
    );
    return value;
}

void panic(const char *message, const char *file, uint32_t line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    print("PANIC(");
    print(message);
    print(") at ");
    print(file);
    print(":");
    print_num_dec(line);
    print("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
void assert(int exp,const char* str)
{
	if(exp!=1)
		print(str);
}
