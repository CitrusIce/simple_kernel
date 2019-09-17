// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials
#include "types.h"
#include "monitor.h"
#include "timer.h"
#include "descriptor_tables.h"
#include "multiboot.h"
#include "pmm.h"
#include "vmm.h"
#include "common.h"
#include "heap.h"
#include "task.h"
#include "scheduler.h"


// 开启分页机制之后的内核栈
char kern_stack[STACK_SIZE];

// 开启分页机制之后的 Multiboot 数据指针
multiboot_t *glb_mboot_ptr;
//tmp
extern multiboot_t* mboot_ptr_tmp;
// 内核使用的临时页表和页目录
// 该地址必须是页对齐的地址，内存 0-640KB 肯定是空闲的
__attribute__((section(".init.data"))) pgd_t *pgd_tmp  = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low  = (pgd_t *)0x2000; __attribute__((section(".init.data"))) pgd_t *pte_hign = (pgd_t *)0x3000;
int main();

uint32_t kern_stack_top;
//int main(struct multiboot *mboot_ptr)
__attribute__((section(".init.text")))void kernel_entry()
{
    pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
    pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_hign | PAGE_PRESENT | PAGE_WRITE;

    // 映射内核虚拟地址 4MB 到物理地址的前 4MB
    int i;
    for (i = 0; i < 1024; i++) {
        pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
    }

    // 映射 0x00000000-0x00400000 的物理地址到虚拟地址 0xC0000000-0xC0400000
    for (i = 0; i < 1024; i++) {
        pte_hign[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
    }
    
    // 设置临时页表
    asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));

    uint32_t cr0;

    // 启用分页，将 cr0 寄存器的分页位置为 1 就好
    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0" : : "r" (cr0));
    
    // 切换内核栈
    kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE) & 0xFFFFFFF0;
    asm volatile ("mov %0, %%esp\n\t"
            "xor %%ebp, %%ebp" : : "r" (kern_stack_top));

    // 更新全局 multiboot_t 指针
    glb_mboot_ptr = (multiboot_t*)((uint32_t)mboot_ptr_tmp + 0xc0000000);

    // 调用内核初始化函数
    main();   
}

int flag = 0;

int thread(void *arg)
{
    while (1) {
        if (flag == 1) {
            printk( "B");
            flag = 0;
        }
    }

    return 0;
}



int main()
{
    // glb_mboot_ptr = mboot;
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
    init_vmm();

    init_sched();
    
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

    test_heap();
    kernel_thread(thread,NULL);
    asm volatile ("sti");
    while (1) {
        if (flag == 0) {
            printk( "A");
            flag = 1;
        }
    }
    while(1){}
    return 0xDEADBAB1;
}
