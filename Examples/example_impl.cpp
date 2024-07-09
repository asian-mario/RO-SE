#include "../ROSE/ROSE.h"

int main() {
	std::vector <soundDevice*> soundDevice;
	std::vector <soundBuffer*> soundBuffer;
	std::vector <soundSource*> soundSource;
	std::vector <SoundList*> SoundList;
	std::vector <musicBuffer*> musictracks;

	SoundList SndList;
	g.SoundList.push_back(&SndList);

	soundDevice* sndDevice = soundDevice::get();
	sndDevice->setAttunation(AL_INVERSE_DISTANCE_CLAMPED);
	sndDevice->setLocation(0.0f, 0.0f, 0.0f);
	sndDevice->setOrientation(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	soundDevice.push_back(sndDevice);

	soundSource crntSpeaker;
	soundSource.push_back(&crntSpeaker);

	musicBuffer mainTrack("./sounds/longtrack.mp3");
	musictracks.push_back(&mainTrack);

	musictracks[0]->Play();

	if (g.musicOn == true)
		g.musictracks[0]->updateBufferStream();

	return 0;
}