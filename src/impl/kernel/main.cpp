#include "print.h"

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
