//
// Created by Wouter on 21/03/2019.
//

#include "SDLMusicPlayer.h"

SDLMusicPlayer::SDLMusicPlayer() : MusicPlayer(){

}

SDLMusicPlayer::~SDLMusicPlayer() {

}

void SDLMusicPlayer::addSound(string name, string path) {
    sounds.insert(make_pair(name,loadSound(path)));             //Laadt muziek, geeft deze een naam en voegt deze onder die naam toe aan een map
}

void SDLMusicPlayer::addMusic(string name, string path) {
    music.insert(make_pair(name,loadMusic(path)));              //Laadt muziek, geeft deze een naam en voegt deze onder die naam toe aan een map
}

Mix_Music* SDLMusicPlayer::loadMusic(string path) {
    Mix_Music* gMusic=NULL;
    gMusic = Mix_LoadMUS(path.c_str());     //Load music gebaseerd op een path, en returnt een Mix_Music*
    if (gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return gMusic;
}

Mix_Chunk* SDLMusicPlayer::loadSound(string path) {

    Mix_Chunk* gSound=NULL;                 //Load sound gebaseerd op een path, en returnt een Mix_Chunk*
    gSound = Mix_LoadWAV(path.c_str());
    if (gSound == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return gSound;
}

void SDLMusicPlayer::playMusic(string name) {
    Mix_Music* m = music.find(name)->second;     //Speelt de muziek met de ingegeven naam indien deze in de map staat
    if(m==NULL){
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else{
        Mix_PlayMusic( m,-1);    // 1 = Repeat
    }

}

void SDLMusicPlayer::playSound(string name) {
    Mix_Chunk* s=sounds.find(name)->second;     //Speelt de sound met de ingegeven naam indien deze in de map staat
    if(s==NULL){
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else {
        Mix_PlayChannel(-1, s, 0);
    }
}


void SDLMusicPlayer::pauseMusic() {
    Mix_PauseMusic();                   //Pauzeert muziek
}

void SDLMusicPlayer::resumeMusic() {
    Mix_ResumeMusic();                  //Herstart muziek
}

bool SDLMusicPlayer::pausedMusic() {
    return Mix_PausedMusic();           //Geeft weer of er muziek speelt

}

void SDLMusicPlayer::pauseSound(){
    Mix_Pause(-1);                      //Pauzeert sounds
}

void SDLMusicPlayer::resumeSound(){
    Mix_Resume(-1);                     //Herstart sounds
}
