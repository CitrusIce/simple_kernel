%macro ISR_NOERRCODE 1
	[global isr%1]
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common_stub
%endmacro 

%macro ISR_ERRCODE 1
	[global isr%1]
	isr%1:
		cli
		push byte %1
		jmp isr_common_stub
%endmacro 

ISR_NOERRCODE  0    ; 0 #DE 除 0 异常
ISR_NOERRCODE  1    ; 1 #DB 调试异常
ISR_NOERRCODE  2    ; 2 NMI
ISR_NOERRCODE  3    ; 3 BP 断点异常 
ISR_NOERRCODE  4    ; 4 #OF 溢出 
ISR_NOERRCODE  5    ; 5 #BR 对数组的引用超出边界 
ISR_NOERRCODE  6    ; 6 #UD 无效或未定义的操作码 
ISR_NOERRCODE  7    ; 7 #NM 设备不可用(无数学协处理器) 
ISR_ERRCODE    8    ; 8 #DF 双重故障(有错误代码) 
ISR_NOERRCODE  9    ; 9 协处理器跨段操作
ISR_ERRCODE   10    ; 10 #TS 无效TSS(有错误代码) 
ISR_ERRCODE   11    ; 11 #NP 段不存在(有错误代码) 
ISR_ERRCODE   12    ; 12 #SS 栈错误(有错误代码) 
ISR_ERRCODE   13    ; 13 #GP 常规保护(有错误代码) 
ISR_ERRCODE   14    ; 14 #PF 页故障(有错误代码) 
ISR_NOERRCODE 15    ; 15 CPU 保留 
ISR_NOERRCODE 16    ; 16 #MF 浮点处理单元错误 
ISR_ERRCODE   17    ; 17 #AC 对齐检查 
ISR_NOERRCODE 18    ; 18 #MC 机器检查 
ISR_NOERRCODE 19    ; 19 #XM SIMD(单指令多数据)浮点异常

; 20 ~ 31 Intel 保留
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

[extern isr_handler]
isr_common_stub:
	pushad
	mov ax,ds
	push eax

	mov ax,0x10
	mov ds,ax 
	mov es,ax 
	mov fs,ax 
	mov gs,ax 

	call isr_handler 
	pop eax 
	mov ds,ax 
	mov es,ax 
	mov fs,ax 
	mov gs,ax 

	popad
	add esp,8
    sti 
    iret
	
%macro IRQ 2
  global irq%1
  irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10,42
IRQ 11,43
IRQ 12,44
IRQ 13,45
IRQ 14,46
IRQ 15,47

[EXTERN irq_handler]

; This is our common IRQ stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame. 
irq_common_stub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop ebx        ; reload the original data segment descriptor
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret  
