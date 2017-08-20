#include "Chronometer.h"

/* Constructor of class */
Chronometer::Chronometer(void){}

/* Function to change next state of machine */
void Chronometer::stateMachine(events *_event, states *_currentState, states *_nextState){
    switch(*_currentState){
        case RESET:
            Serial.println("Current state: RESET");
            switch(*_event){
                case PRESS_PLAY_BUTTON:
                    Serial.println("Event: PRESS_PLAY_BUTTON");
                    *_nextState = PLAY;
                    break;
                case PRESS_CONFIG_BUTTON:
                    Serial.println("Event: PRESS_CONFIG_BUTTON");
                    *_nextState = CONFIG;
                    break;
            }
            break;
        case CONFIG:
            Serial.println("Current state: CONFIG");
            switch(*_event){
                case PRESS_CONFIG_BUTTON:
                    Serial.println("Event: PRESS_CONFIG_BUTTON");
                    *_nextState = RESET;
                    break;
            }
            break;
        case PLAY:
            Serial.println("Current state: PLAY");
            switch(*_event){
                case PRESS_PAUSE_BUTTON:
                    Serial.println("Event: PRESS_PAUSE_BUTTON");
                    *_nextState = PAUSE;
                    break;
            }
            break;
        case PAUSE:
            Serial.println("Current state: PAUSE");
            switch(*_event){
                case PRESS_PLAY_BUTTON:
                    Serial.println("Event: PRESS_PLAY_BUTTON");
                    *_nextState = PLAY;
                    break;
                case PRESS_CONFIG_BUTTON:
                    Serial.println("Event: PRESS_CONFIG_BUTTON");
                    *_nextState = RESET;
                    break;
            }
            break;
    }    
}

/* Function to perform the action of state machine */
void Chronometer::stateSelect(states *_state){
    switch(*_state){
        case RESET:
            Serial.println("State: RESET");
            break;
        case CONFIG:
            Serial.println("State: CONFIG");
            break;
        case PLAY:
            Serial.println("State: PLAY");
            break;
        case PAUSE:
            Serial.println("State: PAUSE");
            break;
    }    
}

/* Destructor of class */
Chronometer::~Chronometer(void){}