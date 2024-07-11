#pragma once

#include "ROSE.h"
#include <vector>

int main() {
    bool musicOn = false;

    std::vector<ROSE::soundDevice*> sndDevices;
    std::vector<ROSE::soundBuffer*> sndBuffers;
    std::vector<ROSE::soundSource*> sndSources;
    std::vector<ROSE::musicBuffer*> msicTracks;

    ROSE::soundDevice* sndDevice = ROSE::soundDevice::get();
    sndDevice->setAttunation(AL_INVERSE_DISTANCE_CLAMPED);
    sndDevice->setLocation(0.0f, 0.0f, 0.0f);
    sndDevice->setOrientation(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    sndDevices.push_back(sndDevice);

    ROSE::soundSource crntSpeaker;
    sndSources.push_back(&crntSpeaker);

    ROSE::musicBuffer mainTrack("./sounds/longtrack.mp3");

    msicTracks.push_back(&mainTrack);

    msicTracks[0]->Play();

    if (msicTracks[0]->isPlaying()) {
        musicOn = true;
    }

    if (musicOn == true)
        msicTracks[0]->updateBufferStream();

    return 0;
}

