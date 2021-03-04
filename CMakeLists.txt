cmake_minimum_required(VERSION 3.13)
project(oefening1)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR/cmake})

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} "C:/MinGW/include/SDL2")

add_executable(oefening1 main.cpp Factories/AFactory.cpp Factories/AFactory.h Factories/SDL/SDLFactory.cpp Factories/SDL/SDLFactory.h Game.cpp Game.h Entities/SDL/SDLCar.cpp Entities/SDL/SDLCar.h Entities/Car.cpp Entities/Car.h LTimer.cpp LTimer.h Entities/ECar.cpp Entities/ECar.h Entities/SDL/SDLECar.cpp Entities/SDL/SDLECar.h Entities/Entity.cpp Entities/Entity.h Event/EventHandler.cpp Event/EventHandler.h Event/SDL/SDLEventHandler.cpp Event/SDL/SDLEventHandler.h MenuElements/button.cpp MenuElements/button.h MenuElements/SDL/SDLbutton.cpp MenuElements/SDL/SDLbutton.h Music/MusicPlayer.cpp Music/MusicPlayer.h Music/SDL/SDLMusicPlayer.cpp Music/SDL/SDLMusicPlayer.h Entities/Missile.cpp Entities/Missile.h Entities/SDL/SDLMissile.cpp Entities/SDL/SDLMissile.h  Entities/EneMissile.cpp Entities/EneMissile.h Entities/SDL/SDLEneMissile.cpp Entities/SDL/SDLEneMissile.h Entities/Object.cpp Entities/Object.h Entities/SDL/SDLObject.cpp Entities/SDL/SDLObject.h Event/Event.cpp Event/Event.h)
target_link_libraries(oefening1 ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)