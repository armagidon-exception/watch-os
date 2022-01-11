#include "Display.h"
#include "SPI.h"

#define SPI_START SPI.beginTransaction(spiSettings)
#define SPI_END SPI.endTransaction()
#define DC_COMMAND(PIN) digitalWrite(PIN, LOW)
#define DC_DATA(PIN) digitalWrite(PIN, HIGH)
#define RST_PIN 8
#define DC_PIN 7

static SPISettings spiSettings(16000000, MSBFIRST, SPI_MODE3);

Display display;

static void displayParamsInit(Display* display) {
    display->__clearColor = BLACK;
    display->drawingArea[0] = 0; //Set startX to 0
    display->drawingArea[1] = 0; //Set startY to 0
    display->drawingArea[2] = DISPLAY_SIZE; //Set endX to DISPLAY_SIZE
    display->drawingArea[3] = DISPLAY_SIZE; //Set endY to DISPLAY_SIZE
    display->cursor[0] = 0; //Set cursorX to 0
    display->cursor[1] = 1; //Set cursorY to 0
}

void displayInit() {
    displayParamsInit(&display);
    SPI.begin();
    //Hardware reset
    //Pinmode rst pin
    pinMode(RST_PIN, OUTPUT);
    //Proceed with hardware reset
    delay(50);
    digitalWrite(RST_PIN, HIGH);
    delay(50);
    digitalWrite(RST_PIN, LOW);
    delay(50);
    digitalWrite(RST_PIN, HIGH);
    delay(50);

    //Init commands
    //Pinmode command pin
    pinMode(DC_PIN, OUTPUT);
    sendCommand(ST_SWRESET); //Software reset
    delay(120);
    sendCommand(ST_SLPOUT); //Get display out of sleep mode
    sendCommand(ST_DISPON);
    sendCommand(ST_COLMOD);
    sendCommandArgument(0x55);
    sendCommand(ST_MADCTL);
    sendCommandArgument(0);
    sendCommand(ST_INVON);
    sendCommand(ST_NORON);
    delay(20);
}

void writeSPI(uint8_t c) 
{
    SPDR = c;
    asm volatile("rjmp .+0\n");
    asm volatile("rjmp .+0\n");
    asm volatile("rjmp .+0\n");
    asm volatile("rjmp .+0\n");
}

void writeMulti(uint16_t color, uint16_t num) {

    asm volatile (
    "next:\n"
    "out %[spdr],%[hi]\n"
    "rjmp .+0\n"  // wait 8*2+1 = 17 cycles
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "nop\n"
    "out %[spdr],%[lo]\n"
    "rjmp .+0\n"  // wait 6*2+1 = 13 cycles + sbiw + brne
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "rjmp .+0\n"
    "nop\n"
    "sbiw %[num],1\n"
    "brne next\n"
    : [num] "+w" (num)
    : [spdr] "I" (_SFR_IO_ADDR(SPDR)), [lo] "r" ((uint8_t)color), [hi] "r" ((uint8_t)(color>>8)));
}

uint8_t drawingAreaWidth() {
    return display.drawingArea[2] - display.drawingArea[0] + 1;
}

uint8_t drawingAreaHeight() {
    return display.drawingArea[3] - display.drawingArea[1] + 1;
}

void sendCommand(uint8_t command) {
    DC_COMMAND(DC_PIN);
    SPI_START;

    writeSPI(command);

    SPI_END;
}

void sendCommandArgument(uint8_t argument) {
    DC_DATA(DC_PIN);
    SPI_START;

    writeSPI(argument);

    SPI_END;
}

void sendSingularData(uint16_t data) {
    sendRepeatedData(data, 1);
}

void sendRepeatedData(uint16_t data, uint16_t quantity) {
    DC_DATA(DC_PIN);
    SPI_START;

    writeMulti(data, quantity);

    SPI_END;
}

void printBufScaled(buffer buf, Dimension* size, const uint8_t scaleFactor) {
    sendCommand(ST_RAMWR);
    DC_DATA(DC_PIN);
    SPI_START;
    const uint8_t aW = drawingAreaWidth();
    const uint8_t aH = drawingAreaHeight();
    for (uint8_t y = 0; y < size->height; y++)
    {
        for (uint8_t scaleY = 0; scaleY < scaleFactor; scaleY++)
        {
            const uint8_t scaledY = (y * scaleFactor + scaleY); 
            if (scaledY >= aH) {
                goto out2;
            }
            for (uint8_t x = 0; x < size->width; x++)
            {
                for (uint8_t scaleX = 0; scaleX < scaleFactor; scaleX++) {
                    const uint8_t scaledX = (x * scaleFactor + scaleX);
                    if (scaledX >= aW) {
                        goto out1;
                    }

                    uint16_t color = pgm_read_word(&buf[y * size->width + x]);
                    writeMulti(color, 1);
                }
            }
            out1: {}
        }
    }
    out2:

    SPI_END;
}

void printBufScaledWithClearDeltas(buffer buf, Dimension* size, const unit scaleFactor, Vec2D* delta) {
    sendCommand(ST_RAMWR);
    DC_DATA(DC_PIN);
    SPI_START;
    const unit aW = drawingAreaWidth();
    const unit aH = drawingAreaHeight();
    const int8_t dx = delta->x, dy = delta->y;
    if (dy > 0) {
        writeMulti(display.__clearColor, aW * dy);
    }
    for (unit y = 0; y < size->height; y++)
    {
        for (unit scaleY = 0; scaleY < scaleFactor; scaleY++)
        {
            const unit scaledY = (y * scaleFactor + scaleY); 
            if (scaledY >= aH)
                goto out2;
            
            uint16_t buffer[aW];

            if (dx > 0) {
                for (unit i = 0; i < dx; i++)
                {
                    buffer[i] = display.__clearColor;
                }
            }


            unit scaledX;
            for (unit x = 0; x < size->width; x++)
            {
                for (unit scaleX = 0; scaleX < scaleFactor; scaleX++) {
                    scaledX = (x * scaleFactor + scaleX);
                    if (scaledX >= aW) {
                        goto print;
                    }
                    uint16_t color = pgm_read_word(&buf[y * size->width + x]);
                    buffer[scaledX  + (dx > 0 ? dx : 0)] = color;
                }
            }

            if (dx < 0) {
                for (unit i = 0; i < aW - scaledX; i++)
                {
                    buffer[scaledX + i] = display.__clearColor;
                }
            }

            print:
            for (unit i = 0; i < aW; i++)
            {
                writeMulti(buffer[i], 1);
            }
            
        }
    }
    out2:
    if (dy < 0) {
        writeMulti(display.__clearColor, aW * -dy);
    }

    SPI_END;
}