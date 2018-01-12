#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>
#include <Chronometer.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8                                                    //States os occurrences

//******************************* Globals Variables *******************************\\

states currentState = RESET;        //Store the actual state of machine
states nextState = RESET;           //Store the next state of machine
events event;
occurrences occurredEvent = NO;     //Store flag of event occurence
uint8_t minutes = 0;                //Store minutes of timer
uint8_t seconds = 0;                //Store seconds of timer

float oldTime;

// char serialValue;

/* Instace of class */
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);
Chronometer chronometer;


void setup()
{
    tft.begin();
    Serial.begin(115200);

    oldTime = millis();   
}

void loop(){

    if((millis() - oldTime) >= POLLING_PERIOD){         //If passed POLLING_PERIOD milliseconds
        oldTime = millis();                             //Store actual time

        if(!digitalRead(PLAY_PAUSE_BUTTON_PIN))     //If play_pause_button press
        {        
            switch(currentState)                       //Verifify current state to determine the correct event
            {
                case PLAY:                   
                    event = PRESS_PAUSE_BUTTON;
                    occurredEvent = YES;
                    break;
                case RESET:case PAUSE:
                    event = PRESS_PLAY_BUTTON;
                    occurredEvent = YES;
                    break;
            }
        }
        else
        {
            if(!digitalRead(RESET_BUTTON_PIN))
            {
                event = PRESS_CONFIG_BUTTON;
                occurredEvent = YES;
            }
        }
    }

    if(occurredEvent == YES)
    {
        chronometer.stateMachine(&event, &currentState, &nextState);
        chronometer.stateSelect(&nextState);
        currentState = nextState;
        occurredEvent = NO;
    }
}


  

  



