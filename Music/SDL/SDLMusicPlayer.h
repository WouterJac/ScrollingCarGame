//
// Created by jacob on 21/03/2019.
//

#ifndef OEFENING1_SDLMUSICPLAYER_H
#define OEFENING1_SDLMUSICPLAYER_H

#include <string>
#include <SDL_mixer.h>
#include <map>
#include "../MusicPlayer.h"

using namespace std;


class SDLMusicPlayer : public MusicPlayer{
public:
    //Constructor en destructor
    SDLMusicPlayer();
    virtual ~SDLMusicPlayer();
    //Speel geluid/muziek af
    void playMusic(string name);
    void playSound(string name);
    //Voegt een muziek/sound resource van een path toe onder een bepaalde naam
    void addSound(string name, string path);
    void addMusic(string name, string path);
    //Pauzeer/herstarten van de muziek/sound
    void pauseMusic();
    void resumeMusic();
    void pauseSound();
    void resumeSound();
    //Geeft weer of de muziek momenteel gepauzeerd is
    bool pausedMusic();
private:
    //Load sound/muziek gebaseerd op een path, en returnt diens Mix_Music*/Mix_Chunk*
    Mix_Music* loadMusic(string path);
    Mix_Chunk* loadSound(string path);
    //In deze mappen zitten de naam en bijhorende Chunk/Music pointer van muziek/sound
    map<string,Mix_Chunk*> sounds;
    map<string,Mix_Music*> music;

};


#endif //OEFENING1_SDLMUSICPLAYER_H
