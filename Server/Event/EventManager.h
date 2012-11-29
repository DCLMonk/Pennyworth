/**
 * Pennyworth - A new smarthome protocol.
 * Copyright (C) 2012  Dream-Crusher Labs LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
/*
 * EventManager.h
 *
 *  Created on: Nov 24, 2012
 *      Author: jmonk
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "Event.h"
#include "Runnable.h"
#include <vector>

namespace dvs {

typedef enum {
    USER_LOGIN=0,
    
    DEVICE_CREATED=1,
    DEVICE_LOST_CONNECTION=2,

    ROOM_CREATED=3,
    GROUP_CREATED=4,

    FIELD_CREATED=5,
    FIELD_SET=6,
    FIELD_SUBSCRIBED=7,
    FIELD_UNSUBSCRIBED=8,
} EventType;

#define MAX_EVENT 8

extern Event* currentEvent;
extern EventType currentEventType;

class EventManager {
public:
    /**
     * Gets event in progress.
     *
     * This function is used by event listeners to
     * get the event that has triggered the callback.
     *
     * return The event in progress
     */
    static Event* getCurrentEvent() {
        return currentEvent;
    }

    /**
     * Gets type of event in progress.
     *
     * This function is used by event listeners to
     * get the type event that has triggered the 
     * callback.
     *
     * return The type of event in progress
     */
    static EventType getCurrentEventType() {
        return currentEventType;
    }
    
	EventManager();
	virtual ~EventManager();

    /**
     * Calls an event triggering registered callbacks.
     *
     * This calls an event in the Server which will
     * trigger any listeners registered for that event.
     * API users should generally have no reason to
     * call this function.
     *
     * @param eventType Type of event being called
     * @param event Class that holds event data
     */
    void callEvent(EventType eventType, Event* event);

    /**
     * Registers a callback for a specific event type.
     *
     * This function registers a runnable to be called anytime
     * a specific event occurs.  It returns the id of the
     * registration that is required to remove the listener
     * later.
     *
     * @param eventType Type of events to listen for
     * @param listener Callback for event trigger
     * @return Registration ID for removal
     */
    int registerListener(EventType eventType, Runnable* listener);

    /**
     * Removes a previously registered callback.
     *
     * @param eventType Type to remove registration
     * @param id Registration id returned by registerListener
     *
     */
    void removeListener(EventType eventType, int id);

protected:
    static void setCurrentEvent(Event* event) {
        currentEvent = event;
    }
    static void setCurrentEventType(EventType eventType) {
        currentEventType = eventType;
    }

private:
    std::vector<Runnable*>* listeners;
    std::vector<int>* listenerIds;
    int currentMaxId;
};

} /* namespace dvs */
#endif /* EVENTMANAGER_H_ */
