#include "trafficLight.h"

// MILLSECOND

long long timeToggleDeley = 1E3;
const long long timeBlinkDeley = 200;

// BUTTON

long long lastTimePushButton; 
const long long needDurationPush = 500;
bool isPush = false;

// MODES

bool isForceGreen = false;
bool isRedShort = false;
ColorNow stateNow = RED;

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void checkButton(){

    //REDO: HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
    int pinStateNow = 0;

    if (pinStateNow){
        if ( isPush ){
            if ( timeInMilliseconds() > lastTimePushButton + needDurationPush ){
                isRedShort = true;

                if ( stateNow & ( RED | BLINK_GREEN | YELLOW ) && ~isForceGreen) {
                    isForceGreen = true;
                } 
            }
        }
        else
        {
            lastTimePushButton = timeInMilliseconds();
            isPush = true;
        }
    }
    else
    {
        isPush = false;
    }
    
}

void diodWork(int pin, bool isBlinking, long long nextTimeDiodToggle){

    long long tempTime;
    long long nextTimeDiodBlink = timeInMilliseconds() + timeBlinkDeley;
    //TODO: HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);

    do {

        tempTime = timeInMilliseconds();

        checkButton();

        if ( isBlinking && nextTimeDiodBlink < tempTime) {
            //TODO: HAL_GPIO_TogglePin(GPIOD, pin);
            nextTimeDiodBlink += timeBlinkDeley;
        }

    } while ( (tempTime < nextTimeDiodToggle && ( ~isRedShort || stateNow != RED) ) 
        || (tempTime < ( nextTimeDiodToggle - 3 * timeToggleDeley ) && stateNow == RED && isRedShort) );

    //TODO: HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);

}

int trafficLight(void){
    
    long long nextTimeDiodToggle = timeInMilliseconds();
    
    while (1){

        nextTimeDiodToggle += timeToggleDeley;
        
        if (isForceGreen){
            diodWork(0, false, nextTimeDiodToggle);
            isForceGreen = false;
            nextTimeDiodToggle += timeToggleDeley;
        }

        switch (stateNow)
        { 
        case RED:
            printf("RED\n");
            nextTimeDiodToggle += 3 * timeToggleDeley;
            diodWork(0, false, nextTimeDiodToggle);
            stateNow = GREEN;
            break;
        case GREEN:
            printf("GREEN\n");
            diodWork(0, false, nextTimeDiodToggle);
            stateNow = BLINK_GREEN;
            break;
        case BLINK_GREEN:
            printf("TEMP_GREEN\n");
            diodWork(0, true, nextTimeDiodToggle);
            stateNow = YELLOW;
            break;
        case YELLOW:
            printf("YELLOW\n");
            diodWork(0, false, nextTimeDiodToggle);
            stateNow = RED;
            break;
        }

    }

}