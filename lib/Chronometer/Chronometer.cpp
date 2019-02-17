#include "Chronometer.hpp"

/* Constructor of class */
Chronometer::Chronometer(void)
    : regular_game_time_minutes_(DEFAULT_REGULAR_GAME_TIME_MINUTES)
    , regular_game_time_seconds_(DEFAULT_REGULAR_GAME_TIME_SECONDS)
    , addition_game_time_minutes_(DEFAULT_ADDITION_GAME_MINUTES)
    , addition_game_time_seconds_(DEFAULT_ADDITION_GAME_SECONDS)
{
    pinMode(PLAY_PAUSE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(SETTING_BUTTON_PIN, INPUT_PULLUP);
    pinMode(PLUS_BUTTON_PIN, INPUT);
    pinMode(LESS_BUTTON_PIN, INPUT);

    currentState = RESET;
    nextState = RESET;
    occurredEvent = NO;

    _seconds = 0;
    _minutes = 0;

    time_game_minutes_ = regular_game_time_minutes_ + addition_game_time_minutes_;
    time_game_seconds_ = regular_game_time_seconds_ + addition_game_time_seconds_;
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
                    nextState = RUNNING;
                    break;
                case PRESS_SETTING_BUTTON:
                    Serial.println("Event: PRESS_SETTING_BUTTON");
                    nextState = REGULAR_TIME_MINUTES_SETTING;
                    break;
            }
            break;
        case REGULAR_TIME_MINUTES_SETTING:
            Serial.println("Current state: REGULAR_TIME_MINUTES_SETTING");
            switch(event)
            {
                case PRESS_SETTING_BUTTON:
                    Serial.println("Event: PRESS_SETTING_BUTTON");
                    nextState = REGULAR_TIME_SECONDS_SETTING;
                    break;
            }
            break;
        case REGULAR_TIME_SECONDS_SETTING:
            Serial.println("Current state: REGULAR_TIME_SECONDS_SETTING");
            switch(event)
            {
                case PRESS_SETTING_BUTTON:
                    Serial.println("Event: PRESS_SETTING_BUTTON");
                    nextState = ADDITION_TIME_MINUTES_SETTING;
                    break;
            }
            break;
        case ADDITION_TIME_MINUTES_SETTING:
            Serial.println("Current state: ADDITION_TIME_MINUTES_SETTING");
            switch(event)
            {
                case PRESS_SETTING_BUTTON:
                    Serial.println("Event: PRESS_SETTING_BUTTON");
                    nextState = ADDITION_TIME_SECONDS_SETTING;
                    break;
            }
            break;
        case ADDITION_TIME_SECONDS_SETTING:
            Serial.println("Current state: ADDITION_TIME_SECONDS_SETTING");
            switch(event)
            {
                case PRESS_SETTING_BUTTON:
                    Serial.println("Event: PRESS_SETTING_BUTTON");
                    nextState = RESET;
                    break;
            }
            break;
        case RUNNING:
            Serial.println("Current state: RUNNING");
            switch(event)
            {
                case PRESS_PAUSE_BUTTON:
                    Serial.println("Event: PRESS_PAUSE_BUTTON");
                    nextState = STOPPED;
                    break;
            }
            break;
        case STOPPED:
            Serial.println("Current state: STOPPED");
            switch(event)
            {
                case PRESS_PLAY_BUTTON:
                    Serial.println("Event: PRESS_PLAY_BUTTON");
                    nextState = RUNNING;
                    break;
                case PRESS_SETTING_BUTTON:
                    Serial.println("Event: PRESS_SETTING_BUTTON");
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
        case REGULAR_TIME_MINUTES_SETTING:
            Serial.println("State: REGULAR_TIME_MINUTES_SETTING");
            break;
        case REGULAR_TIME_SECONDS_SETTING:
            Serial.println("State: REGULAR_TIME_SECONDS_SETTING");
            break;
        case ADDITION_TIME_MINUTES_SETTING:
            Serial.println("State: ADDITION_TIME_MINUTES_SETTING");
            break;
        case ADDITION_TIME_SECONDS_SETTING:
            Serial.println("State: ADDITION_TIME_SECONDS_SETTING");
            break;
        case RUNNING:
            Serial.println("State: RUNNING");
            play();
            break;
        case STOPPED:
            Serial.println("State: STOPPED");
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

    if(_minutes == regular_game_time_minutes_ && _seconds == regular_game_time_seconds_)
    {
        Serial.println("Game on addition time");
    }
    if(_minutes == time_game_minutes_  && _seconds == time_game_seconds_)
    {
        Serial.println("End Game!");
        this->reset();
        currentState = RESET;
    }


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