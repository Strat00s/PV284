#include <Arduino.h>
#include <ShiftRegister74HC595.h>


#define BTN_RED    PB4
#define BTN_YELLOW PA15
#define BTN_GREEN  PB5

#define DATA_PIN  PB14
#define CLOCK_PIN PB15
#define LATCH_PIN PB13


ShiftRegister74HC595<1> sr(DATA_PIN, CLOCK_PIN, LATCH_PIN);

uint8_t pin_num = 0;
uint8_t red_pressed = 0;
uint8_t yellow_pressed = 0;
uint8_t green_pressed = 0;

void setup() {
    //Serial2.begin(9600);
    pinMode(BTN_RED, INPUT);
    pinMode(BTN_YELLOW, INPUT);
    pinMode(BTN_GREEN, INPUT);
    //sr.set(0, HIGH);
}

void loop() {
    //Serial2.printf("%d %d %d\n", digitalRead(BTN_RED), digitalRead(BTN_YELLOW), digitalRead(BTN_GREEN));
    if (!digitalRead(BTN_RED) && !red_pressed) {
        red_pressed = 1;
        sr.setAllHigh();
        delay(500);
        sr.setAllLow();
    }
    else if (!digitalRead(BTN_YELLOW) && !yellow_pressed) {
        yellow_pressed = 1;
        for (uint i = 0; i < 8; i++) {
            sr.set(i, HIGH);
            delay(100);
        }
        delay(500);
        sr.setAllLow();
    }
    else if (!digitalRead(BTN_GREEN) && !green_pressed) {
        green_pressed = 1;
        for (uint8_t i = 0; i < 4; i++)
            sr.set(i * 2 + 1, HIGH);
        delay(500);
        sr.setAllLow();
    }


    if (digitalRead(BTN_RED))
        red_pressed = 0;
    if (digitalRead(BTN_YELLOW))
        yellow_pressed = 0;
    if (digitalRead(BTN_GREEN))
        green_pressed = 0;
}
