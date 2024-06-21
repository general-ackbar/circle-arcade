
#pragma once
#ifndef Sound_h
#define Sound_h


#include <fatfs/ff.h>
#include <circle/util.h>
#include <circle/alloc.h>
#include <circle/sound/pwmsounddevice.h>

#define bytes_to_u16(MSB,LSB) (((unsigned int) ((unsigned char) MSB)) & 255)<<8 | (((unsigned char) LSB)&255)


#define SOUND_SAMPLES(DATA,CHANNELS)		(sizeof(DATA) / sizeof(DATA[0]) / CHANNELS)

class Sound{

    
private:
    uint8_t* data;    
    int soundChannels;
    int soundBits;
    size_t data_length;
    bool ready;
    bool copy;

public:
	//Sound();
    ~Sound();
    Sound(const char* filename, int channels, int bits);  
    Sound(const Sound& other);    
    Sound& operator=(const Sound&) = delete;
    
    uint8_t* getSoundData() {return data; };
    int getSoundBits() { return soundBits;};
    int getSoundChannels() { return soundChannels;};
    int getSoundSamples() { return  data_length / 2 / soundChannels; };
    int getDataLength() { return data_length; };
    void Play(CPWMSoundDevice *device);
    void Stop(CPWMSoundDevice *device);
};

#endif 
