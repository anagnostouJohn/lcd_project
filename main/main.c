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

#include <stdio.h>
#include <stdint.h>

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

    IMPORTANT:
    Do NOT put 5V on SCK/SDA/DC/RES.
*/

#define LCD_SCK 16
#define LCD_MOSI 15
#define LCD_DC 17
#define LCD_RST 18

#define LCD_W 240
#define LCD_H 240

#define LCD_X_OFFSET 0
#define LCD_Y_OFFSET 0

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE 0x001F
#define COLOR_YELLOW 0xFFE0
#define COLOR_PURPLE 0x8010
#define COLOR_CYAN 0x07FF

static const char *TAG = "ST7789_SMILEY";

/*
    16x16 smiley sprite.

    . = transparent/background black
    Y = yellow
    K = black
    R = red
*/
static const char smiley_16x16[16][17] = {
    "................",
    ".....YYYYYY.....",
    "...YYYYYYYYYY...",
    "..YYYYYYYYYYYY..",
    ".YYYYYYYYYYYYYY.",
    ".YYYKKYYYYKKYYY.",
    "YYYYKKYYYYKKYYYY",
    "YYYYYYYYYYYYYYYY",
    "YYYYYYYYYYYYYYYY",
    "YYYYYRRRRRRYYYYY",
    ".YYYYRYYYYRYYYY.",
    ".YYYYYRRRYYYYYY.",
    "..YYYYYYYYYYYY..",
    "...YYYYYYYYYY...",
    ".....YYYYYY.....",
    "................"};

static void lcd_delay_ms(int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

static void lcd_delay_us(int us)
{
    esp_rom_delay_us(us);
}

/*
    Bit-banged SPI mode 3 style:
    - clock idle HIGH
    - data changes while clock is LOW
    - LCD reads data on rising edge
*/
static void spi_write_byte(uint8_t data)
{
    gpio_set_level(LCD_SCK, 1);

    for (int i = 7; i >= 0; i--)
    {
        gpio_set_level(LCD_SCK, 0);
        lcd_delay_us(1);

        gpio_set_level(LCD_MOSI, (data >> i) & 0x01);
        lcd_delay_us(1);

        gpio_set_level(LCD_SCK, 1);
        lcd_delay_us(1);
    }
}

static void lcd_cmd(uint8_t cmd)
{
    gpio_set_level(LCD_DC, 0);
    lcd_delay_us(1);
    spi_write_byte(cmd);
}

static void lcd_data(uint8_t data)
{
    gpio_set_level(LCD_DC, 1);
    lcd_delay_us(1);
    spi_write_byte(data);
}

static void lcd_data16(uint16_t data)
{
    lcd_data(data >> 8);
    lcd_data(data & 0xFF);
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

static void lcd_init(void)
{
    lcd_reset();

    ESP_LOGI(TAG, "SWRESET");
    lcd_cmd(0x01); // Software reset
    lcd_delay_ms(150);

    ESP_LOGI(TAG, "SLPOUT");
    lcd_cmd(0x11); // Sleep out
    lcd_delay_ms(150);

    ESP_LOGI(TAG, "COLMOD RGB565");
    lcd_cmd(0x3A);  // Color mode
    lcd_data(0x55); // 16-bit RGB565
    lcd_delay_ms(10);

    ESP_LOGI(TAG, "MADCTL");
    lcd_cmd(0x36); // Memory access control
    lcd_data(0x00);

    ESP_LOGI(TAG, "INVOFF");
    lcd_cmd(0x20); // Inversion off

    ESP_LOGI(TAG, "NORON");
    lcd_cmd(0x13); // Normal display mode
    lcd_delay_ms(10);

    ESP_LOGI(TAG, "DISPON");
    lcd_cmd(0x29); // Display on
    lcd_delay_ms(100);
}

static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    x0 += LCD_X_OFFSET;
    x1 += LCD_X_OFFSET;
    y0 += LCD_Y_OFFSET;
    y1 += LCD_Y_OFFSET;

    lcd_cmd(0x2A); // CASET - column address
    lcd_data16(x0);
    lcd_data16(x1);

    lcd_cmd(0x2B); // RASET - row address
    lcd_data16(y0);
    lcd_data16(y1);

    lcd_cmd(0x2C); // RAMWR - memory write
}

static void lcd_send_color(uint16_t color)
{
    spi_write_byte(color >> 8);
    spi_write_byte(color & 0xFF);
}

static void lcd_fill(uint16_t color)
{
    lcd_set_window(0, 0, LCD_W - 1, LCD_H - 1);

    gpio_set_level(LCD_DC, 1);
    lcd_delay_us(1);

    for (int i = 0; i < LCD_W * LCD_H; i++)
    {
        lcd_send_color(color);
    }
}

static uint16_t sprite_color(char c, uint16_t background)
{
    switch (c)
    {
    case 'Y':
        return COLOR_YELLOW;
    case 'K':
        return COLOR_BLACK;
    case 'R':
        return COLOR_RED;
    case 'W':
        return COLOR_WHITE;
    case 'B':
        return COLOR_BLUE;
    case 'G':
        return COLOR_GREEN;
    case 'P':
        return COLOR_PURPLE;
    case 'C':
        return COLOR_CYAN;
    case '.':
    default:
        return background;
    }
}

/*
    Draws a 16x16 sprite scaled up.

    Example:
    scale = 1 -> 16x16
    scale = 4 -> 64x64
    scale = 6 -> 96x96
*/
static void lcd_draw_sprite_16x16_scaled(
    int x,
    int y,
    const char sprite[16][17],
    int scale,
    uint16_t background)
{
    int width = 16 * scale;

    for (int row = 0; row < 16; row++)
    {
        for (int sy = 0; sy < scale; sy++)
        {
            int screen_y = y + row * scale + sy;

            lcd_set_window(
                x,
                screen_y,
                x + width - 1,
                screen_y);

            gpio_set_level(LCD_DC, 1);
            lcd_delay_us(1);

            for (int col = 0; col < 16; col++)
            {
                uint16_t color = sprite_color(sprite[row][col], background);

                for (int sx = 0; sx < scale; sx++)
                {
                    lcd_send_color(color);
                }
            }
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting ST7789 smiley test");

    gpio_config_t conf = {
        .pin_bit_mask = (1ULL << LCD_SCK) |
                        (1ULL << LCD_MOSI) |
                        (1ULL << LCD_DC) |
                        (1ULL << LCD_RST),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};

    gpio_config(&conf);

    gpio_set_level(LCD_SCK, 1);
    gpio_set_level(LCD_MOSI, 0);
    gpio_set_level(LCD_DC, 0);
    gpio_set_level(LCD_RST, 1);

    lcd_delay_ms(500);

    lcd_init();

    while (1)
    {
        ESP_LOGI(TAG, "Smiley on black");
        lcd_fill(COLOR_BLACK);
        lcd_draw_sprite_16x16_scaled(72, 72, smiley_16x16, 6, COLOR_BLACK);
        lcd_delay_ms(3000);

        ESP_LOGI(TAG, "Smiley on blue");
        lcd_fill(COLOR_BLUE);
        lcd_draw_sprite_16x16_scaled(72, 72, smiley_16x16, 6, COLOR_BLUE);
        lcd_delay_ms(3000);

        ESP_LOGI(TAG, "Smiley on purple");
        lcd_fill(COLOR_PURPLE);
        lcd_draw_sprite_16x16_scaled(72, 72, smiley_16x16, 6, COLOR_PURPLE);
        lcd_delay_ms(3000);

        ESP_LOGI(TAG, "Color cycle test");
        lcd_fill(COLOR_RED);
        lcd_delay_ms(800);

        lcd_fill(COLOR_GREEN);
        lcd_delay_ms(800);

        lcd_fill(COLOR_BLUE);
        lcd_delay_ms(800);

        lcd_fill(COLOR_WHITE);
        lcd_delay_ms(800);

        lcd_fill(COLOR_BLACK);
        lcd_delay_ms(800);
    }
}