#pragma once

#include <stdint.h>
#include <stddef.h>

enum class ScreenColor {
    BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GRAY = 7,
	DARK_GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15,
};

struct Char
{
	uint8_t character;
	uint8_t color;
};


class Screen
{
public:
	Screen();
	void print_str(char* string);
	void setColor(ScreenColor foreground, ScreenColor background);
	void clear();
	void print_char(char character);

private:
	void print_newline();
	void clear_row(size_t row);
	Char emptyChar();
	static size_t formatColor(ScreenColor foreground, ScreenColor background);

	const static size_t NUM_COLS = 80;
	const static size_t NUM_ROWS = 25;
private:
	Char* buffer;
	size_t col = 0;
	size_t row = 0;
	uint8_t color;
};

