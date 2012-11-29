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
 * EventManager.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: jmonk
 */

#include "EventManager.h"
#include "string.h"

using namespace std;

namespace dvs {
Event* currentEvent;
EventType currentEventType;

EventManager::EventManager() {
    listeners = new vector<Runnable*>[MAX_EVENT];
    listenerIds = new vector<int>[MAX_EVENT];
    currentMaxId = 1;
}

EventManager::~EventManager() {
    delete[] listeners;
    delete[] listenerIds;
}

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
void EventManager::callEvent(EventType eventType, Event* event) {
    vector<Runnable*>* list = listeners + (int)eventType;
    setCurrentEventType(eventType);
    setCurrentEvent(event);

    for (unsigned int i = 0; i < list->size(); i++) {
        (*list)[i]->run();
    }

    setCurrentEvent(NULL);
}


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
int EventManager::registerListener(EventType eventType, Runnable* listener) {
    listeners[(int)eventType].push_back(listener);
    listenerIds[(int)eventType].push_back(currentMaxId);
    return currentMaxId++;
}


/**
 * Removes a previously registered callback.
 *
 * @param eventType Type to remove registration
 * @param id Registration id returned by registerListener
 *
 */
void EventManager::removeListener(EventType eventType, int id) {
    vector<Runnable*>* list = listeners + (int)eventType;
    vector<int>* listIds = listenerIds + (int)eventType;
    for (unsigned int i = 0; i < list->size(); i++) {
        if ((*listIds)[i] == id) {
            list->erase(list->begin() + i);
            listIds->erase(listIds->begin() + i);
            return;
        }
    }
}

} /* namespace dvs */
