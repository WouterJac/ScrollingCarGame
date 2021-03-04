// 
//  Created by Wouter on 4/03/2019.
// 

#include "Game.h"
#include "Event/EventHandler.h"
#include "Entities/Object.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

// Al gedaan:
// abstract factory, windows, player, entity-inheritance, enemy, menu, playercontrol,
// Eventhandler, store enemies, lives, score, gameover & play again, sounds&music, restart
// Missile, highScore, enemy missile, options -> skins, switch ipv if loop, destructors, bonus: Shield
// overstekers, options -> mute musi, enemy schiet missile als je ervoor rijdt, resizable window, sdl coord & gewone coord splitsen
// high score opslaan in file, supermario invincible power , lives -> hartjes (factory), bug key loslaten tijdens unpause, level design, documentatie
// TODO: controller input

// Dingen om te vermelden op PWP: Muziek/mute vanuit config file, walking enemy met ecar-klasse+ID is animated, powerup (shield & ster) met timer (+vulnerable blink time), resizable, menu met options & skins

enum state {
    init, menu, game, end, options, pause       // Mogelijke states van het spel.
};


Game::Game() = default;

Game::~Game() {
    eh=nullptr;

}

Game::Game(AFactory* f, EventHandler* eh, MusicPlayer* mp) {
    this->eh = eh;
    this->mp=mp;
    this->f = f;
    f->initializeGraphics();
    SCREEN_WIDTH = f->SCREEN_WIDTH;         // Verandert niet, logische width en height wordt eenmalig ingegeven voor de gemakzucht.
    SCREEN_HEIGHT = f->SCREEN_HEIGHT;       // Zo kan een button bijvoorbeeld makkelijk gecentreerd worden op het scherm.
    // gamestate = state::init;
}


void Game::start() {

    // Gameloop

    srand(time(NULL));

    state gamestate=state::init;        // Game start met het definiëren van variabelen (levens etc).

    int shieldDuration = 2000;          // Duur van de powerups.
    int starDuration = 6000;
    stringstream frameText;     // Strings voor rendertext en userinput.
    string userInput;
    stringstream lifeText;
    stringstream scoreText;
    stringstream ammoText;

    mp->addMusic("mainmusic", "resources/music/BMTH_Throne_8b.wav");        // Musicplayer krijgt een mapping van resource location en de naam voor deze resource.
    mp->addSound("crashEnd", "resources/sounds/perTotal.wav");
    mp->addSound("crash", "resources/sounds/CarCrash.wav");
    mp->addSound("Pew", "resources/sounds/Pew.wav");
    mp->addSound("Boef", "resources/sounds/Boef.wav");
    mp->addSound("Bop", "resources/sounds/Bop.wav");
    mp->addSound("Schild","resources/sounds/DomienDruppel.wav");
    mp->addSound("Nineties","resources/music/Star.wav");
    mp->addSound("Reload","resources/sounds/Reload.wav");
    string carSprites[10] = {"resources/cars/F12.png", "resources/cars/boxCarPl.png", "resources/cars/Car.bmp", "resources/cars/Tank.png"};
    string carSprite = carSprites[0];           // carSprites bevat alle mogelijke skins van de speler-auto.

    loadConfig();   // Laadt de configfile met oa. de highscore.

    while (!quit) {                 // Zolang men niet afsluit, runt de gameloop.
        switch (gamestate) {        // Game voert acties uit naargelang de state van het spel.
            case state::init : {
                blinks = 2;         // Init -> beginvariabelen van het spel worden gereset, als ook de muziek.
                enemyCount = 0;
                lives = 3;
                ammo = 3;
                score = 0;          // Aantal blinks bij het verliezen van het leven, aantal levens in het begin, ..
                quit = false;
                playerVulnerable = true;
                if (!mute) {
                    if (mp->pausedMusic()) {
                        mp->resumeMusic();
                    }
                    else {
                        mp->playMusic("mainmusic");         // Speel muziek indien niet op mute.
                    }
                }

                gamestate = state::menu;    // Na init wordt het menu getoond.
                break;
            }
            case state::menu : {         // In de menu-state zijn speel en optie-knoppen te zien.
                f->changeBG("resources/backgrounds/title.jpg");
                button* startBut = f->createButton();
                button* optionBut = f->createButton();
                startBut->loadMedia("resources\\buttons\\startButton.png");           // Maak buttons aan en verander background naar menu-achtergrond.
                startBut->setDims(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 200, 120);
                optionBut->loadMedia("resources\\buttons\\optionButton.png");
                optionBut->setDims(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 2, 200, 120);
                while (gamestate == state::menu && !quit) {         // Run zolang het menu niet verlaten wordt.
                    inputEv = eh->pollForEvent();
                    if (inputEv.getQuit()) {        // Gebruik de eventklasse om userinput te verkrijgen.
                        quit = true;
                    }
                    f->loadBG();
                    startBut->render();             // Breng de achtergrond & buttons in de renderbuffer.
                    optionBut->render();
                    if (startBut->clickedOn(inputEv)) {     // Indien een knop aangeklikt wordt, verander van state.
                        mp->playSound("Bop");               // En speel sound "bop" af.
                        gamestate = state::game;
                    }
                    else if (optionBut->clickedOn(inputEv)) {
                        mp->playSound("Bop");
                        gamestate = state::options;     // Naargelang de button, verander de gamestate.
                    }
                    renderAll();    // Visualiseer de renderbuffer.
                }
                delete startBut;
                delete optionBut;
                break;
            }
            case state::options : {
                f->changeBG("resources/backgrounds/Options.jpg");       // In de optie-state worden skins getoond, alsook een back-knop en mute-knop.
                button* backBut = f->createButton();
                button* leftBut = f->createButton();
                button* rightBut = f->createButton();
                button* muteBut = f->createButton();
                backBut->loadMedia("resources\\buttons\\backButton.png");
                backBut->setDims(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 * 7, 200, 120);     // Verander achtergrond en plaats nieuwe buttons.
                leftBut->loadMedia("resources\\buttons\\leftButton.png");
                leftBut->setDims(SCREEN_WIDTH / 8 * 3, SCREEN_HEIGHT / 2, 32, 128);
                rightBut->loadMedia("resources\\buttons\\rightButton.png");
                rightBut->setDims(SCREEN_WIDTH / 8 * 5, SCREEN_HEIGHT / 2, 32, 128);
                muteBut->loadMedia("resources\\buttons\\muteButton.jpg");
                muteBut->setDims(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3 - 30, 200, 90);
                Entity* showCar = f->createCar();                                       //  Plaats een voorbeeld-auto om skin weer te geven.
                showCar->setPos((SCREEN_WIDTH / 2) - showCar->SPRITE_WIDTH / 2,
                                (SCREEN_HEIGHT / 2) - showCar->SPRITE_HEIGHT / 2);
                int currSpr = 0;
                while (gamestate == state::options && !quit) {  //  Zolang men in deze state zit, run volgende render/input code.
                    inputEv = eh->pollForEvent();
                    if (inputEv.getQuit()) {
                        quit = true;        //  Indien de speler op het kruisje klikt, zet de quit-flag aan.
                    }
                    f->loadBG();
                    backBut->render();
                    leftBut->render();       //  Breng de achtergrond & buttons in de renderbuffer.
                    rightBut->render();
                    muteBut->render();
                    showCar->visualize();
                    if (backBut->clickedOn(inputEv)) {     // Bij terugklik wordt de huidige skin ingesteld.
                        mp->playSound("Bop");
                        carSprite = (carSprites[currSpr]);
                        gamestate = state::menu;
                    }
                    else if (leftBut->clickedOn(inputEv)) {   // Klik sprite naar links.
                        mp->playSound("Bop");
                        currSpr--;
                        if (currSpr < 0) {
                            currSpr = 3;                        // Cycle door de mogelijke car-sprites.
                        }
                        showCar->setSpritePath(carSprites[currSpr]);    // Toon de huidige sprite.
                    }
                    else if (rightBut->clickedOn(inputEv)) {  // Klik sprite naar rechts.
                        mp->playSound("Bop");
                        currSpr++;
                        if (currSpr > 3) {
                            currSpr = 0;
                        }
                        showCar->setSpritePath(carSprites[currSpr]);
                    }
                    else if (muteBut->clickedOn(inputEv)) {
                        mute = !mute;
                        if (mute) {
                            mp->pauseMusic();         // Als hierop geklikt wordt valt de muziek weg of begint deze terug.
                        }
                        else {
                            mp->playMusic("mainmusic");
                        }
                    }
                    renderAll();
                }
                delete backBut;
                delete leftBut;
                delete rightBut;
                delete muteBut;
                delete showCar;
                break;
            }
            case state::game : {
                f->changeBG("resources/backgrounds/roadBG5.png");   // Zet scrollende wegachtergrond aan.
                f->setScrolling(true);

                Entity* c = f->createCar();     // Maak de speler-auto aan en zet deze op de startpositie.
                c->setPos(270, 550);
                c->setSpritePath(carSprite);
                bool blinking = false;
                int countblink = blinks;        // Houdt bij hoevaak de auto nog moet knipperen bij botsing.
                frameText << " ";
                scoreText << " ";
                lifeText  << " ";
                ammoText  << " ";
                int random = 100;
                int spawnIncr=0;


                int countedFrames = 0;
                fpsTimer.start();           // Start met het tellen van frames per second.

                while (!quit && gamestate == state::game) {     // Zolang de game niet gesloten wordt, run volgende game-logica.
                    bool pleasePause=false;



                     // THE SPAWN SECTION----------------------------------------------------------

                    spawnIncr++;
                    if (spawnIncr % random == 0) {
                        int lane1 = getRandomLane();
                        addEnemy(lane1, -200, f->createECar());
                        int lane2 = getRandomLane();
                        if (lane2 != lane1) {
                            addEnemy(lane2, -200, f->createECar());             // Maakt enemy cars aan op willekeurige tijdstippen en lanes.
                        }
                        int lane3 = getRandomLane();
                        if ((lane3 != lane1) && (lane3 != lane2)) {
                            addEnemy(lane3, -200, f->createECar());             // Maakt enemy cars aan op willekeurige tijdstippen en lanes.
                        }
                        random = rand() % 50 + 65;
                        spawnIncr=0;
                    }
                    if (score % 800 == 799) {
                        addEnemy(getRandomLane(), -200, f->createObject("Shield"));   // Maakt een schild aan, eens per x tijd.
                    }
                    if(score % 1900 == 1899){
                        addEnemy(getRandomLane(), -200,f->createObject("Star"));
                    }
                    if(score % 390 == 389){
                        addEnemy(getRandomLane(), -200,f->createObject("Ammo"));
                    }
                    if (score % 500 == 499) {
                        Entity* man = f->createECar();
                        man->setAnimated("resources/cars/guy", 4);      // Maakt een voetganger aan, en animeert deze.
                        man->setVel(3, 4);
                        man->setId("Man");
                        addEnemy(0, -40, man);
                    }

                    capTimer.start();       // Timer voor het beperken van de fps (tot 60 fps) start.


                     //THE INPUT SECTION--------------------------------------------------------------



                    inputEv = eh->pollForEvent();        // Handle the user userInput.
                    if (inputEv.getQuit()) {
                        quit = true;
                    }
                    else if (inputEv.getType() == 'k') {      // Indien de user op een knop drukt.
                        if (inputEv.getUpDown() == 1) {         // Updown =1 wilt zeggen dat de knop ingedrukt wordt (0 is losgelaten).
                            if (inputEv.getKey() == "space") {  // De ingedrukte toets is spatie.
                                if(ammo>0) {
                                    mp->playSound("Pew");
                                    addEnemy(c->mPosX + (c->SPRITE_WIDTH / 2), c->mPosY,f->createMissile());   // Maak een missile aan in het midden van de auto.
                                    ammo--;
                                }
                            }
                            else if (inputEv.getKey() == "p") {
                                cout<<"Pause"<<endl;                // Zet de gameloop op pauze bij het indrukken van de 'p'-toets.
                                pleasePause=true;
                            }
                        }
                        c->handleEvent(inputEv);
                    }


                     // THE POWERUP TIMING SECTION---------------------------------


                    if (powerTimer.isStarted()) {   // Indien de speler een powerup genomen heeft, is deze timer actief.
                        if (c->power == "Shield") {
                            if (powerTimer.getTicks() > shieldDuration) {       // Indien de speler een schild heeft, wordt gecheckt.
                                playerVulnerable = true;                        // Of dit schild nog aan blijft staan voor de volgende render.
                                c->setPower("None");
                                powerTimer.stop();
                            }
                        }
                        else if(c->power == "Star"){                           // Speler kan slechts 1 powerup tegelijk hebben.
                            if(powerTimer.getTicks() > starDuration){
                                if(mp->pausedMusic() && !mute){          // Indien de star-powerup verstreken is, start de normale muziek terug.
                                    mp->resumeMusic();
                                }
                                playerVulnerable = true;
                                c->setPower("None");
                                powerTimer.stop();
                            }
                        }
                    }


                     // THE MOVEMENT AND COLLISION SECTION----------------------------


                    c->move();
                    for (int i = 0; i < enemyCount; i++) {              // Beweeg alle entities.
                        Entity* e = enemies[i];
                        e->move();
                        if (e->getId() == "ECar" || e->getId() == "EneMissile" || e->getId() == "Man") {
                            if (e->getId() == "ECar") {
                                if (c->mPosY < e->mPosY && c->mPosX > e->mPosX &&
                                    c->mPosX < e->mPosX + e->SPRITE_WIDTH && !e->hasShot()) {
                                    addEnemy(e->mPosX + (e->SPRITE_WIDTH / 2), e->mPosY, f->createEneMissile());    // Enemy auto's schieten als je ervoor rijdt.
                                    e->shot = true;
                                }
                            }
                            if(e->checkColl(c)) {
                                if(c->power!="Shield" && !blinking) {
                                    if (e->getId() == "ECar") {
                                        e->setId("Explode");
                                        e->setSpritePath("resources/Cars/explode2.png");
                                    }
                                    else {
                                        enemies[i]->setActive(false);
                                    }
                                }
                                if (playerVulnerable) {
                                    lives--;
                                    if (lives > 0) {
                                        mp->playSound("crash");             // Check op collision tussen player en enemy.
                                        playerVulnerable = false;
                                        blinking = true;
                                        eventTimer.start();
                                    }
                                    else {
                                        c->setActive(false);
                                        gamestate = state::end;         // Game over als levens op zijn.
                                        cout << "Game over" << endl;
                                    }
                                }
                            }
                        }
                        else if (e->getId() == "Missile") {
                            for (int j = 0;
                                 j < enemyCount; j++) {              // Check for collision between Missile & Enemy.
                                Entity* p = enemies[j];
                                if (p->getId() == "ECar" || p->getId() == "Man") {
                                    if (e->checkColl(p)) {
                                        mp->playSound("Boef");          // Indien Missile de enemy raakt, verdwijnen beide.
                                        if(p->getId()=="ECar"){
                                            p->setId("Explode");
                                            p->setSpritePath("resources/Cars/explode2.png");

                                        }
                                        else if(p->getId()=="Man"){
                                            // p->setActive(false);
                                            p->setId("Explode");
                                            p->setVel(0,10);
                                            p->setAnimated("resources/Cars/blood.png",-1);
                                        }
                                        e->setActive(false);
                                        break;
                                    }
                                }
                                // delete p;
                            }
                        }
                        else if(e->getId()=="Ammo"){
                            if(e->checkColl(c)) {
                                ammo = ammo + 3;
                                if (ammo > AMMO_CAP) {
                                    ammo = AMMO_CAP;
                                }
                                mp->playSound("Reload");
                                e->setActive(false);
                            }
                        }
                        else if (!powerTimer.isStarted() && !blinking) {   // Er kan maar één power  actief zijn.
                            if (e->getId() == "Shield") {
                                if (e->checkColl(c)) {
                                    mp->playSound("Schild");        // Bij het oppakken van een schild wordt deze power actief.
                                    powerTimer.start();
                                    c->setPower("Shield");
                                    e->setActive(false);
                                    playerVulnerable = false;
                                }
                            }
                            else if (e->getId() == "Star") {
                                if (e->checkColl(c)) {
                                    if(!mute){
                                        mp->pauseMusic();
                                    }
                                    mp->playSound("Nineties");
                                    powerTimer.start();
                                    c->setPower("Star");    // Bij het oppakken van een ster wordt deze power actief.
                                    e->setActive(false);
                                    playerVulnerable = false;
                                }
                            }
                        }
                        // delete e;
                    }
                    deleteInactive();


                     // THE FPS TIMER/CAP SECTION----------------------------------


                    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);      // Bereken FPS.
                    if (avgFPS > 2000000) {
                        avgFPS = 0;
                    }
                    frameText.str(string());   // Clears stringstream.
                    int s = (int) avgFPS;
                    if(s==61){
                        s=60;   // Rounding fix.
                    }
                    frameText << "FPS: " << s;       // cast float naar int = round down.

                    f->loadBG();
                    for (int i = 0; i < enemyCount; i++) {
                        enemies[i]->visualize();
                    }                                           // Visualiseer enemies en player.
                    if (!blinking) {
                        c->visualize();
                    }
                    else {
                        if (eventTimer.isStarted()) {
                            Uint32 blinktime = eventTimer.getTicks();
                            if (blinktime < 400) {
                                // don't visualize car
                            }
                            else if (blinktime > 400 && blinktime < 600) {
                                c->visualize();
                            }
                            else if (blinktime >= 600) {
                                c->visualize();
                                eventTimer.stop();
                                countblink--;
                                if (countblink < 1) {               // Wanneer de player gebotst is, zal deze blinken.
                                    blinking = false;               // Hier wordt bepaald hoe lang de player blinkt.

                                    playerVulnerable = true;
                                    countblink = blinks;
                                }
                                else {
                                    eventTimer.start();
                                }
                            }
                        }
                    }


                    //THE RENDER SECTION---------------------------------------


                    f->renderText(frameText.str(), "white", 20, 10);
                    f->renderText(lifeText.str(), "white", 380, 10);   // Toon score en fps.
                    f->renderLife(lives);
                    f->renderText(scoreText.str(),"white",450,750);
                    f->renderText(ammoText.str(), "white",450, 50);

                    if(pleasePause){
                        c->setVel(0,0);
                        pauseGame();
                    }
                    else {
                        renderAll();
                    }


                    //SECOND PART OF FPS TIMER/CAP----------------------


                    ++countedFrames;
                    int frameTicks = capTimer.getTicks();
                    if (frameTicks < SCREEN_TICK_PER_FRAME) {
                        f->pauseRender(SCREEN_TICK_PER_FRAME - frameTicks);     // Wacht de overige tijd om FPS te cappen.
                    }
                    score++;

                    // Setup voor de volgende gameloop.

                    lifeText.str(string()); // Maak strings leeg.
                    scoreText.str(string());
                    ammoText.str(string());
                    ammoText << " Ammo: "<<ammo;
                    lifeText << "Lives: ";
                    scoreText<< "Score: " << score;


                }
                delete c;
                break;
            }

            case state::end : {          // De end-state geeft "GAME OVER" en de behaalde eindscore + highscore, en play again button.
                button* b1 = f->createButton();
                button* b2 = f->createButton();
                mp->pauseMusic();   // Muziek stopt en crash speelt af
                mp->playSound("crashEnd");
                f->changeBG("resources/backgrounds/gameOver.png");      // Verander achtergrond naar Game Over.
                f->setScrolling(false);
                if (score > highScore) {
                    highScore = score;      // update highscore
                }
                scoreText.str(string());
                scoreText << "Score: " << score;
                b1->loadMedia("resources\\buttons\\playAgain.png");     // Play again button.
                b1->setDims(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 * 5, 200, 120);
                f->loadBG();
                f->renderText(scoreText.str(), "white", 250, 350);
                scoreText.str(string());
                scoreText << "HighScore: " << highScore;
                f->renderText(scoreText.str(), "white", 250, 380);      // Display de score.
                b1->render();
                renderAll();
                while (!quit && gamestate == state::end) {  // Wacht op userinput.
                    inputEv = eh->pollForEvent();
                    if (inputEv.getQuit()) {
                        quit = true;
                    }
                    else if (b1->clickedOn(inputEv)) {     // Play again start het spel terug op.
                        mp->playSound("Bop");
                        gamestate = state::init;
                    }
                }
                delete b1;
                delete b2;
                break;
            }
            default:
                printf("[ERROR] System wasn't set up properly, can't start game.");
                break;
        }
    }
    saveConfig();       // Sla de highscore en opties op in een file.
}

void Game::pauseGame(){     // Functie bij het pauzeren van het spel.
    mp->pauseMusic();
    mp->pauseSound();
    powerTimer.pause();     // Timers en geluid worden gepauzeerd.
    eventTimer.pause();

    f->setScrolling(false);
    f->changeBG("resources/backgrounds/Paused.png");    // Pauzescherm wordt bovenop het laatste spelbeeld gerenderd.
    f->loadBG();
    f->renderAll();

    Event pauseEv;
    bool paused = true;


    wait(100);

    while(paused && !pauseEv.getQuit()){
        pauseEv.clear();

        pauseEv=eh->pollForEvent();     // Wacht op een 'p' om terug te starten.

        if(pauseEv.getKey()=="p" && pauseEv.getUpDown()==1 ){
            paused = false;
        }
        if(pauseEv.getKey()=="return"){
            f->handleWindowEvent(pauseEv);  // Indien de speler fullscreen wilt activeren.
        }
    }

    if(pauseEv.getQuit()){  // Indien het spel afgesloten wordt -> quit.
        quit=true;
    }

    f->changeBG("resources/backgrounds/roadBG5.png");
    f->loadBG();
    f->setScrolling(true);

    eventTimer.unpause();
    powerTimer.unpause();   // Hervat geluid en timers.
    if(!mute) {
        mp->resumeMusic();
    }
    mp->resumeSound();
}

void Game::renderAll() {

    f->handleWindowEvent(inputEv);
    f->renderAll();
    f->renderClear();           // Breng de renderbuffer naar het scherm, en clear deze nadien.
}

void Game::addEnemy(int x, int y, Entity* ent) {
    ent->setPos(x, y);
    enemies[enemyCount] = ent;      // Maak nieuwe enemy aan op een bepaalde positie, en voeg deze toe aan de enemylijst.
    enemyCount++;
}

void Game::deleteInactive() {
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i]->isActive()) {
            if (enemyCount == 1) {
                delete enemies[0];
                enemyCount--;
            }
            else {
                delete enemies[i];
                for (int j = i; j < (enemyCount - 1); j++) {            // Checkt of alle enemies nog actief zijn, en verwijdert inactieve enemies.
                    enemies[j] = enemies[j + 1];
                }
                enemyCount--;
            }
        }
    }
}

void Game::saveConfig(){
    ofstream myfile ("config.txt");     // TODO: Don't make this user readable
    if (myfile.is_open())
    {
        myfile << highScore<<"\n";
        myfile << mute<<"\n";
        myfile.close();
        cout<<"Saved variables to config.txt"<<endl;        // Schrijft config en highscore naar een file.
    }
    else cout << "Unable to open file";
}

void Game::loadConfig(){
    string line;
    ifstream myfile ("config.txt");
    if (myfile.is_open())
    {
        getline (myfile,line);
        highScore = stoi(line);
        getline (myfile,line);
        mute = stoi(line);

        myfile.close();
        cout<<"Loaded config.txt"<<endl;        // Leest config en highscore uit een file.
    }
    else cout << "No config.txt file found";
}

Game *Game::getInstance(AFactory* f, EventHandler* eh, MusicPlayer* mp) {
    if (instance==0)
    {
        instance = new Game(f,eh,mp);       // Maakt gebruik van het singleton design patern zodat er slechts 1 game kan zijn.
    }

    return instance;
}

void Game::wait(int ms){
    LTimer* time = new LTimer;
    time->start();
    while(time->getTicks()<ms){     // Wacht een bepaalde tijd.
        // cout<<"Waiting"<<endl;
    }
    delete time;
}

int Game::getRandomLane() {
    return 77 + (125 * (rand() % 4));
}