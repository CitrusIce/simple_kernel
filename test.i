# 1 "init/main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "init/main.c"


# 1 "include/types.h" 1
# 13 "include/types.h"
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;

typedef int intptr_t;
typedef unsigned int size_t;
# 4 "init/main.c" 2
# 1 "include/monitor.h" 1


# 1 "include/types.h" 1
# 4 "include/monitor.h" 2
# 1 "include/common.h" 1



# 1 "include/monitor.h" 1
# 5 "include/common.h" 2


void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

void panic(const char *message, const char *file, uint32_t line);
void assert(int exp,const char* str);
# 5 "include/monitor.h" 2

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
# 5 "init/main.c" 2
# 1 "include/timer.h" 1





void init_timer(uint32_t frequency);
# 6 "init/main.c" 2
# 1 "include/descriptor_tables.h" 1
# 1 "include/gdt.h" 1




typedef struct gdt_entry_struct
{
 uint16_t limit_low;
 uint16_t base_low;
 uint8_t base_middle;
 uint8_t access;
 uint8_t granularity;
 uint8_t base_high;
}__attribute__((packed)) gdt_entry_t;


typedef struct gdt_ptr_struct
{
 uint16_t limit;
 uint32_t base;
}__attribute__((packed)) gdt_ptr_t;

void init_gdt();
# 2 "include/descriptor_tables.h" 2
# 1 "include/idt.h" 1



# 1 "include/memory.h" 1





uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);
# 5 "include/idt.h" 2


typedef struct idt_entry_struct
{
 uint16_t base_low;
 uint16_t sel;
 uint8_t always0;
 uint8_t flags;
 uint16_t base_high;
}__attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_struct
{
 uint16_t limit;
 uint32_t base;
}__attribute__((packed)) idt_ptr_t;

void init_idt();
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
# 3 "include/descriptor_tables.h" 2

void init_descriptor_tables();
# 7 "init/main.c" 2
# 1 "include/multiboot.h" 1
# 35 "include/multiboot.h"
typedef
struct multiboot_t {
 uint32_t flags;
# 46 "include/multiboot.h"
 uint32_t mem_lower;
 uint32_t mem_upper;

 uint32_t boot_device;
 uint32_t cmdline;
 uint32_t mods_count;
 uint32_t mods_addr;





 uint32_t num;
 uint32_t size;
 uint32_t addr;
 uint32_t shndx;






 uint32_t mmap_length;
 uint32_t mmap_addr;

 uint32_t drives_length;
 uint32_t drives_addr;
 uint32_t config_table;
 uint32_t boot_loader_name;
 uint32_t apm_table;
 uint32_t vbe_control_info;
 uint32_t vbe_mode_info;
 uint32_t vbe_mode;
 uint32_t vbe_interface_seg;
 uint32_t vbe_interface_off;
 uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;







typedef
struct mmap_entry_t {
 uint32_t size;
 uint32_t base_addr_low;
 uint32_t base_addr_high;
 uint32_t length_low;
 uint32_t length_high;
 uint32_t type;
} __attribute__((packed)) mmap_entry_t;



extern multiboot_t* mboot_ptr_tmp;


extern multiboot_t* glb_mboot_ptr;
# 8 "init/main.c" 2
# 1 "include/pmm.h" 1



# 1 "include/multiboot.h" 1
# 5 "include/pmm.h" 2
# 23 "include/pmm.h"
extern uint8_t kern_start[];
extern uint8_t kern_end[];


extern uint32_t phy_page_count;


void show_memory_map();


void init_pmm();


uint32_t pmm_alloc_page();


void pmm_free_page(uint32_t p);
# 9 "init/main.c" 2
# 1 "include/vmm.h" 1





# 1 "include/vmm.h" 1
# 7 "include/vmm.h" 2
# 1 "include/isr.h" 1


typedef struct registers
{
   uint32_t ds;
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   uint32_t int_no, err_code;
   uint32_t eip, cs, eflags, useresp, ss;
} registers_t;
typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler);
# 8 "include/vmm.h" 2
# 50 "include/vmm.h"
typedef uint32_t pgd_t;


typedef uint32_t pte_t;
# 65 "include/vmm.h"
extern pgd_t pgd_kern[(4096/sizeof(pte_t))];


void init_vmm();


void switch_pgd(uint32_t pd);


void map(pgd_t *pgd_now, uint32_t va, uint32_t pa, uint32_t flags);


void unmap(pgd_t *pgd_now, uint32_t va);



uint32_t get_mapping(pgd_t* pgd_now, uint32_t va, uint32_t *pa);


void page_fault(registers_t *regs);
# 10 "init/main.c" 2
# 1 "include/common.h" 1
# 11 "init/main.c" 2



char kern_stack[8192];


multiboot_t *glb_mboot_ptr;

extern multiboot_t* mboot_ptr_tmp;


__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low = (pgd_t *)0x2000; __attribute__((section(".init.data"))) pgd_t *pte_hign = (pgd_t *)0x3000;
int main();

__attribute__((section(".init.text")))void kernel_entry()
{
    pgd_tmp[0] = (uint32_t)pte_low | 0x1 | 0x2;
    pgd_tmp[(((0xC0000000) >> 22) & 0x3FF)] = (uint32_t)pte_hign | 0x1 | 0x2;


    int i;
    for (i = 0; i < 1024; i++) {
        pte_low[i] = (i << 12) | 0x1 | 0x2;
    }


    for (i = 0; i < 1024; i++) {
        pte_hign[i] = (i << 12) | 0x1 | 0x2;
    }


    asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));

    uint32_t cr0;


    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0" : : "r" (cr0));


    uint32_t kern_stack_top = ((uint32_t)kern_stack + 8192) & 0xFFFFFFF0;
    asm volatile ("mov %0, %%esp\n\t"
            "xor %%ebp, %%ebp" : : "r" (kern_stack_top));


    glb_mboot_ptr = mboot_ptr_tmp + 0xC0000000;


    main();
}

int main()
{

    init_descriptor_tables();
    clear();
    print("hello world!");
    print_num_dec(12345);

    init_timer(50);
    printk("kernel in memory start: 0x%08X\n", kern_start);
    printk("kernel in memory end:   0x%08X\n", kern_end);
    printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start + 1023) / 1024);
    show_memory_map();
    init_vmm();
    init_pmm();

    printk("\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

    uint32_t allc_addr = 0;
    printk("Test Physical Memory Alloc :\n");
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", allc_addr);
    while(1){}

    return 0xDEADBAB1;
}
