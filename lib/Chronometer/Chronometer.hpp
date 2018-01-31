#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <Arduino.h>
#include "TimerOne.h"
 
#define PLAY_PAUSE_BUTTON_PIN 2
#define RESET_BUTTON_PIN 3
#define PLUS_BUTTON_PIN 4
#define LESS_BUTTON_PIN 5

#define POLLING_PERIOD 200 //Time in milliseconds

enum states {RESET, CONFIG, PLAY, PAUSE};                                       //States of machine
enum events {PRESS_PLAY_BUTTON, PRESS_PAUSE_BUTTON, PRESS_CONFIG_BUTTON};       //Possible events
enum occurrences {NO, YES};

class Chronometer{
    
    public:
        Chronometer();
        ~Chronometer(void);
        
        void begin();
        void play();
        void pause();
        void reset();
        void stateMachine();
        void stateSelect();
        void incrementTime();
        bool interruptFlagActived();
        static void activeInterruptFlag();


        static bool interruptFlag;

        states currentState;
        states nextState;
        events event;
        occurrences occurredEvent;

    private:
        uint8_t _seconds;
        uint8_t _minutes;
        TimerOne *_timer;
};

#endif