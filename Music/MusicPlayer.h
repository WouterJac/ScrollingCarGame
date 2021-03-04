//
// Created by jacob on 21/03/2019.
//

#ifndef OEFENING1_MUSICPLAYER_H
#define OEFENING1_MUSICPLAYER_H
#include <string>
using namespace std;

//Parent van SDLMusicPLayer

class MusicPlayer {
public:
    //Constructor en destructor
    MusicPlayer();
    virtual ~MusicPlayer();
    //Speel geluid/muziek af
    virtual void playMusic(string name)=0;
    virtual void playSound(string name)=0;
    //Voegt een muziek/sound resource van een path toe onder een bepaalde naam
    virtual void addSound(string name, string path)=0;
    virtual void addMusic(string name, string path)=0;
    //Pauzeer/herstarten van de muziek/sound
    virtual void pauseMusic()=0;
    virtual void resumeMusic()=0;
    virtual void pauseSound()=0;
    virtual void resumeSound()=0;
    //Geeft weer of de muziek momenteel gepauzeerd is
    virtual bool pausedMusic()=0;

};




#endif //OEFENING1_MUSICPLAYER_H
