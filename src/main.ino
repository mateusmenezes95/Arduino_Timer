#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>

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

enum states {RESET, CONFIG, PLAY, PAUSE};                                    //States of machine
enum events {PRESS_PLAY_BUTTON, PRESS_PAUSE_BUTTON, PRESS_CONFIG_BUTTON};    //Possible events
enum occurrences {NO, YES};                                                   //States os occurrences

//******************************* Globals Variables *******************************\\

states currentState = RESET;        //Store the actual state of machine
states nextState = RESET;            //Store the next state of machine
events event;
occurrences occurredEvent = NO;     //Store flag of event occurence
uint8_t minutes = 0;                //Store minutes of timer
uint8_t seconds = 0;                //Store seconds of timer

// char serialValue;


Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

void setup(){
  tft.begin();
  Serial.begin(115200); 
}

void loop(){
    // if(Serial.available()){
    //     occurredEvent = YES;
    //     serialValue = Serial.read();
    //     switch(serialValue){
    //         case '1':
    //             event = PRESS_PLAY_BUTTON;
    //             Serial.println("Event: PRESS_PLAY_BUTTON");
    //             break;
    //         case '2':
    //             event = PRESS_PAUSE_BUTTON;
    //             Serial.println("Event: PRESS_PAUSE_BUTTON");
    //             break;
    //         case '3':
    //             event = PRESS_CONFIG_BUTTON;
    //             Serial.println("Event: PRESS_CONFIG_BUTTON");
    //             break;
    //     }
    // } 
    if(occurredEvent == YES){
        stateMachine(event);
        stateSelect(nextState);
        currentState = nextState;
        occurredEvent = NO;
    }
}

//******************************* State Machine *******************************\\

void stateMachine(events _event){        //Function to change next state of machine 
    switch(currentState){
        case RESET:
            switch(_event){
                case PRESS_PLAY_BUTTON:
                    nextState = PLAY;
                    break;
                case PRESS_CONFIG_BUTTON:
                    nextState = CONFIG;
                    break;
            }
        break;
        case CONFIG:
            switch(_event){
                case PRESS_CONFIG_BUTTON:
                    nextState = RESET;
                    break;
            }
        break;
        case PLAY:
            switch(_event){
                case PRESS_PAUSE_BUTTON:
                    nextState = PAUSE;
                    break;
            }
        break;
        case PAUSE:
            switch(_event){
                case PRESS_PLAY_BUTTON:
                    nextState = PLAY;
                    break;
                case PRESS_CONFIG_BUTT0N:
                    nextState = RESET;
                    break;
            }
        break;
    }
}

void stateSelect(states state){
    switch(state){
        case RESET:
            // Serial.println("State: RESET");
            break;
        case CONFIG:
            // Serial.println("State: CONFIG");
            break;
        case PLAY:
            // Serial.println("State: PLAY");
            break;
        case PAUSE:
            // Serial.println("State: PAUSE");
            break;
    }
}


  

  



