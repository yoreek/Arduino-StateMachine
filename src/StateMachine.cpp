/*
 * StateMachine.cpp - Arduino library for implementating simple state machine
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
#include "StateMachine.h"
#ifndef WITH_STATE_MACHINE_DEBUG
#  undef WITH_DEBUG
#endif
#include <DebugUtil.h>

void StateMachine::setState(PState state) {
    _prevState    = _curState;
    _curState     = state;
    _stateUpdated = millis();
}

void StateMachine::pushState(PState state) {
    if (_stackPos < SM_STACK_DEPTH) {
        _stack[_stackPos++] = state;
    }
    else {
        // Stack overflow
        DEBUG("stack overflow");
        while (1)
            ;
    }
}

PState StateMachine::popState() {
    if (_stackPos > 0) {
        return _stack[--_stackPos];
    }
    else {
        return NULL;
    }
}

void StateMachine::loop() {
    if (_paused) {
        idle();
    }
    else {
        PState oldState = _curState;
        (this->*_curState)();
        _isStateUpdated = (oldState != _curState);
    }
}

State StateMachine::DELAY(void) {
    if (isTimeout(_delay)) {
        SM_RETURN();
    }
}
