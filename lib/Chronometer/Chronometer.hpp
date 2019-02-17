#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <Arduino.h>
#include "TimerOne.h"
#include "config.h"

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
        uint8_t time_game_minutes_;
        uint8_t time_game_seconds_;
        uint8_t addition_game_time_minutes_;
        uint8_t addition_game_time_seconds_;
        uint8_t regular_game_time_minutes_;
        uint8_t regular_game_time_seconds_;
        TimerOne *_timer;
};

#endif