/**
 * This file is part of Rocky.
 *
 * Copyright (c) 2012, VolumetricPixels <http://www.volumetricpixels.com/>
 * Rocky is licensed under the GNU Lesser General Public License.
 *
 * Rocky is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rocky is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include <map>
#include <string>

typedef boost::signal1<void, Event> EventSignal;

class EventManager {

public:

	boost::signals::connection& addListener(std::string& eventName, EventSignal::slot_type& slot);

	Event& callEvent(std::string& eventName, Event& event);

	EventSignal& registerEvent(std::string& eventName);

private:
	// Stores all of the events, their signals, and their corresponding connections (listeners)
	std::map<std::string, boost::signal1<void, Event>> events;

};

#endif // _EVENT_MANAGER_HPP_