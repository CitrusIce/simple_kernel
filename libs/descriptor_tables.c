#include "descriptor_tables.h"

void init_descriptor_tables()
{
	init_gdt();
	init_idt();
}
