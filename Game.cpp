#include "Game.h"


Game::Game(int width, int height){
    this->screenWidth = width;
    this->screenHeight = height;
}

void Game::setSoundDevice(CPWMSoundDevice *device)
{
    this->soundDevice = device;
}


Game::~Game(){
    soundDevice->CancelPlayback();
    while(soundDevice->PlaybackActive())
    {

        //wait for playback to end.
    }
}

void Game::SetActive(bool state)
{
    active = state;
}



void Game::SaveHighscoreToFile(int highscore, const char* file)
{

    Text txt = Text(file, FA_WRITE | FA_CREATE_ALWAYS);
    CString s;
    s.Format("%i", highscore);
    txt.Write(s);
    txt.Close();

}

int Game::LoadHighscoreFromFile(const char* file) {
    int loadedHighscore = 0;
    Text txt = Text(file, FA_READ | FA_OPEN_ALWAYS);
    loadedHighscore =  atoi( txt.Read() );    
    txt.Close();
    return loadedHighscore;
}

bool Game::EventTriggered(double interval, int ticks)
{
    double currentTime = ticks;
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}