#include "print.h"

// TODO:
// Make vs project
// Make user input
// Make the 8086 stuff abstract

extern "C" void kernel_main()
{
    Screen screen;
    screen.clear();
    screen.setColor(ScreenColor::GREEN, ScreenColor::BLACK);
    while (1)
    {
        screen.print_str("Welcome! ");
    }
}
