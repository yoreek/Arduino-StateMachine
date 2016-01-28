/*
 * StateMachine.h - Arduino library for implementating simple state machine
 * Copyright (C) 2016 Yuriy Ustushenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the version 3 GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>

class StateMachine;

typedef void State;
typedef State (StateMachine::*PState)(void);

class StateMachine {
    public:
        StateMachine(PState curState, PState prevState) :
            _curState(curState),
            _prevState(prevState),
            _finished(false),
            _isStateUpdated(true),
            _stateUpdated(millis()) {
        };
        StateMachine(PState curState) : StateMachine(curState, NULL) {};
        virtual void loop();
        virtual void idle() {};
        virtual void setState(PState state);
        inline PState getState() { return _curState; };
        inline PState getPrevState() { return _prevState; };
        inline void setPrevState() { setState(_prevState); };
        inline bool isStateUpdated() { return _isStateUpdated; };
        inline void finish() { _finished = true; };
        inline void restart() { _finished = false; };
        inline bool isTimeout(uint32_t t) { return (millis() - _stateUpdated) > t; };
        inline uint32_t stateUpdated() { return _stateUpdated; };

    protected:
        PState   _curState;
        PState   _prevState;
        bool     _finished;
        bool     _isStateUpdated;
        uint32_t _stateUpdated;

};

#endif
