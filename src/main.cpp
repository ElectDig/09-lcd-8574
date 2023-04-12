/*
 *     Project 09-lcd-8574 - main.cpp
 *
 *     Austral 2023 - Electronica Digital  - EAM
 *
 *     Interfacing LCD 16x2 Display to ESP32 using I2C
 */

//  includes

#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//  definitions and macros

#define LOOP_DELAY 500
#define POTE_VOLTAGE 3.3

#define SPLASH0 "I2C LCD en ESP32"
#define SPLASH1 "Austral EDI 2023"

//  Object creation

LiquidCrystal_I2C lcd(0x27, 16, 2); // i2c address, columns, rows

//  Private functions

/*
 *  show_line
 *      Shows one of line with data
 */

static void
show_line(int line, const char *buf)
{
    lcd.setCursor(0, line);
    lcd.print(buf);
}

/*
 *  fill_display:
 *      Clears and shows both lines
 */

static void
fill_display(const char *line0, const char *line1)
{
    lcd.clear();
    show_line(0, line0);
    show_line(1, line1);
}

//  Public functions

void
setup()
{
    lcd.init();
    lcd.backlight();
    fill_display(SPLASH0, SPLASH1);
    delay(2000);
}

void
loop()
{
    int sensorValue;
    float voltage;
    char buff0[30], buff1[30];

    sensorValue = analogRead(ANAIN);                    //  Reads pote convertes value
    voltage = sensorValue * POTE_VOLTAGE / DIVISOR;     //  Converts to voltage

    sprintf(buff0, "Digital = %4d", sensorValue);       //  Format both lines
    sprintf(buff1, "Voltage = %.2f V", voltage);
    fill_display(buff0, buff1);

    delay(LOOP_DELAY);
}
