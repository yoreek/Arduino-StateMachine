#include <Arduino.h>
#include <StateMachine.h>
#define WITH_DEBUG
#include <DebugUtil.h>

#define RED_LED_PIN    10
#define YELLOW_LED_PIN 11
#define GREEN_LED_PIN  12

#define RED_ON()       digitalWrite(RED_LED_PIN, HIGH)
#define YELLOW_ON()    digitalWrite(YELLOW_LED_PIN, HIGH)
#define GREEN_ON()     digitalWrite(GREEN_LED_PIN, HIGH)
#define RED_OFF()      digitalWrite(RED_LED_PIN, LOW)
#define YELLOW_OFF()   digitalWrite(YELLOW_LED_PIN, LOW)
#define GREEN_OFF()    digitalWrite(GREEN_LED_PIN, LOW)

class TrafficLight : public StateMachine {
    public:
        using StateMachine::StateMachine;
        State STOP() {
            if (isStateUpdated()) {
                RED_ON();
                YELLOW_OFF();
                GREEN_OFF();
                DEBUG("STOP");
                return;
            }
            if (isTimeout(10000)) {
                setState((PState) &TrafficLight::WAIT);
                return;
            }
        };
        State WAIT() {
            if (isStateUpdated()) {
                RED_ON();
                YELLOW_ON();
                GREEN_OFF();
                DEBUG("WAIT");
                return;
            }
            if (isTimeout(2000)) {
                setState((PState) &TrafficLight::DRIVE);
                return;
            }
        };
        State DRIVE() {
            if (isStateUpdated()) {
                RED_OFF();
                YELLOW_OFF();
                GREEN_ON();
                DEBUG("DRIVE");
                return;
            }
            if (isTimeout(10000)) {
                setState((PState) &TrafficLight::SLOW);
                return;
            }
        };
        State SLOW() {
            if (isStateUpdated()) {
                RED_OFF();
                YELLOW_ON();
                GREEN_OFF();
                DEBUG("SLOW");
                return;
            }
            if (isTimeout(2000)) {
                setState((PState) &TrafficLight::STOP);
                return;
            }
        };
};

TrafficLight trafficLight((PState) &TrafficLight::STOP);

void setup() {
    Serial.begin(9600);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    RED_OFF();
    YELLOW_OFF();
    GREEN_OFF();
}

void loop() {
    trafficLight.loop();
}

