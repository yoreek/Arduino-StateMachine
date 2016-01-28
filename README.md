# Arduino library for implementating simple state machine [![Build Status](https://travis-ci.org/yoreek/Arduino-StateMachine.svg?branch=master)](https://travis-ci.org/yoreek/Arduino-StateMachine)

* Version: 1.0.0
* Release Date: 2016-01-28

## How do I get set up? ##

 * [Download](https://github.com/yoreek/Arduino-StateMachine/archive/master.zip) the Latest release from gitHub.
 * Unzip and modify the Folder name to "StateMachine".
 * Paste the modified folder on your library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).
 * Restart the Arduino Software


## Usage ##

### Traffic light control example ###
```
#include <Arduino.h>
#include <StateMachine.h>
#define WITH_DEBUG
#include <DebugUtil.h>

// Initialization
...

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
        ...
};

TrafficLight trafficLight((PState) &TrafficLight::STOP);

void loop() {
    trafficLight.loop();
    // Other code
    ...
}

```

Results:

```
0: TrafficLight.ino:25 STOP - STOP
10001: TrafficLight.ino:38 WAIT - WAIT
12002: TrafficLight.ino:51 DRIVE - DRIVE
22003: TrafficLight.ino:64 SLOW - SLOW
24004: TrafficLight.ino:25 STOP - STOP
34006: TrafficLight.ino:38 WAIT - WAIT
36007: TrafficLight.ino:51 DRIVE - DRIVE
...
```

## Example ##

Included on example folder, available on Arduino IDE.


## Version History ##

 * 1.0.0 (2016-01-28): Initial version.


## Links

 * Wikipedia on [Finite State Machines](https://en.wikipedia.org/wiki/Finite-state_machine)
 * [RTTTL Player library](https://github.com/yoreek/Arduino-RtttlPlayer)
 * [Push Button library](https://github.com/yoreek/Arduino-PushButton)


## Who do I talk to? ##

 * [Yoreek](https://github.com/yoreek)
