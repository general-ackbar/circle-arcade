#include "Sound.h"
#include "../assets/audio/no_sound.h"

/*
Sound::Sound()
{
    data = no_sound;
    soundBits = 16;
    soundChannels = 2;
    data_length = no_sound_length;
    ready = true;
}
*/

Sound::~Sound()
{
    delete[] data;
    data = nullptr;
}

Sound::Sound(const char *filename, int channels, int bits)
{
    FIL myfile;
    if( f_open(&myfile, filename, FA_READ) == FR_OK)
    {
        UINT btr;
        
                
        data_length = f_size(&myfile);
        data = new uint8_t[data_length];
                
        f_read(&myfile, data, data_length, &btr );
        f_close(&myfile);

        soundBits = bits;
        soundChannels = channels;
        ready = true;
    } else {
        data = no_sound;
        soundBits = 16;
        soundChannels = 2;
        data_length = SOUND_SAMPLES(no_sound, soundChannels);
        ready = true;
    }

}

Sound::Sound(const Sound &other)
{
    soundBits = other.soundBits;
    soundChannels = other.soundChannels;
    data_length = other.data_length;
    if (other.data != nullptr) {
        data = new uint8_t[data_length];
        for (size_t i = 0; i < data_length; ++i) {
            data[i] = other.data[i];
        }
        copy = true;
    } else {
        data = nullptr;
    }
}

void Sound::Play(CPWMSoundDevice *device)
{
    if(ready && device != nullptr && !device->PlaybackActive())
    {
        device->Playback(data, getSoundSamples(), soundChannels, soundBits);
    }
}

void Sound::Stop(CPWMSoundDevice *device)
{
    if(device != nullptr && device->PlaybackActive())
        device->CancelPlayback();
}
