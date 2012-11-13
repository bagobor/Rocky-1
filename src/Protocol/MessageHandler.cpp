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

#include <Protocol/MessageHandler.hpp>
#include <Engine.hpp>

#include <Protocol/Message/KeepAliveMessage.hpp>
#include <Protocol/Message/ClientStatusMessage.hpp>
#include <Protocol/Message/EncryptationKeyRequestMessage.hpp>

#define CASE_PACKET(hex, classname) \
    case hex: {\
    classname messageType; \
    messageType.read(in); \
    handleMessage(&messageType, engine); \
    break; \
}\
 
     
void handleMessage(KeepAliveMessage *message, Engine *engine)
{
    KeepAliveMessage response(message->getAliveId());
    engine->getSession().send(response);
}

void handleMessage(EncryptationKeyRequestMessage *message, Engine *engine)
{
    ClientStatusMessage response(INITIAL_SPAWN_STATUS);
    engine->getSession().send(response);
}

void MessageHandler::readMessage(MessageBuffer &in, unsigned int id)
{
    Engine *engine = Engine::getSingletonPtr();
    switch (id)
    {
        CASE_PACKET(0x00, KeepAliveMessage);
        CASE_PACKET(0xFD, EncryptationKeyRequestMessage);
    }
}

void MessageHandler::writeMessage(MessageBuffer &out, Message &message)
{
    // Every vanilla packet start with a header of 1 Byte.
    out << (unsigned char) message.getId();

    // After the header, we write the packet
    message.write(out);
}
