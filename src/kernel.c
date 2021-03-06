#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you're in for lots of surprises trolololo"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

enum vga_color {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

size_t strlen(const char* str) {
    size_t ret = 0;
    while (str[ret] != 0) {
        ret++;
    }
    return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_advancebuffer() {
    for (size_t i = 0; i < VGA_HEIGHT; i++) {
        for (size_t j = 0; j < VGA_WIDTH; j++) {
            terminal_buffer[i * VGA_WIDTH + j] = terminal_buffer[(i + 1) * VGA_WIDTH + j];
        }
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_advancebuffer();
            terminal_row--;
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_advancebuffer();
                terminal_row = 0;
            }
        }
    }
}

void terminal_writestring(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) {
        terminal_putchar(data[i]);
    }
}

#if defined(__cplusplus)
extern "C"
#endif

void kernel_main() {
    terminal_initialize();
    terminal_writestring("Hello, kernel world! 1\n");
    terminal_writestring("Hello, kernel world! 2\n");
    terminal_writestring("Hello, kernel world! 3\n");
    terminal_writestring("Hello, kernel world! 4\n");
    terminal_writestring("Hello, kernel world! 5\n");
    terminal_writestring("Hello, kernel world! 6\n");

    terminal_writestring("Hello, kernel world! 7\n");
    terminal_writestring("Hello, kernel world! 8\n");
    terminal_writestring("Hello, kernel world! 9\n");
    terminal_writestring("Hello, kernel world! 10\n");
    terminal_writestring("Hello, kernel world! 11\n");    
    terminal_writestring("Hello, kernel world! 12\n");
    terminal_writestring("Hello, kernel world! 13\n");
    terminal_writestring("Hello, kernel world! 14\n");
    terminal_writestring("Hello, kernel world! 15\n");
    
    terminal_writestring("Hello, kernel world! 16\n");
    terminal_writestring("Hello, kernel world! 17\n");
    terminal_writestring("Hello, kernel world! 18\n");
    terminal_writestring("Hello, kernel world! 19\n");
    terminal_writestring("Hello, kernel world! 20\n");
    terminal_writestring("Hello, kernel world! 21\n");
    terminal_writestring("Hello, kernel world! 22\n");

    terminal_writestring("Hello, kernel world! 23\n");
    terminal_writestring("Hello, kernel world! 24\n");
    terminal_writestring("Hello, kernel world! 25\n");
    terminal_writestring("Hello, kernel world! 26\n");
    terminal_writestring("Hello, kernel world! 27\n");
    terminal_writestring("Hello, kernel world! 28\n");

    terminal_writestring("Hello, kernel world! 29\n");
    terminal_writestring("Mourits is the best!!!\n");
}
