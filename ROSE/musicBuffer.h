#pragma once
#include <AL/al.h>
#include<sndfile.h>

namespace ROSE {
	class musicBuffer {
	public:
		void Play();
		void Stop();
		void Pause();
		void Resume();

		void updateBufferStream();
		musicBuffer(const char* filename);
		~musicBuffer();

		bool isPlaying();
	private:
		//sauce
		ALuint se_source;

		static const int b_samples = 8192;
		static const int num_buffers = 4;
		ALuint se_buffers[num_buffers];

		//data from soundtrack is needed for the buffers
		SNDFILE* se_sndfile;
		SF_INFO se_sfinfo;

		//because memory is important :)
		short* se_membuf;

		ALenum se_format;

		//a music buffer needs a file name so no default constructor
		musicBuffer() = delete;
	};


}
