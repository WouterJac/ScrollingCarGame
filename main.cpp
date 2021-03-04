// Oefening 1, gebaseerd op voorbeeldprogramma 1

#include <iostream>
#include "Factories/AFactory.h"
#include "Factories/SDL/SDLFactory.h"
#include "Game.h"
#include "Event/EventHandler.h"
#include "Event/SDL/SDLEventHandler.h"
#include "Music/SDL/SDLMusicPlayer.h"

using namespace std;

Game* Game::instance=0;     // Game singleton.

int main(int argc, char* argv[])
{
    int SCREEN_WIDTH = 600;     // Logische size van de game.
    int SCREEN_HEIGHT = 800;

    AFactory* f = new SDLFactory(SCREEN_WIDTH,SCREEN_HEIGHT);
    EventHandler* eh = new SDLEventHandler();
    MusicPlayer* mp = new SDLMusicPlayer();
    //Game* g = new Game(f,eh,mp);
    Game* g = Game::getInstance(f,eh,mp);
    Game* p = Game::getInstance(f,eh,mp);       // P bewijst enkel de werking van het Singleton design-pattern.

    std::cout << "Adres van gebruikte game: "<< g << std::endl;
    std::cout << "Adres van ander game-object: "<< p << std::endl;    // De adressen van g en p zijn dezelfde, er kan dus slechts 1 game bestaan.
    std::cout << "Beide adressen zijn gelijk -> de singleton werkt\n"<<std::endl;

    g->start();
    //f->quit();
    delete g;
    delete f;
    delete eh;
    delete mp;

    return 0;
}