#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <Arduino.h>
 
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
        void stateMachine(events *_event, states *_currentState, states *_nextState);
        void stateSelect(states *_state);
        void playPauseCallback();
};

#endif