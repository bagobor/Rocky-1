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

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <string>

class Event {

public:

	enum EventPriority {
		LOWEST, LOW, NORMAL, HIGH, HIGHEST
	};

protected:
	
	Event(std::string name, EventPriority priority) {
		this->name = name;
		this->priority = priority;
		this->priority
	}

public:

	std::string& getName() {
		return name;
	}

	EventPriority getPriority() {
		return priority;
	}

protected:
	std::string name;
	EventPriority priority;

};

#endif // _EVENT_HPP_