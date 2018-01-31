#include "Chronometer.hpp"

/* Constructor of class */
Chronometer::Chronometer(void)
{
    pinMode(PLAY_PAUSE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
    pinMode(PLUS_BUTTON_PIN, INPUT);
    pinMode(LESS_BUTTON_PIN, INPUT);

    currentState = RESET;
    nextState = RESET;
    occurredEvent = NO;

    _seconds = 0;
    _minutes = 0;
}

void Chronometer::begin()
{
    Timer1.initialize(1000000);
    Timer1.attachInterrupt(Chronometer::activeInterruptFlag);
    Timer1.stop();
}

void Chronometer::play()
{
    Timer1.resume();
}

void Chronometer::pause()
{
    Timer1.stop();
}

void Chronometer::reset()
{
    _seconds = 0;
    _minutes = 0;
    Timer1.stop();
}

/* Function to change next state of machine */
void Chronometer::stateMachine()
{
    switch(currentState)
    {
        case RESET:
            Serial.println("Current state: RESET");
            switch(event)
            {
                case PRESS_PLAY_BUTTON:
                    Serial.println("Event: PRESS_PLAY_BUTTON");
                    nextState = PLAY;
                    break;
                case PRESS_CONFIG_BUTTON:
                    Serial.println("Event: PRESS_CONFIG_BUTTON");
                    nextState = CONFIG;
                    break;
            }
            break;
        case CONFIG:
            Serial.println("Current state: CONFIG");
            switch(event)
            {
                case PRESS_CONFIG_BUTTON:
                    Serial.println("Event: PRESS_CONFIG_BUTTON");
                    nextState = RESET;
                    break;
            }
            break;
        case PLAY:
            Serial.println("Current state: PLAY");
            switch(event)
            {
                case PRESS_PAUSE_BUTTON:
                    Serial.println("Event: PRESS_PAUSE_BUTTON");
                    nextState = PAUSE;
                    break;
            }
            break;
        case PAUSE:
            Serial.println("Current state: PAUSE");
            switch(event)
            {
                case PRESS_PLAY_BUTTON:
                    Serial.println("Event: PRESS_PLAY_BUTTON");
                    nextState = PLAY;
                    break;
                case PRESS_CONFIG_BUTTON:
                    Serial.println("Event: PRESS_CONFIG_BUTTON");
                    nextState = RESET;
                    break;
            }
            break;
    }    
}

/* Function to perform the action of state machine */
void Chronometer::stateSelect()
{
    switch(nextState)
    {
        case RESET:
            Serial.println("State: RESET");
            reset();
            break;
        case CONFIG:
            Serial.println("State: CONFIG");
            break;
        case PLAY:
            Serial.println("State: PLAY");
            play();
            break;
        case PAUSE:
            Serial.println("State: PAUSE");
            pause();
            break;
    }    
    occurredEvent = NO;
    currentState = nextState;
}

void Chronometer::incrementTime()
{
    _seconds++;
    if(_seconds == 60)
    {
        _seconds = 0;
        _minutes++;
        if(_minutes == 60)
        {
            _minutes = 0;
        }
    }
    Serial.print("Seconds: ");  
    Serial.println(_seconds);
    Serial.print("Minutes: ");
    Serial.println(_minutes);

    interruptFlag = false;   
}

void Chronometer::activeInterruptFlag()
{
    interruptFlag = true;
}

bool Chronometer::interruptFlagActived()
{
    return interruptFlag;
}

/* Destructor of class */
Chronometer::~Chronometer(void)
{

}