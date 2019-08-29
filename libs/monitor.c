#include "monitor.h"

uint16_t * const video_memory = (uint16_t*)0xB8000;
const int screen_width = 80;
const int screen_height = 25;
const int default_color = 0b00000111;
// int cursor_x;
// int cursor_y;

// void outb(uint16_t port, uint8_t value)
// {
// asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
// }
void move_cursor()
{
    uint16_t cursor_location;
    cursor_location = cursor_y * 80 + cursor_x;
    outb(0x3D4, 0xe);
    outb(0x3D5, cursor_location >> 8);
    outb(0x3D4, 0xf);
    outb(0x3D5, cursor_location);
}
void scroll()
{

    uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20  | (attributeByte << 8);

    if(cursor_y >= 25)
    {
        int i;
        for (i = 0 * 80; i < 24 * 80; i++)
        {
            video_memory[i] = video_memory[i + 80];
        }
        for (i = 24 * 80; i < 25 * 80; i++)
        {
            video_memory[i] = blank;
        }
        cursor_y = 24;
    }
}
void clear()
{
    int x;
    uint16_t* location;
    for(x = 0; x < 80 * 25; x++)
    {
        location = video_memory + x;
        *location = default_color << 8 | 0x20;
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}
void print_char(char c)
{
    uint16_t* location;
    location = video_memory + cursor_x + (80 * cursor_y) ;
    switch(c)
    {
    case '\n':
        cursor_y++;
        cursor_x = 0;
        break;
    case '\t':
        cursor_x = cursor_x - (cursor_x % 4) + 4;
        cursor_x++;
        break;
    //backspace
    case 0x08:
        cursor_x--;
        location = video_memory + cursor_x + (80 * cursor_y) ;
        *location = default_color << 8 | 0x20;
        break;
    default:
        *location = default_color << 8 | c;
        cursor_x++;
    }
    if(cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_cursor();
}
void print(const char * text)
{
    while(*text != '\0')
    {
        print_char(*text);
        text++;
    }
}
void print_num_dec(int num)
{
    char stack_buffer[255];
    int i = -1; //stack pointer
    while(num != 0)
    {
        stack_buffer[++i] = num % 10 + '0';
        num /= 10;
    }
    for(; i >= 0; i--)
    {
        print_char(stack_buffer[i]);
    }

}
void print_num_hex(int num)
{
    char stack_buffer[255];
    int i = -1; //stack pointer
    while(num != 0)
    {
        if(num % 16 >= 10)
        {
            stack_buffer[++i] = num % 16 + 'A' - 10;
        }
        else
        {
            stack_buffer[++i] = num % 10 + '0';
        }
        num /= 16;
    }
    // print("0x");
    for(; i >= 0; i--)
    {
        print_char(stack_buffer[i]);
    }

}
