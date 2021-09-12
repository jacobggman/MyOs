#pragma once

#include "ScreenColor.h"
#include "Char.h"

class Screen
{
public:
	Screen();
	void print_str(const char* string);
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
