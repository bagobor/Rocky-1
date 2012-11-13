SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(SOURCES
  Engine.cpp
  Main.cpp
  Protocol/MessageBuffer.cpp
  Protocol/MessageHandler.cpp
  Protocol/Session.cpp
  Protocol/SessionSecureLayer.cpp
)

ADD_EXECUTABLE(Rocky ${SOURCES})
