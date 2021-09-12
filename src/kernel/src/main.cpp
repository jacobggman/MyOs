#include "Screen.h"

// TODO:
// Learn and implement libc
// Fix the folders of the project
// Fix the build of the project
// Make user input
// Make the 8086 stuff abstract

static unsigned long int next = 1;

int rand(void) // RAND_MAX assumed to be 32767
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
	next = seed;
}

static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile("outb %0, %1"
				 :
				 : "a"(val), "Nd"(port));
	/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline void io_wait(void)
{
	outb(0x80, 0);
}

//extern "C" int get_input();
//{
//	int a = 48, b = 5, c;
//
//	__asm
//	{
//		mov ax, a
//		mov bx, b
//		add ax, bx
//		mov c, ax
//	};
//	return c;
//}

static inline uint32_t farpeekl(uint16_t sel, void *off)
{
	uint32_t ret;
	asm("push %%fs\n\t"
		"mov  %1, %%fs\n\t"
		"mov  %%fs:(%2), %0\n\t"
		"pop  %%fs"
		: "=r"(ret)
		: "g"(sel), "r"(off));
	return ret;
}

extern "C" void kernel_main()
{

	Screen screen;
	screen.clear();
	screen.setColor(ScreenColor::GREEN, ScreenColor::BLACK);
	srand(2);
	while (1)
	{
		screen.print_str("Welcome! ");
		// for (size_t i = 0; i < 69; i++)
		// {
		// 	screen.print_char(48 + (rand() % 10));
		// }
		extern int say_hi();
		screen.print_char(say_hi());
		screen.print_char('\n');
		for (size_t i = 0; i < 100; i++)
		{
		}
	}
}