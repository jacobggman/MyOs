#include "print.h"




//void clear_row(size_t row)
//{
//    Char empty = {
//        ' ',
//        color,
//    };
//
//    for (size_t col = 0; col < NUM_COLS; col++)
//    {
//        buffer[col + NUM_COLS * row] = empty;
//    }
//}
//
//void clear()
//{
//    for (size_t i = 0; i < NUM_ROWS; i++)
//    {
//        clear_row(i);
//    }
//}
//
//void print_newline()
//{
//    col = 0;
//
//    if (row < NUM_ROWS - 1)
//    {
//        row++;
//        return;
//    }
//
//    for (size_t row = 1; row < NUM_ROWS; row++)
//    {
//        for (size_t col = 0; col < NUM_COLS; col++)
//        {
//            Char character = buffer[col + NUM_COLS * row];
//            buffer[col + NUM_COLS * (row - 1)] = character;
//        }
//    }
//
//    clear_row(NUM_ROWS - 1);
//}
//
//void print_char(char character)
//{
//    if (character == '\n')
//    {
//        print_newline();
//        return;
//    }
//
//    if (col >= NUM_COLS)
//    {
//        print_newline();
//    }
//
//    buffer[col + NUM_COLS * row] = {
//        (uint8_t)character,
//        color,
//    };
//
//    col++;
//}
//
//void print_str(char *str)
//{
//    for (size_t i = 0; 1; i++)
//    {
//        char character = (uint8_t)str[i];
//
//        if (character == '\0')
//        {
//            return;
//        }
//
//        print_char(character);
//    }
//}

//void print_set_color(uint8_t foreground, uint8_t background)
//{
//    color = foreground + (background << 4);
//}

Screen::Screen()
{
    this->buffer = (Char*)0xb8000;
    this->col = 0;
    this->row = 0;
    this->setColor(ScreenColor::WHITE, ScreenColor::BLACK);
}

void Screen::print_str(char* string)
{
    for (size_t i = 0; 1; i++)
    {
        char character = (uint8_t)string[i];

        if (character == '\0')
        {
            return;
        }

        this->print_char(character);
    }
}

void Screen::setColor(ScreenColor foreground, ScreenColor background)
{
    this->color = Screen::formatColor(foreground, background);
}

void Screen::clear()
{
    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        this->clear_row(i);
    }
}

void Screen::print_char(char character)
{
    if (character == '\n')
    {
        print_newline();
        return;
    }

    if (col >= NUM_COLS)
    {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = {
        (uint8_t)character,
        color,
    };

    col++;
}

void Screen::print_newline()
{
    col = 0;
    
    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }
    
    for (size_t row = 1; row < NUM_ROWS; row++)
    {
        for (size_t col = 0; col < NUM_COLS; col++)
        {
            Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }
    
    clear_row(NUM_ROWS - 1);
}

void Screen::clear_row(size_t row)
{
    Char empty = emptyChar();

    for (size_t col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

Char Screen::emptyChar()
{
    return { ' ', color };
}

size_t Screen::formatColor(ScreenColor foreground, ScreenColor background)
{
    return (size_t)foreground | (size_t)background << 4;
}
