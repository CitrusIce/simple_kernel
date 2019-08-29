#include "idt.h"


idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void idt_flush(uint32_t);

static void idt_set_gate(
    uint8_t,
    uint32_t,
    uint16_t,
    uint8_t
);


void init_idt()
{
    // 重新映射 IRQ 表
    // 两片级联的 Intel 8259A 芯片
    // 主片端口 0x20 0x21
    // 从片端口 0xA0 0xA1
        
    // 初始化主片、从片
    // 0001 0001
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    
    // 设置主片 IRQ 从 0x20(32) 号中断开始
    outb(0x21, 0x20);

    // 设置从片 IRQ 从 0x28(40) 号中断开始
    outb(0xA1, 0x28);
    
    // 设置主片 IR2 引脚连接从片
    outb(0x21, 0x04);

    // 告诉从片输出引脚和主片 IR2 号相连
    outb(0xA1, 0x02);
    
    // 设置主片和从片按照 8086 的方式工作
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    
    // 设置主从片允许中断
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (int)idt_entries;
    memset(idt_entries, 0, sizeof(idt_entry_t) * 256);
	idt_set_gate(0,(uint32_t)isr1,0x8,0x8E);
	idt_set_gate(1,(uint32_t)isr2,0x8,0x8E);
	idt_set_gate(2,(uint32_t)isr3,0x8,0x8E);
	idt_set_gate(3,(uint32_t)isr4,0x8,0x8E);
	idt_set_gate(4,(uint32_t)isr5,0x8,0x8E);
	idt_set_gate(5,(uint32_t)isr6,0x8,0x8E);
	idt_set_gate(6,(uint32_t)isr7,0x8,0x8E);
	idt_set_gate(7,(uint32_t)isr8,0x8,0x8E);
	idt_set_gate(9,(uint32_t)isr9,0x8,0x8E);
	idt_set_gate(10,(uint32_t)isr10,0x8,0x8E);
	idt_set_gate(11,(uint32_t)isr11,0x8,0x8E);
	idt_set_gate(12,(uint32_t)isr12,0x8,0x8E);
	idt_set_gate(13,(uint32_t)isr13,0x8,0x8E);
	idt_set_gate(14,(uint32_t)isr14,0x8,0x8E);
	idt_set_gate(15,(uint32_t)isr15,0x8,0x8E);
	idt_set_gate(16,(uint32_t)isr16,0x8,0x8E);
	idt_set_gate(17,(uint32_t)isr17,0x8,0x8E);
	idt_set_gate(18,(uint32_t)isr18,0x8,0x8E);
	idt_set_gate(19,(uint32_t)isr19,0x8,0x8E);
	idt_set_gate(20,(uint32_t)isr20,0x8,0x8E);
	idt_set_gate(21,(uint32_t)isr21,0x8,0x8E);
	idt_set_gate(22,(uint32_t)isr22,0x8,0x8E);
	idt_set_gate(23,(uint32_t)isr23,0x8,0x8E);
	idt_set_gate(24,(uint32_t)isr24,0x8,0x8E);
	idt_set_gate(25,(uint32_t)isr25,0x8,0x8E);
	idt_set_gate(26,(uint32_t)isr26,0x8,0x8E);
	idt_set_gate(27,(uint32_t)isr27,0x8,0x8E);
	idt_set_gate(28,(uint32_t)isr28,0x8,0x8E);
	idt_set_gate(29,(uint32_t)isr29,0x8,0x8E);
	idt_set_gate(30,(uint32_t)isr30,0x8,0x8E);
	idt_set_gate(31,(uint32_t)isr31,0x8,0x8E);
	idt_set_gate(32,(uint32_t)irq0,0x8,0x8E);
	idt_set_gate(33,(uint32_t)irq1,0x8,0x8E);
	idt_set_gate(34,(uint32_t)irq2,0x8,0x8E);
	idt_set_gate(35,(uint32_t)irq3,0x8,0x8E);
	idt_set_gate(36,(uint32_t)irq4,0x8,0x8E);
	idt_set_gate(37,(uint32_t)irq5,0x8,0x8E);
	idt_set_gate(38,(uint32_t)irq6,0x8,0x8E);
	idt_set_gate(39,(uint32_t)irq7,0x8,0x8E);
	idt_set_gate(40,(uint32_t)irq8,0x8,0x8E);
	idt_set_gate(41,(uint32_t)irq9,0x8,0x8E);
	idt_set_gate(42,(uint32_t)irq10,0x8,0x8E);
	idt_set_gate(43,(uint32_t)irq11,0x8,0x8E);
	idt_set_gate(44,(uint32_t)irq12,0x8,0x8E);
	idt_set_gate(45,(uint32_t)irq13,0x8,0x8E);
	idt_set_gate(46,(uint32_t)irq14,0x8,0x8E);
	idt_set_gate(47,(uint32_t)irq15,0x8,0x8E);
	idt_flush((int)&idt_ptr);
}
static void idt_set_gate(
    uint8_t	num,
    uint32_t base,
    uint16_t sel,
    uint8_t flags
)
{
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}
