// #include <stdio.h>
// #include <stdint.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_rom_sys.h"

// #define LCD_SCK 16
// #define LCD_MOSI 15
// #define LCD_DC 17
// #define LCD_RST 18

// #define LCD_W 240
// #define LCD_H 240

// // For many 240x240 ST7789 modules
// #define LCD_X_OFFSET 0
// #define LCD_Y_OFFSET 0

// static const char *TAG = "ST7789_BITBANG";

// static void lcd_delay_ms(int ms)
// {
//     vTaskDelay(pdMS_TO_TICKS(ms));
// }

// static void lcd_delay_us(int us)
// {
//     esp_rom_delay_us(us);
// }

// static void spi_write_byte(uint8_t data)
// {
//     gpio_set_level(LCD_SCK, 1); // idle high

//     for (int i = 7; i >= 0; i--)
//     {
//         gpio_set_level(LCD_SCK, 0);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_SCK, 1);
//         lcd_delay_us(1);
//     }
// }

// static void lcd_cmd(uint8_t cmd)
// {
//     gpio_set_level(LCD_DC, 0);
//     lcd_delay_us(1);
//     spi_write_byte(cmd);
// }

// static void lcd_data(uint8_t data)
// {
//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);
//     spi_write_byte(data);
// }

// static void lcd_data16(uint16_t data)
// {
//     lcd_data(data >> 8);
//     lcd_data(data & 0xFF);
// }

// static void lcd_reset(void)
// {
//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 0);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(200);
// }

// static void lcd_init(void)
// {
//     lcd_reset();

//     ESP_LOGI(TAG, "SWRESET");
//     lcd_cmd(0x01);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "SLPOUT");
//     lcd_cmd(0x11);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "COLMOD RGB565");
//     lcd_cmd(0x3A);
//     lcd_data(0x55); // 16-bit RGB565
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "MADCTL");
//     lcd_cmd(0x36);
//     lcd_data(0x00);

//     /*
//         Try this first: inversion ON.
//         If nothing or weird colors, change 0x21 to 0x20.
//     */
//     ESP_LOGI(TAG, "INVON");
//     // lcd_cmd(0x21); // inversion ON
//     lcd_cmd(0x20); // inversion OFF

//     ESP_LOGI(TAG, "NORON");
//     lcd_cmd(0x13);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "DISPON");
//     lcd_cmd(0x29);
//     lcd_delay_ms(100);
// }

// static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
// {
//     x0 += LCD_X_OFFSET;
//     x1 += LCD_X_OFFSET;
//     y0 += LCD_Y_OFFSET;
//     y1 += LCD_Y_OFFSET;

//     lcd_cmd(0x2A); // CASET
//     lcd_data16(x0);
//     lcd_data16(x1);

//     lcd_cmd(0x2B); // RASET
//     lcd_data16(y0);
//     lcd_data16(y1);

//     lcd_cmd(0x2C); // RAMWR
// }

// static void lcd_fill(uint16_t color)
// {
//     uint8_t hi = color >> 8;
//     uint8_t lo = color & 0xFF;

//     lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < LCD_W * LCD_H; i++)
//     {
//         spi_write_byte(hi);
//         spi_write_byte(lo);
//     }
// }
// void app_main(void)
// {
//     ESP_LOGI(TAG, "Starting ST7789 bitbang test");

//     gpio_config_t conf = {
//         .pin_bit_mask = (1ULL << LCD_SCK) |
//                         (1ULL << LCD_MOSI) |
//                         (1ULL << LCD_DC) |
//                         (1ULL << LCD_RST),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};

//     gpio_config(&conf);

//     // SPI mode 3 style: clock idle HIGH
//     gpio_set_level(LCD_SCK, 1);
//     gpio_set_level(LCD_MOSI, 0);
//     gpio_set_level(LCD_DC, 0);
//     gpio_set_level(LCD_RST, 1);

//     lcd_delay_ms(500);

//     lcd_init();

//     while (1)
//     {
//         ESP_LOGI(TAG, "RED");
//         lcd_fill(0xF800);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "GREEN");
//         lcd_fill(0x07E0);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "BLUE");
//         lcd_fill(0x001F);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "WHITE");
//         lcd_fill(0xFFFF);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "BLACK");
//         lcd_fill(0x0000);
//         lcd_delay_ms(1000);
//     }
// }
//////////////////////////////////////////////////////
// #include <stdio.h>
// #include <stdint.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_rom_sys.h"

// #define LCD_SCK 16
// #define LCD_MOSI 15
// #define LCD_DC 17
// #define LCD_RST 18

// #define LCD_W 240
// #define LCD_H 240

// #define LCD_X_OFFSET 0
// #define LCD_Y_OFFSET 0

// static const char *TAG = "ST7789_BITBANG";

// static void lcd_delay_ms(int ms)
// {
//     vTaskDelay(pdMS_TO_TICKS(ms));
// }

// static void lcd_delay_us(int us)
// {
//     esp_rom_delay_us(us);
// }

// /*
//     SPI mode 3 style:
//     - Clock idle HIGH
//     - Data changes while clock is LOW
//     - LCD reads on rising edge
// */
// static void spi_write_byte(uint8_t data)
// {
//     gpio_set_level(LCD_SCK, 1);

//     for (int i = 7; i >= 0; i--)
//     {
//         gpio_set_level(LCD_SCK, 0);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_SCK, 1);
//         lcd_delay_us(1);
//     }
// }

// static void lcd_cmd(uint8_t cmd)
// {
//     gpio_set_level(LCD_DC, 0);
//     lcd_delay_us(1);
//     spi_write_byte(cmd);
// }

// static void lcd_data(uint8_t data)
// {
//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);
//     spi_write_byte(data);
// }

// static void lcd_data16(uint16_t data)
// {
//     lcd_data(data >> 8);
//     lcd_data(data & 0xFF);
// }

// static void lcd_reset(void)
// {
//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 0);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(200);
// }

// static void lcd_init(void)
// {
//     lcd_reset();

//     ESP_LOGI(TAG, "SWRESET");
//     lcd_cmd(0x01);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "SLPOUT");
//     lcd_cmd(0x11);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "COLMOD RGB565");
//     lcd_cmd(0x3A);
//     lcd_data(0x55);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "MADCTL");
//     lcd_cmd(0x36);
//     lcd_data(0x00);

//     ESP_LOGI(TAG, "INVOFF");
//     lcd_cmd(0x20);

//     ESP_LOGI(TAG, "NORON");
//     lcd_cmd(0x13);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "DISPON");
//     lcd_cmd(0x29);
//     lcd_delay_ms(100);
// }

// static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
// {
//     x0 += LCD_X_OFFSET;
//     x1 += LCD_X_OFFSET;
//     y0 += LCD_Y_OFFSET;
//     y1 += LCD_Y_OFFSET;

//     lcd_cmd(0x2A);
//     lcd_data16(x0);
//     lcd_data16(x1);

//     lcd_cmd(0x2B);
//     lcd_data16(y0);
//     lcd_data16(y1);

//     lcd_cmd(0x2C);
// }

// static void lcd_fill(uint16_t color)
// {
//     uint8_t hi = color >> 8;
//     uint8_t lo = color & 0xFF;

//     lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < LCD_W * LCD_H; i++)
//     {
//         spi_write_byte(hi);
//         spi_write_byte(lo);
//     }
// }

// void app_main(void)
// {
//     ESP_LOGI(TAG, "Starting ST7789 bitbang test");

//     gpio_config_t conf = {
//         .pin_bit_mask = (1ULL << LCD_SCK) |
//                         (1ULL << LCD_MOSI) |
//                         (1ULL << LCD_DC) |
//                         (1ULL << LCD_RST),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};

//     gpio_config(&conf);

//     gpio_set_level(LCD_SCK, 1);
//     gpio_set_level(LCD_MOSI, 0);
//     gpio_set_level(LCD_DC, 0);
//     gpio_set_level(LCD_RST, 1);

//     lcd_delay_ms(500);

//     lcd_init();

//     while (1)
//     {
//         ESP_LOGI(TAG, "RED");
//         lcd_fill(0xF800);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "GREEN");
//         lcd_fill(0x07E0);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "BLUE");
//         lcd_fill(0x001F);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "WHITE");
//         lcd_fill(0xFFFF);
//         lcd_delay_ms(1000);

//         ESP_LOGI(TAG, "BLACK");
//         lcd_fill(0x0000);
//         lcd_delay_ms(1000);
//     }
// }

//////////////////////////////////////////////////////

// #include <stdio.h>
// #include <stdint.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_rom_sys.h"

// /*
//     WORKING WIRING:

//     LCD VCC  -> 5V
//     LCD BUK  -> 5V
//     LCD GND  -> external GND
//     ESP32 GND -> same external GND

//     LCD SCK  -> GPIO16
//     LCD SDA  -> GPIO15
//     LCD DC   -> GPIO17
//     LCD RES  -> GPIO18

//     IMPORTANT:
//     Do NOT put 5V on SCK/SDA/DC/RES.
// */

// #define LCD_SCK 16
// #define LCD_MOSI 15
// #define LCD_DC 17
// #define LCD_RST 18

// #define LCD_W 240
// #define LCD_H 240

// #define LCD_X_OFFSET 0
// #define LCD_Y_OFFSET 0

// #define COLOR_BLACK 0x0000
// #define COLOR_WHITE 0xFFFF
// #define COLOR_RED 0xF800
// #define COLOR_GREEN 0x07E0
// #define COLOR_BLUE 0x001F
// #define COLOR_YELLOW 0xFFE0
// #define COLOR_PURPLE 0x8010
// #define COLOR_CYAN 0x07FF

// static const char *TAG = "ST7789_SMILEY";

// /*
//     16x16 smiley sprite.

//     . = transparent/background black
//     Y = yellow
//     K = black
//     R = red
// */
// static const char smiley_16x16[16][17] = {
//     "................",
//     ".....YYYYYY.....",
//     "...YYYYYYYYYY...",
//     "..YYYYYYYYYYYY..",
//     ".YYYYYYYYYYYYYY.",
//     ".YYYKKYYYYKKYYY.",
//     "YYYYKKYYYYKKYYYY",
//     "YYYYYYYYYYYYYYYY",
//     "YYYYYYYYYYYYYYYY",
//     "YYYYYRRRRRRYYYYY",
//     ".YYYYRYYYYRYYYY.",
//     ".YYYYYRRRYYYYYY.",
//     "..YYYYYYYYYYYY..",
//     "...YYYYYYYYYY...",
//     ".....YYYYYY.....",
//     "................"};

// static void lcd_delay_ms(int ms)
// {
//     vTaskDelay(pdMS_TO_TICKS(ms));
// }

// static void lcd_delay_us(int us)
// {
//     esp_rom_delay_us(us);
// }

// /*
//     Bit-banged SPI mode 3 style:
//     - clock idle HIGH
//     - data changes while clock is LOW
//     - LCD reads data on rising edge
// */
// static void spi_write_byte(uint8_t data)
// {
//     gpio_set_level(LCD_SCK, 1);

//     for (int i = 7; i >= 0; i--)
//     {
//         gpio_set_level(LCD_SCK, 0);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_SCK, 1);
//         lcd_delay_us(1);
//     }
// }

// static void lcd_cmd(uint8_t cmd)
// {
//     gpio_set_level(LCD_DC, 0);
//     lcd_delay_us(1);
//     spi_write_byte(cmd);
// }

// static void lcd_data(uint8_t data)
// {
//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);
//     spi_write_byte(data);
// }

// static void lcd_data16(uint16_t data)
// {
//     lcd_data(data >> 8);
//     lcd_data(data & 0xFF);
// }

// static void lcd_reset(void)
// {
//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 0);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(200);
// }

// static void lcd_init(void)
// {
//     lcd_reset();

//     ESP_LOGI(TAG, "SWRESET");
//     lcd_cmd(0x01); // Software reset
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "SLPOUT");
//     lcd_cmd(0x11); // Sleep out
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "COLMOD RGB565");
//     lcd_cmd(0x3A);  // Color mode
//     lcd_data(0x55); // 16-bit RGB565
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "MADCTL");
//     lcd_cmd(0x36); // Memory access control
//     lcd_data(0x00);

//     ESP_LOGI(TAG, "INVOFF");
//     lcd_cmd(0x20); // Inversion off

//     ESP_LOGI(TAG, "NORON");
//     lcd_cmd(0x13); // Normal display mode
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "DISPON");
//     lcd_cmd(0x29); // Display on
//     lcd_delay_ms(100);
// }

// static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
// {
//     x0 += LCD_X_OFFSET;
//     x1 += LCD_X_OFFSET;
//     y0 += LCD_Y_OFFSET;
//     y1 += LCD_Y_OFFSET;

//     lcd_cmd(0x2A); // CASET - column address
//     lcd_data16(x0);
//     lcd_data16(x1);

//     lcd_cmd(0x2B); // RASET - row address
//     lcd_data16(y0);
//     lcd_data16(y1);

//     lcd_cmd(0x2C); // RAMWR - memory write
// }

// static void lcd_send_color(uint16_t color)
// {
//     spi_write_byte(color >> 8);
//     spi_write_byte(color & 0xFF);
// }

// static void lcd_fill(uint16_t color)
// {
//     lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < LCD_W * LCD_H; i++)
//     {
//         lcd_send_color(color);
//     }
// }

// static uint16_t sprite_color(char c, uint16_t background)
// {
//     switch (c)
//     {
//     case 'Y':
//         return COLOR_YELLOW;
//     case 'K':
//         return COLOR_BLACK;
//     case 'R':
//         return COLOR_RED;
//     case 'W':
//         return COLOR_WHITE;
//     case 'B':
//         return COLOR_BLUE;
//     case 'G':
//         return COLOR_GREEN;
//     case 'P':
//         return COLOR_PURPLE;
//     case 'C':
//         return COLOR_CYAN;
//     case '.':
//     default:
//         return background;
//     }
// }

// /*
//     Draws a 16x16 sprite scaled up.

//     Example:
//     scale = 1 -> 16x16
//     scale = 4 -> 64x64
//     scale = 6 -> 96x96
// */
// static void lcd_draw_sprite_16x16_scaled(
//     int x,
//     int y,
//     const char sprite[16][17],
//     int scale,
//     uint16_t background)
// {
//     int width = 16 * scale;

//     for (int row = 0; row < 16; row++)
//     {
//         for (int sy = 0; sy < scale; sy++)
//         {
//             int screen_y = y + row * scale + sy;

//             lcd_set_window(
//                 x,
//                 screen_y,
//                 x + width - 1,
//                 screen_y);

//             gpio_set_level(LCD_DC, 1);
//             lcd_delay_us(1);

//             for (int col = 0; col < 16; col++)
//             {
//                 uint16_t color = sprite_color(sprite[row][col], background);

//                 for (int sx = 0; sx < scale; sx++)
//                 {
//                     lcd_send_color(color);
//                 }
//             }
//         }
//     }
// }

// void app_main(void)
// {
//     ESP_LOGI(TAG, "Starting ST7789 smiley test");

//     gpio_config_t conf = {
//         .pin_bit_mask = (1ULL << LCD_SCK) |
//                         (1ULL << LCD_MOSI) |
//                         (1ULL << LCD_DC) |
//                         (1ULL << LCD_RST),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};

//     gpio_config(&conf);

//     gpio_set_level(LCD_SCK, 1);
//     gpio_set_level(LCD_MOSI, 0);
//     gpio_set_level(LCD_DC, 0);
//     gpio_set_level(LCD_RST, 1);

//     lcd_delay_ms(500);

//     lcd_init();

//     while (1)
//     {
//         ESP_LOGI(TAG, "Smiley on black");
//         lcd_fill(COLOR_BLACK);
//         lcd_draw_sprite_16x16_scaled(72, 72, smiley_16x16, 6, COLOR_BLACK);
//         lcd_delay_ms(3000);

//         ESP_LOGI(TAG, "Smiley on blue");
//         lcd_fill(COLOR_BLUE);
//         lcd_draw_sprite_16x16_scaled(72, 72, smiley_16x16, 6, COLOR_BLUE);
//         lcd_delay_ms(3000);

//         ESP_LOGI(TAG, "Smiley on purple");
//         lcd_fill(COLOR_PURPLE);
//         lcd_draw_sprite_16x16_scaled(72, 72, smiley_16x16, 6, COLOR_PURPLE);
//         lcd_delay_ms(3000);

//         ESP_LOGI(TAG, "Color cycle test");
//         lcd_fill(COLOR_RED);
//         lcd_delay_ms(800);

//         lcd_fill(COLOR_GREEN);
//         lcd_delay_ms(800);

//         lcd_fill(COLOR_BLUE);
//         lcd_delay_ms(800);

//         lcd_fill(COLOR_WHITE);
//         lcd_delay_ms(800);

//         lcd_fill(COLOR_BLACK);
//         lcd_delay_ms(800);
//     }
// }

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"

/*
    WORKING WIRING:

    LCD VCC  -> 5V
    LCD BUK  -> 5V
    LCD GND  -> external GND
    ESP32 GND -> same external GND

    LCD SCK  -> GPIO16
    LCD SDA  -> GPIO15
    LCD DC   -> GPIO17
    LCD RES  -> GPIO18
*/

// #define LCD_SCK 16
// #define LCD_MOSI 15
// #define LCD_DC 17
// #define LCD_RST 18

// #define LCD_W 240
// #define LCD_H 240

// #define LCD_X_OFFSET 0
// #define LCD_Y_OFFSET 0

// #define COLOR_BLACK 0x0000
// #define COLOR_WHITE 0xFFFF
// #define COLOR_RED 0xF800
// #define COLOR_GREEN 0x07E0
// #define COLOR_BLUE 0x001F
// #define COLOR_YELLOW 0xFFE0

// static const char *TAG = "ST7789_TEXT";

// /*
//     Tiny 5x7 font.
//     Each byte is one row.
//     Bits: 1 = draw pixel, 0 = background.
// */
// static const uint8_t FONT_SPACE[7] = {
//     0b00000,
//     0b00000,
//     0b00000,
//     0b00000,
//     0b00000,
//     0b00000,
//     0b00000};

// static const uint8_t FONT_H[7] = {
//     0b10001,
//     0b10001,
//     0b10001,
//     0b11111,
//     0b10001,
//     0b10001,
//     0b10001};

// static const uint8_t FONT_E[7] = {
//     0b11111,
//     0b10000,
//     0b10000,
//     0b11110,
//     0b10000,
//     0b10000,
//     0b11111};

// static const uint8_t FONT_L[7] = {
//     0b10000,
//     0b10000,
//     0b10000,
//     0b10000,
//     0b10000,
//     0b10000,
//     0b11111};

// static const uint8_t FONT_O[7] = {
//     0b01110,
//     0b10001,
//     0b10001,
//     0b10001,
//     0b10001,
//     0b10001,
//     0b01110};

// static const uint8_t FONT_W[7] = {
//     0b10001,
//     0b10001,
//     0b10001,
//     0b10101,
//     0b10101,
//     0b10101,
//     0b01010};

// static const uint8_t FONT_R[7] = {
//     0b11110,
//     0b10001,
//     0b10001,
//     0b11110,
//     0b10100,
//     0b10010,
//     0b10001};

// static const uint8_t FONT_D[7] = {
//     0b11110,
//     0b10001,
//     0b10001,
//     0b10001,
//     0b10001,
//     0b10001,
//     0b11110};

// static void lcd_delay_ms(int ms)
// {
//     vTaskDelay(pdMS_TO_TICKS(ms));
// }

// static void lcd_delay_us(int us)
// {
//     esp_rom_delay_us(us);
// }

// /*
//     SPI mode 3 style:
//     - Clock idle HIGH
//     - Data changes while clock is LOW
//     - LCD reads on rising edge
// */
// static void spi_write_byte(uint8_t data)
// {
//     gpio_set_level(LCD_SCK, 1);

//     for (int i = 7; i >= 0; i--)
//     {
//         gpio_set_level(LCD_SCK, 0);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_SCK, 1);
//         lcd_delay_us(1);
//     }
// }

// static void lcd_cmd(uint8_t cmd)
// {
//     gpio_set_level(LCD_DC, 0);
//     lcd_delay_us(1);
//     spi_write_byte(cmd);
// }

// static void lcd_data(uint8_t data)
// {
//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);
//     spi_write_byte(data);
// }

// static void lcd_data16(uint16_t data)
// {
//     lcd_data(data >> 8);
//     lcd_data(data & 0xFF);
// }

// static void lcd_reset(void)
// {
//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 0);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(200);
// }

// static void lcd_init(void)
// {
//     lcd_reset();

//     ESP_LOGI(TAG, "SWRESET");
//     lcd_cmd(0x01);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "SLPOUT");
//     lcd_cmd(0x11);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "COLMOD RGB565");
//     lcd_cmd(0x3A);
//     lcd_data(0x55);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "MADCTL");
//     lcd_cmd(0x36);
//     lcd_data(0x00);

//     ESP_LOGI(TAG, "INVOFF");
//     lcd_cmd(0x20);

//     ESP_LOGI(TAG, "NORON");
//     lcd_cmd(0x13);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "DISPON");
//     lcd_cmd(0x29);
//     lcd_delay_ms(100);
// }

// static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
// {
//     x0 += LCD_X_OFFSET;
//     x1 += LCD_X_OFFSET;
//     y0 += LCD_Y_OFFSET;
//     y1 += LCD_Y_OFFSET;

//     lcd_cmd(0x2A);
//     lcd_data16(x0);
//     lcd_data16(x1);

//     lcd_cmd(0x2B);
//     lcd_data16(y0);
//     lcd_data16(y1);

//     lcd_cmd(0x2C);
// }

// static void lcd_send_color(uint16_t color)
// {
//     spi_write_byte(color >> 8);
//     spi_write_byte(color & 0xFF);
// }

// static void lcd_fill(uint16_t color)
// {
//     lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < LCD_W * LCD_H; i++)
//     {
//         lcd_send_color(color);
//     }
// }

// static void lcd_draw_rect(int x, int y, int w, int h, uint16_t color)
// {
//     if (x < 0 || y < 0 || x + w > LCD_W || y + h > LCD_H)
//     {
//         return;
//     }

//     lcd_set_window(x, y, x + w - 1, y + h - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < w * h; i++)
//     {
//         lcd_send_color(color);
//     }
// }

// static const uint8_t *get_font(char c)
// {
//     switch (c)
//     {
//     case 'H':
//         return FONT_H;
//     case 'E':
//         return FONT_E;
//     case 'L':
//         return FONT_L;
//     case 'O':
//         return FONT_O;
//     case 'W':
//         return FONT_W;
//     case 'R':
//         return FONT_R;
//     case 'D':
//         return FONT_D;
//     case ' ':
//     default:
//         return FONT_SPACE;
//     }
// }

// static void lcd_draw_char(int x, int y, char c, int scale, uint16_t text_color, uint16_t bg_color)
// {
//     const uint8_t *glyph = get_font(c);

//     for (int row = 0; row < 7; row++)
//     {
//         for (int col = 0; col < 5; col++)
//         {
//             int bit = (glyph[row] >> (4 - col)) & 0x01;

//             uint16_t color = bit ? text_color : bg_color;

//             lcd_draw_rect(
//                 x + col * scale,
//                 y + row * scale,
//                 scale,
//                 scale,
//                 color);
//         }
//     }
// }

// static void lcd_draw_text(int x, int y, const char *text, int scale, uint16_t text_color, uint16_t bg_color)
// {
//     int cursor_x = x;

//     for (int i = 0; text[i] != '\0'; i++)
//     {
//         lcd_draw_char(cursor_x, y, text[i], scale, text_color, bg_color);

//         /*
//             5 pixels character width + 1 pixel spacing
//         */
//         cursor_x += 6 * scale;
//     }
// }

// void app_main(void)
// {
//     ESP_LOGI(TAG, "Starting ST7789 text test");

//     gpio_config_t conf = {
//         .pin_bit_mask = (1ULL << LCD_SCK) |
//                         (1ULL << LCD_MOSI) |
//                         (1ULL << LCD_DC) |
//                         (1ULL << LCD_RST),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};

//     gpio_config(&conf);

//     gpio_set_level(LCD_SCK, 1);
//     gpio_set_level(LCD_MOSI, 0);
//     gpio_set_level(LCD_DC, 0);
//     gpio_set_level(LCD_RST, 1);

//     lcd_delay_ms(500);

//     lcd_init();

//     while (1)
//     {
//         ESP_LOGI(TAG, "HELLO WORLD");

//         lcd_fill(COLOR_YELLOW);

//         /*
//             Text size:
//             each char = 5x7 pixels
//             scale = 3
//             char width with spacing = 6 * 3 = 18 pixels
//             "HELLO WORLD" = 11 chars
//             11 * 18 = 198 pixels
//             centered x = (240 - 198) / 2 = 21
//         */
//         lcd_draw_text(21, 105, "HELLO WORLD", 3, COLOR_BLUE, COLOR_YELLOW);

//         lcd_delay_ms(5000);
//     }
// }
///////////////////////////////////////////////////////////////////////////////////
// #include <stdio.h>
// #include <stdint.h>
// #include <string.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_rom_sys.h"

// /*
//     WORKING WIRING:

//     LCD VCC   -> 5V
//     LCD BUK   -> 5V
//     LCD GND   -> external GND
//     ESP32 GND -> same external GND

//     LCD SCK   -> GPIO16
//     LCD SDA   -> GPIO15
//     LCD DC    -> GPIO17
//     LCD RES   -> GPIO18

//     IMPORTANT:
//     Do NOT put 5V on SCK/SDA/DC/RES.
// */

// #define LCD_SCK 16
// #define LCD_MOSI 15
// #define LCD_DC 17
// #define LCD_RST 18

// #define LCD_W 240
// #define LCD_H 240

// #define LCD_X_OFFSET 0
// #define LCD_Y_OFFSET 0

// #define COLOR_BLACK 0x0000
// #define COLOR_WHITE 0xFFFF
// #define COLOR_RED 0xF800
// #define COLOR_GREEN 0x07E0
// #define COLOR_BLUE 0x001F
// #define COLOR_YELLOW 0xFFE0
// #define COLOR_PURPLE 0x8010
// #define COLOR_CYAN 0x07FF
// #define COLOR_ORANGE 0xFD20

// static const char *TAG = "ST7789_DYNAMIC_TEXT";

// /*
//     5x7 font.
//     Each character is 5 pixels wide and 7 pixels tall.

//     1 = draw text color
//     0 = draw background color
// */
// static const uint8_t font_5x7[37][7] = {
//     // A
//     {0b01110, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001},
//     // B
//     {0b11110, 0b10001, 0b10001, 0b11110, 0b10001, 0b10001, 0b11110},
//     // C
//     {0b01110, 0b10001, 0b10000, 0b10000, 0b10000, 0b10001, 0b01110},
//     // D
//     {0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11110},
//     // E
//     {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b11111},
//     // F
//     {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b10000},
//     // G
//     {0b01110, 0b10001, 0b10000, 0b10111, 0b10001, 0b10001, 0b01110},
//     // H
//     {0b10001, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001},
//     // I
//     {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111},
//     // J
//     {0b00111, 0b00010, 0b00010, 0b00010, 0b10010, 0b10010, 0b01100},
//     // K
//     {0b10001, 0b10010, 0b10100, 0b11000, 0b10100, 0b10010, 0b10001},
//     // L
//     {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111},
//     // M
//     {0b10001, 0b11011, 0b10101, 0b10101, 0b10001, 0b10001, 0b10001},
//     // N
//     {0b10001, 0b11001, 0b10101, 0b10011, 0b10001, 0b10001, 0b10001},
//     // O
//     {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110},
//     // P
//     {0b11110, 0b10001, 0b10001, 0b11110, 0b10000, 0b10000, 0b10000},
//     // Q
//     {0b01110, 0b10001, 0b10001, 0b10001, 0b10101, 0b10010, 0b01101},
//     // R
//     {0b11110, 0b10001, 0b10001, 0b11110, 0b10100, 0b10010, 0b10001},
//     // S
//     {0b01111, 0b10000, 0b10000, 0b01110, 0b00001, 0b00001, 0b11110},
//     // T
//     {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100},
//     // U
//     {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110},
//     // V
//     {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01010, 0b00100},
//     // W
//     {0b10001, 0b10001, 0b10001, 0b10101, 0b10101, 0b10101, 0b01010},
//     // X
//     {0b10001, 0b10001, 0b01010, 0b00100, 0b01010, 0b10001, 0b10001},
//     // Y
//     {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b00100, 0b00100},
//     // Z
//     {0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b11111},

//     // 0
//     {0b01110, 0b10001, 0b10011, 0b10101, 0b11001, 0b10001, 0b01110},
//     // 1
//     {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110},
//     // 2
//     {0b01110, 0b10001, 0b00001, 0b00010, 0b00100, 0b01000, 0b11111},
//     // 3
//     {0b11110, 0b00001, 0b00001, 0b01110, 0b00001, 0b00001, 0b11110},
//     // 4
//     {0b00010, 0b00110, 0b01010, 0b10010, 0b11111, 0b00010, 0b00010},
//     // 5
//     {0b11111, 0b10000, 0b10000, 0b11110, 0b00001, 0b00001, 0b11110},
//     // 6
//     {0b01110, 0b10000, 0b10000, 0b11110, 0b10001, 0b10001, 0b01110},
//     // 7
//     {0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b01000, 0b01000},
//     // 8
//     {0b01110, 0b10001, 0b10001, 0b01110, 0b10001, 0b10001, 0b01110},
//     // 9
//     {0b01110, 0b10001, 0b10001, 0b01111, 0b00001, 0b00001, 0b01110},

//     // space
//     {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}};

// static void lcd_delay_ms(int ms)
// {
//     vTaskDelay(pdMS_TO_TICKS(ms));
// }

// static void lcd_delay_us(int us)
// {
//     esp_rom_delay_us(us);
// }

// /*
//     SPI mode 3 style:
//     - Clock idle HIGH
//     - Data changes while clock is LOW
//     - LCD reads on rising edge
// */
// static void spi_write_byte(uint8_t data)
// {
//     gpio_set_level(LCD_SCK, 1);

//     for (int i = 7; i >= 0; i--)
//     {
//         gpio_set_level(LCD_SCK, 0);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_SCK, 1);
//         lcd_delay_us(1);
//     }
// }

// static void lcd_cmd(uint8_t cmd)
// {
//     gpio_set_level(LCD_DC, 0);
//     lcd_delay_us(1);
//     spi_write_byte(cmd);
// }

// static void lcd_data(uint8_t data)
// {
//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);
//     spi_write_byte(data);
// }

// static void lcd_data16(uint16_t data)
// {
//     lcd_data(data >> 8);
//     lcd_data(data & 0xFF);
// }

// static void lcd_reset(void)
// {
//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 0);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(200);
// }

// static void lcd_init(void)
// {
//     lcd_reset();

//     ESP_LOGI(TAG, "SWRESET");
//     lcd_cmd(0x01);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "SLPOUT");
//     lcd_cmd(0x11);
//     lcd_delay_ms(150);

//     ESP_LOGI(TAG, "COLMOD RGB565");
//     lcd_cmd(0x3A);
//     lcd_data(0x55);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "MADCTL");
//     lcd_cmd(0x36);
//     lcd_data(0x00);

//     ESP_LOGI(TAG, "INVOFF");
//     lcd_cmd(0x20);

//     ESP_LOGI(TAG, "NORON");
//     lcd_cmd(0x13);
//     lcd_delay_ms(10);

//     ESP_LOGI(TAG, "DISPON");
//     lcd_cmd(0x29);
//     lcd_delay_ms(100);
// }

// static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
// {
//     x0 += LCD_X_OFFSET;
//     x1 += LCD_X_OFFSET;
//     y0 += LCD_Y_OFFSET;
//     y1 += LCD_Y_OFFSET;

//     lcd_cmd(0x2A);
//     lcd_data16(x0);
//     lcd_data16(x1);

//     lcd_cmd(0x2B);
//     lcd_data16(y0);
//     lcd_data16(y1);

//     lcd_cmd(0x2C);
// }

// static void lcd_send_color(uint16_t color)
// {
//     spi_write_byte(color >> 8);
//     spi_write_byte(color & 0xFF);
// }

// static void lcd_fill(uint16_t color)
// {
//     lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < LCD_W * LCD_H; i++)
//     {
//         lcd_send_color(color);
//     }
// }

// static void lcd_draw_rect(int x, int y, int w, int h, uint16_t color)
// {
//     if (x < 0 || y < 0 || x + w > LCD_W || y + h > LCD_H)
//     {
//         return;
//     }

//     lcd_set_window(x, y, x + w - 1, y + h - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int i = 0; i < w * h; i++)
//     {
//         lcd_send_color(color);
//     }
// }

// static const uint8_t *get_font(char c)
// {
//     if (c >= 'a' && c <= 'z')
//     {
//         c = c - 'a' + 'A';
//     }

//     if (c >= 'A' && c <= 'Z')
//     {
//         return font_5x7[c - 'A'];
//     }

//     if (c >= '0' && c <= '9')
//     {
//         return font_5x7[26 + (c - '0')];
//     }

//     return font_5x7[36]; // space
// }

// static void lcd_draw_char(int x, int y, char c, int scale, uint16_t text_color, uint16_t bg_color)
// {
//     const uint8_t *glyph = get_font(c);

//     for (int row = 0; row < 7; row++)
//     {
//         for (int col = 0; col < 5; col++)
//         {
//             int bit = (glyph[row] >> (4 - col)) & 0x01;
//             uint16_t color = bit ? text_color : bg_color;

//             lcd_draw_rect(
//                 x + col * scale,
//                 y + row * scale,
//                 scale,
//                 scale,
//                 color);
//         }
//     }
// }

// static void lcd_draw_text(int x, int y, const char *text, int scale, uint16_t text_color, uint16_t bg_color)
// {
//     int cursor_x = x;

//     for (int i = 0; text[i] != '\0'; i++)
//     {
//         lcd_draw_char(cursor_x, y, text[i], scale, text_color, bg_color);
//         cursor_x += 6 * scale;
//     }
// }

// static int lcd_text_width(const char *text, int scale)
// {
//     return strlen(text) * 6 * scale;
// }

// static void lcd_draw_text_centered(int y, const char *text, int scale, uint16_t text_color, uint16_t bg_color)
// {
//     int width = lcd_text_width(text, scale);
//     int x = (LCD_W - width) / 2;

//     if (x < 0)
//     {
//         x = 0;
//     }

//     lcd_draw_text(x, y, text, scale, text_color, bg_color);
// }

// static void lcd_draw_text_box(int x, int y, int w, int h, const char *text, int scale, uint16_t text_color, uint16_t bg_color)
// {
//     lcd_draw_rect(x, y, w, h, bg_color);
//     lcd_draw_text(x, y, text, scale, text_color, bg_color);
// }

// void app_main(void)
// {
//     ESP_LOGI(TAG, "Starting ST7789 dynamic text test");

//     gpio_config_t conf = {
//         .pin_bit_mask = (1ULL << LCD_SCK) |
//                         (1ULL << LCD_MOSI) |
//                         (1ULL << LCD_DC) |
//                         (1ULL << LCD_RST),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};

//     gpio_config(&conf);

//     gpio_set_level(LCD_SCK, 1);
//     gpio_set_level(LCD_MOSI, 0);
//     gpio_set_level(LCD_DC, 0);
//     gpio_set_level(LCD_RST, 1);

//     lcd_delay_ms(500);

//     lcd_init();

//     lcd_fill(COLOR_YELLOW);

//     int counter = 0;

//     while (1)
//     {
//         char line1[32];
//         char line2[32];

//         snprintf(line1, sizeof(line1), "HELLO WORLD");
//         snprintf(line2, sizeof(line2), "COUNT %d", counter);

//         lcd_draw_rect(0, 70, 240, 100, COLOR_YELLOW);

//         lcd_draw_text_centered(80, line1, 3, COLOR_BLUE, COLOR_YELLOW);
//         lcd_draw_text_centered(120, line2, 3, COLOR_BLUE, COLOR_YELLOW);

//         lcd_delay_ms(1000);

//         lcd_draw_rect(0, 70, 240, 100, COLOR_YELLOW);

//         if ((counter % 2) == 0)
//         {
//             lcd_draw_text_centered(90, "STATE ARMED", 3, COLOR_GREEN, COLOR_YELLOW);
//         }
//         else
//         {
//             lcd_draw_text_centered(90, "STATE DISARMED", 2, COLOR_RED, COLOR_YELLOW);
//         }

//         lcd_delay_ms(1000);

//         counter++;
//     }
// }

// #include <stdio.h>
// #include <stdint.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_rom_sys.h"

// #define LCD_SCK 16
// #define LCD_MOSI 15
// #define LCD_DC 17
// #define LCD_RST 18

// #define LCD_W 240
// #define LCD_H 240

// #define COLOR_YELLOW 0xFFE0
// #define COLOR_BLUE 0x189C

// static const char *TAG = "LCD_YELLOW";

// static void lcd_delay_ms(int ms)
// {
//     vTaskDelay(pdMS_TO_TICKS(ms));
// }

// static void lcd_delay_us(int us)
// {
//     esp_rom_delay_us(us);
// }

// static void spi_write_byte(uint8_t data)
// {
//     gpio_set_level(LCD_SCK, 1);

//     for (int i = 7; i >= 0; i--)
//     {
//         gpio_set_level(LCD_SCK, 0);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
//         lcd_delay_us(1);

//         gpio_set_level(LCD_SCK, 1);
//         lcd_delay_us(1);
//     }
// }

// static void lcd_cmd(uint8_t cmd)
// {
//     gpio_set_level(LCD_DC, 0);
//     lcd_delay_us(1);
//     spi_write_byte(cmd);
// }

// static void lcd_data(uint8_t data)
// {
//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);
//     spi_write_byte(data);
// }

// static void lcd_data16(uint16_t data)
// {
//     lcd_data(data >> 8);
//     lcd_data(data & 0xFF);
// }

// static void lcd_reset(void)
// {
//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 0);
//     lcd_delay_ms(100);

//     gpio_set_level(LCD_RST, 1);
//     lcd_delay_ms(200);
// }

// static void lcd_init(void)
// {
//     lcd_reset();

//     lcd_cmd(0x01); // software reset
//     lcd_delay_ms(150);

//     lcd_cmd(0x11); // sleep out
//     lcd_delay_ms(150);

//     lcd_cmd(0x3A);  // color mode
//     lcd_data(0x55); // RGB565, 16-bit color
//     lcd_delay_ms(10);

//     lcd_cmd(0x36); // orientation
//     lcd_data(0x00);

//     lcd_cmd(0x21); // inversion on

//     lcd_cmd(0x13); // normal mode
//     lcd_delay_ms(10);

//     lcd_cmd(0x29); // display on
//     lcd_delay_ms(100);
// }

// static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
// {
//     lcd_cmd(0x2A); // X area
//     lcd_data16(x0);
//     lcd_data16(x1);

//     lcd_cmd(0x2B); // Y area
//     lcd_data16(y0);
//     lcd_data16(y1);

//     lcd_cmd(0x2C); // start writing pixels
// }

// static void lcd_send_color(uint16_t color)
// {
//     spi_write_byte(color >> 8);
//     spi_write_byte(color & 0xFF);
// }

// static void lcd_fill_yellow(void)
// {
//     lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

//     gpio_set_level(LCD_DC, 1);
//     lcd_delay_us(1);

//     for (int y = 0; y < LCD_H; y++)
//     {
//         uint16_t line_color;

//         if (y % 2 == 0)
//         {
//             line_color = COLOR_BLUE;
//         }
//         else
//         {
//             line_color = COLOR_YELLOW;
//         }

//         for (int x = 0; x < LCD_W; x++)
//         {
//             lcd_send_color(line_color);
//         }
//     }
// }

// void app_main(void)
// {
//     ESP_LOGI(TAG, "Start yellow screen test");

//     gpio_config_t conf = {
//         .pin_bit_mask = (1ULL << LCD_SCK) |
//                         (1ULL << LCD_MOSI) |
//                         (1ULL << LCD_DC) |
//                         (1ULL << LCD_RST),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};

//     gpio_config(&conf);

//     gpio_set_level(LCD_SCK, 1);
//     gpio_set_level(LCD_MOSI, 0);
//     gpio_set_level(LCD_DC, 0);
//     gpio_set_level(LCD_RST, 1);

//     lcd_delay_ms(500);

//     lcd_init();

//     lcd_fill_yellow();

//     while (1)
//     {
//         lcd_delay_ms(1000);
//     }
// }

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_err.h"
#include "esp_log.h"

/*
    WORKING WIRING:

    LCD VCC   -> 5V
    LCD BUK   -> 5V
    LCD GND   -> external GND
    ESP32 GND -> same external GND

    LCD SCK   -> GPIO16
    LCD SDA   -> GPIO15
    LCD DC    -> GPIO17
    LCD RES   -> GPIO18

    IMPORTANT:
    Do NOT put 5V on SCK/SDA/DC/RES.
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_err.h"
#include "esp_log.h"

#define LCD_HOST SPI3_HOST

#define LCD_SCK 16
#define LCD_MOSI 15
#define LCD_DC 17
#define LCD_RST 18

#define LCD_W 240
#define LCD_H 240

#define COLOR_YELLOW 0xFFE0
#define COLOR_BLUE 0x001F
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0

static const char *TAG = "LCD_FONT_TEST";

static spi_device_handle_t lcd_spi = NULL;

static const uint8_t font_5x7[37][7] = {
    // A
    {0b01110, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001},
    // B
    {0b11110, 0b10001, 0b10001, 0b11110, 0b10001, 0b10001, 0b11110},
    // C
    {0b01110, 0b10001, 0b10000, 0b10000, 0b10000, 0b10001, 0b01110},
    // D
    {0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11110},
    // E
    {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b11111},
    // F
    {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b10000},
    // G
    {0b01110, 0b10001, 0b10000, 0b10111, 0b10001, 0b10001, 0b01110},
    // H
    {0b10001, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001},
    // I
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111},
    // J
    {0b00111, 0b00010, 0b00010, 0b00010, 0b10010, 0b10010, 0b01100},
    // K
    {0b10001, 0b10010, 0b10100, 0b11000, 0b10100, 0b10010, 0b10001},
    // L
    {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111},
    // M
    {0b10001, 0b11011, 0b10101, 0b10101, 0b10001, 0b10001, 0b10001},
    // N
    {0b10001, 0b11001, 0b10101, 0b10011, 0b10001, 0b10001, 0b10001},
    // O
    {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110},
    // P
    {0b11110, 0b10001, 0b10001, 0b11110, 0b10000, 0b10000, 0b10000},
    // Q
    {0b01110, 0b10001, 0b10001, 0b10001, 0b10101, 0b10010, 0b01101},
    // R
    {0b11110, 0b10001, 0b10001, 0b11110, 0b10100, 0b10010, 0b10001},
    // S
    {0b01111, 0b10000, 0b10000, 0b01110, 0b00001, 0b00001, 0b11110},
    // T
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100},
    // U
    {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110},
    // V
    {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01010, 0b00100},
    // W
    {0b10001, 0b10001, 0b10001, 0b10101, 0b10101, 0b10101, 0b01010},
    // X
    {0b10001, 0b10001, 0b01010, 0b00100, 0b01010, 0b10001, 0b10001},
    // Y
    {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b00100, 0b00100},
    // Z
    {0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b11111},

    // 0
    {0b01110, 0b10001, 0b10011, 0b10101, 0b11001, 0b10001, 0b01110},
    // 1
    {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110},
    // 2
    {0b01110, 0b10001, 0b00001, 0b00010, 0b00100, 0b01000, 0b11111},
    // 3
    {0b11110, 0b00001, 0b00001, 0b01110, 0b00001, 0b00001, 0b11110},
    // 4
    {0b00010, 0b00110, 0b01010, 0b10010, 0b11111, 0b00010, 0b00010},
    // 5
    {0b11111, 0b10000, 0b10000, 0b11110, 0b00001, 0b00001, 0b11110},
    // 6
    {0b01110, 0b10000, 0b10000, 0b11110, 0b10001, 0b10001, 0b01110},
    // 7
    {0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b01000, 0b01000},
    // 8
    {0b01110, 0b10001, 0b10001, 0b01110, 0b10001, 0b10001, 0b01110},
    // 9
    {0b01110, 0b10001, 0b10001, 0b01111, 0b00001, 0b00001, 0b01110},

    // SPACE
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}};

static void lcd_delay_ms(int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

static void lcd_spi_send_bytes(const uint8_t *data, int len)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));

    t.length = len * 8;
    t.tx_buffer = data;

    ESP_ERROR_CHECK(spi_device_transmit(lcd_spi, &t));
}

static void lcd_spi_send_byte(uint8_t data)
{
    lcd_spi_send_bytes(&data, 1);
}

static void lcd_cmd(uint8_t cmd)
{
    gpio_set_level(LCD_DC, 0);
    lcd_spi_send_byte(cmd);
}

static void lcd_data(uint8_t data)
{
    gpio_set_level(LCD_DC, 1);
    lcd_spi_send_byte(data);
}

static void lcd_data16(uint16_t data)
{
    uint8_t bytes[2];

    bytes[0] = data >> 8;
    bytes[1] = data & 0xFF;

    gpio_set_level(LCD_DC, 1);
    lcd_spi_send_bytes(bytes, 2);
}

static void lcd_reset(void)
{
    gpio_set_level(LCD_RST, 1);
    lcd_delay_ms(100);

    gpio_set_level(LCD_RST, 0);
    lcd_delay_ms(100);

    gpio_set_level(LCD_RST, 1);
    lcd_delay_ms(200);
}

static void lcd_spi_init(void)
{
    spi_bus_config_t buscfg = {
        .sclk_io_num = LCD_SCK,
        .mosi_io_num = LCD_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_W * 2,
    };

    ESP_ERROR_CHECK(spi_bus_initialize(
        LCD_HOST,
        &buscfg,
        SPI_DMA_CH_AUTO));

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 3,
        .spics_io_num = -1,
        .queue_size = 1,
    };

    ESP_ERROR_CHECK(spi_bus_add_device(
        LCD_HOST,
        &devcfg,
        &lcd_spi));
}

static void lcd_init(void)
{
    lcd_reset();

    lcd_cmd(0x01);
    lcd_delay_ms(150);

    lcd_cmd(0x11);
    lcd_delay_ms(150);

    lcd_cmd(0x3A);
    lcd_data(0x55);
    lcd_delay_ms(10);

    lcd_cmd(0x36);
    lcd_data(0x00);

    lcd_cmd(0x21);

    lcd_cmd(0x13);
    lcd_delay_ms(10);

    lcd_cmd(0x29);
    lcd_delay_ms(100);
}

static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    lcd_cmd(0x2A);
    lcd_data16(x0);
    lcd_data16(x1);

    lcd_cmd(0x2B);
    lcd_data16(y0);
    lcd_data16(y1);

    lcd_cmd(0x2C);
}

static void lcd_send_color(uint16_t color)
{
    uint8_t bytes[2];

    bytes[0] = color >> 8;
    bytes[1] = color & 0xFF;

    lcd_spi_send_bytes(bytes, 2);
}

static void lcd_fill_color(uint16_t color)
{
    static uint8_t line[LCD_W * 2];

    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    for (int x = 0; x < LCD_W; x++)
    {
        line[x * 2] = hi;
        line[x * 2 + 1] = lo;
    }

    lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

    gpio_set_level(LCD_DC, 1);

    for (int y = 0; y < LCD_H; y++)
    {
        lcd_spi_send_bytes(line, sizeof(line));
    }
}

static void lcd_draw_rect(int x, int y, int w, int h, uint16_t color)
{
    if (x < 0 || y < 0 || x + w > LCD_W || y + h > LCD_H)
    {
        return;
    }

    lcd_set_window(x, y, x + w - 1, y + h - 1);

    gpio_set_level(LCD_DC, 1);

    for (int i = 0; i < w * h; i++)
    {
        lcd_send_color(color);
    }
}

static const uint8_t *get_font(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        c = c - 'a' + 'A';
    }

    if (c >= 'A' && c <= 'Z')
    {
        return font_5x7[c - 'A'];
    }

    if (c >= '0' && c <= '9')
    {
        return font_5x7[26 + (c - '0')];
    }

    return font_5x7[36];
}

static void lcd_draw_char(int x, int y, char c, int scale, uint16_t text_color, uint16_t bg_color)
{
    const uint8_t *glyph = get_font(c);

    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int bit = (glyph[row] >> (4 - col)) & 0x01;
            uint16_t color = bit ? text_color : bg_color;

            lcd_draw_rect(
                x + col * scale,
                y + row * scale,
                scale,
                scale,
                color);
        }
    }
}

static void lcd_draw_text(int x, int y, const char *text, int scale, uint16_t text_color, uint16_t bg_color)
{
    int cursor_x = x;

    for (int i = 0; text[i] != '\0'; i++)
    {
        lcd_draw_char(cursor_x, y, text[i], scale, text_color, bg_color);
        cursor_x += 6 * scale;
    }
}

static int lcd_text_width(const char *text, int scale)
{
    return strlen(text) * 6 * scale;
}

static void lcd_draw_text_centered(int y, const char *text, int scale, uint16_t text_color, uint16_t bg_color)
{
    int width = lcd_text_width(text, scale);
    int x = (LCD_W - width) / 2;

    if (x < 0)
    {
        x = 0;
    }

    lcd_draw_text(x, y, text, scale, text_color, bg_color);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting font test");

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LCD_DC) | (1ULL << LCD_RST),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};

    gpio_config(&io_conf);

    gpio_set_level(LCD_DC, 0);
    gpio_set_level(LCD_RST, 1);

    lcd_spi_init();

    lcd_delay_ms(500);

    lcd_init();

    lcd_fill_color(COLOR_YELLOW);

    lcd_draw_text_centered(90, "HELLO", 4, COLOR_BLUE, COLOR_YELLOW);
    lcd_draw_text_centered(140, "WORLD", 4, COLOR_BLUE, COLOR_YELLOW);

    while (1)
    {
        lcd_delay_ms(1000);
    }
}