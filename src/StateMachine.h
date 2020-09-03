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

#define SM_STACK_DEPTH 6

#define SM_CLASS              StateMachine
#define SM_STATE(s)           State SM_CLASS::s()
#define SM_NEXT(s)            setState((PState) &SM_CLASS::s)
#define SM_GOTO(s)            do {                                      \
        setState((PState) &SM_CLASS::s);                                \
        return;                                                         \
    } while (0)
#define SM_CALL(s, r)         do {                                      \
        pushState((PState) &SM_CLASS::r);                               \
        SM_GOTO(s);                                                     \
    } while (0)
#define SM_CALL2(s, r1, r2)   do {                                      \
        pushState((PState) &SM_CLASS::r1);                              \
        pushState((PState) &SM_CLASS::r2);                              \
        SM_GOTO(s);                                                     \
    } while (0)
#define SM_RETURN()           do {                                      \
        setState(popState());                                           \
        return;                                                         \
    } while (0)
#define SM_RETURN_SUCCESS()   do {                                      \
        popState();                                                     \
        setState(popState());                                           \
        return;                                                         \
    } while (0)
#define SM_RETURN_FAIL()      do {                                      \
        setState(popState());                                           \
        popState();                                                     \
        return;                                                         \
    } while (0)
#define SM_TIMED_GOTO(s, t)   do {                                      \
        _delay = t;                                                     \
        SM_CALL(DELAY, s);                                              \
    } while (0)

class StateMachine;

typedef void State;
typedef State (StateMachine::*PState)(void);


class StateMachine {
    public:
        StateMachine(PState curState, PState prevState) :
            _curState(curState),
            _prevState(prevState),
            _paused(false),
            _isStateUpdated(true),
            _stateUpdated(millis()),
            _stackPos(0) {
        };
        StateMachine(PState curState) : StateMachine(curState, NULL) {};
        virtual void loop();
        virtual void idle() {};
        void setState(PState state);
        inline PState getState() { return _curState; };
        inline PState getPrevState() { return _prevState; };
        inline void setPrevState() { setState(_prevState); };
        void pushState(PState state);
        inline void pushState() { pushState(_curState); };
        PState popState();
        inline bool isStateUpdated() { return _isStateUpdated; };
        inline void pause() { _paused = true; };
        inline void restart() { _paused = false; };
        inline bool isPaused() { return _paused; };
        bool isTimeout(uint32_t t) { return (millis() - _stateUpdated) > t; };
        inline uint32_t stateUpdated() { return _stateUpdated; };
        State DELAY();

    protected:
        PState   _curState;
        PState   _prevState;
        bool     _paused;
        bool     _isStateUpdated;
        uint32_t _stateUpdated;
        PState   _stack[SM_STACK_DEPTH];
        uint16_t _stackPos;
        uint32_t _delay;
};

#endif
