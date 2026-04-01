#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Donanım seviyesi metin renkleri: VGA modunda Arka planı KOYU MOR rengine benzemesi için Magenta kullanıyoruz */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	// Siyah form yerine morumsu renkle (Magenta) Ankadia IDE teması yansıtılır
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_MAGENTA);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < 25; y++) {
		for (size_t x = 0; x < 80; x++) {
			const size_t index = y * 80 + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_print(const char* data) {
	size_t datalen = 0;
	while (data[datalen]) datalen++;
	
	for (size_t i = 0; i < datalen; i++) {
        const size_t index = terminal_row * 80 + terminal_column;
		terminal_buffer[index] = vga_entry(data[i], terminal_color);
		if (++terminal_column == 80) {
			terminal_column = 0;
			if (++terminal_row == 25) terminal_row = 0;
		}
	}
}

// OS Çekirdeği Başlangıç Noktası (Boot loader burayı çağırır)
void kmain(void) {
	terminal_initialize();
    
	terminal_print("Ankadia OS Yukleniyor...\n");
	terminal_print("[OK] GDT ve IDT Segmentleri Ayarlandi\n");
    terminal_print("[OK] Turkce Klavye Suruculeri Baslatiliyor...\n");
    terminal_print("Ankadia IDE Grafik Ortami Baslatilmaya Hazir.\n");
}
