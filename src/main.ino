#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>
#include "Chronometer.hpp"

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8

float oldTime;

/* Instace of class */
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);
Chronometer chronometer;

bool Chronometer::interruptFlag = false;

void setup()
{
    tft.begin();
    chronometer.begin();
    Serial.begin(115200);

    oldTime = millis();   
}

void loop()
{

    if((millis() - oldTime) >= POLLING_PERIOD)         //If passed POLLING_PERIOD milliseconds
    {
        oldTime = millis();                             //Sto/re actual time

        if(!digitalRead(PLAY_PAUSE_BUTTON_PIN))     //If play_pause_button press
        {        
            switch(chronometer.currentState)                       //Verifify current state to determine the correct event
            {
                case RUNNING:                   
                    chronometer.event = PRESS_PAUSE_BUTTON;
                    break;
                case RESET:case STOPPED:
                    chronometer.event = PRESS_PLAY_BUTTON;
                    break;
            }
            chronometer.occurredEvent = YES;
        }
        if(!digitalRead(SETTING_BUTTON_PIN))
        {
            chronometer.event = PRESS_SETTING_BUTTON;
            chronometer.occurredEvent = YES;
        }
    }

    if(chronometer.occurredEvent == YES)
    {
        chronometer.stateMachine();
        chronometer.stateSelect();
    }

    if(chronometer.interruptFlagActived())
    {
        chronometer.incrementTime();
    }
}